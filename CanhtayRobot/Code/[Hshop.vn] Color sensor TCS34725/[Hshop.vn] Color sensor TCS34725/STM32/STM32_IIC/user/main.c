#include "stm32f10x.h"
#include "LED.h"
#include "IIC.h"
#include "delay.h"
#include "usart.h"
/*
Keil: MDK5.10.0.2
MCU:stm32f103c8
硬件接法：
GY-TCS3414---STM32
SCL---PB6
SDA---PB7
STM32---FT232
TX---RX
RX---TX
软件说明:
该程序采用IIC对GY-TCS3414进行读取数据
采用上位机发送对应指令：
A5 51 F6 ----上传数据
A5 BB 60 ----白平衡
注：
	IIC时钟频率需低于100Khz；
	中断函数位于stm32f10x_it.c
联系方式：
http://shop62474960.taobao.com/?spm=a230r.7195193.1997079397.2.9qa3Ky&v=1
*/
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_X;
  
  /* 4个抢占优先级，4个响应优先级 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  /*抢占优先级可打断中断级别低的中断*/
	/*响应优先级按等级执行*/
	NVIC_X.NVIC_IRQChannel = USART1_IRQn;//中断向量
  NVIC_X.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
  NVIC_X.NVIC_IRQChannelSubPriority = 0;//响应优先级
  NVIC_X.NVIC_IRQChannelCmd = ENABLE;//使能中断响应
  NVIC_Init(&NVIC_X);
}
typedef struct
{
    uint16_t Red;
    uint16_t Green;
    uint16_t Blue;
    uint16_t Clear;
} RGBC;
typedef struct
{
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
} RGB;
int main(void)
{
	u8  raw_data[9]={0},data=0;
	u16 datas[4]={0};
	RGBC rgbc={0,0,0,0};
	RGB rgb={0,0,0};
	uint16_t CT=0,Lux=0;
	u8 color=0;
	
	delay_init(72);
	LED_Int(GPIOB,GPIO_Pin_9,RCC_APB2Periph_GPIOB);
	NVIC_Configuration();
	Usart_Int(115200);
	I2C_GPIO_Config();
	delay_ms(1);//等待模块初始化完成
	while(1)
	{
		if(Calibration==0)//读取数据并上传给上位机
		{
			if(Single_ReadI2C(0xb4,0x00,raw_data,8))//读取原始RGBC值
			{
				datas[0]=rgbc.Red=(raw_data[0]<<8)|raw_data[1];
				datas[1]=rgbc.Green=(raw_data[2]<<8)|raw_data[3];
				datas[2]=rgbc.Blue=(raw_data[4]<<8)|raw_data[5];
				datas[3]=rgbc.Clear=(raw_data[6]<<8)|raw_data[7];
			}
			send_out(datas,4,0x15);//串口发送
			
			if(Single_ReadI2C(0xb4,0x08,raw_data,4))//读取色温，亮度
			{
				datas[0]=Lux=(raw_data[0]<<8)|raw_data[1];
				datas[1]=CT=(raw_data[2]<<8)|raw_data[3];
			}
			if(Single_ReadI2C(0xb4,0x0f,raw_data,1))//读取颜色
				datas[2]=color=raw_data[0];
			 send_out(datas,3,0x25);//串口发送
			
			if(Single_ReadI2C(0xb4,0x0c,raw_data,3))//读取处理后的rgb
			{
				rgb.Red=raw_data[0];
				rgb.Green=raw_data[1];
				rgb.Blue=raw_data[2];
			}
			send_3out(raw_data,3,0x45);//串口发送
			delay_ms(100);//延时
		}
		
		if(Calibration==1)//发送一次白平衡指令
		{
			Single_WriteI2C_byte(0xb4,0x10,0x31);/*向010寄存器写入0x31,3表示LED亮度等级为3；1表示进行白平衡*/
			Calibration=3;
		}
	}
}
