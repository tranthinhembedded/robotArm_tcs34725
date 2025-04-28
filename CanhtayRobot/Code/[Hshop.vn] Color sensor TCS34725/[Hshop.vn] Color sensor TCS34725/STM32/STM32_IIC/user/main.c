#include "stm32f10x.h"
#include "LED.h"
#include "IIC.h"
#include "delay.h"
#include "usart.h"
/*
Keil: MDK5.10.0.2
MCU:stm32f103c8
Ӳ���ӷ���
GY-TCS3414---STM32
SCL---PB6
SDA---PB7
STM32---FT232
TX---RX
RX---TX
���˵��:
�ó������IIC��GY-TCS3414���ж�ȡ����
������λ�����Ͷ�Ӧָ�
A5 51 F6 ----�ϴ�����
A5 BB 60 ----��ƽ��
ע��
	IICʱ��Ƶ�������100Khz��
	�жϺ���λ��stm32f10x_it.c
��ϵ��ʽ��
http://shop62474960.taobao.com/?spm=a230r.7195193.1997079397.2.9qa3Ky&v=1
*/
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_X;
  
  /* 4����ռ���ȼ���4����Ӧ���ȼ� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  /*��ռ���ȼ��ɴ���жϼ���͵��ж�*/
	/*��Ӧ���ȼ����ȼ�ִ��*/
	NVIC_X.NVIC_IRQChannel = USART1_IRQn;//�ж�����
  NVIC_X.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
  NVIC_X.NVIC_IRQChannelSubPriority = 0;//��Ӧ���ȼ�
  NVIC_X.NVIC_IRQChannelCmd = ENABLE;//ʹ���ж���Ӧ
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
	delay_ms(1);//�ȴ�ģ���ʼ�����
	while(1)
	{
		if(Calibration==0)//��ȡ���ݲ��ϴ�����λ��
		{
			if(Single_ReadI2C(0xb4,0x00,raw_data,8))//��ȡԭʼRGBCֵ
			{
				datas[0]=rgbc.Red=(raw_data[0]<<8)|raw_data[1];
				datas[1]=rgbc.Green=(raw_data[2]<<8)|raw_data[3];
				datas[2]=rgbc.Blue=(raw_data[4]<<8)|raw_data[5];
				datas[3]=rgbc.Clear=(raw_data[6]<<8)|raw_data[7];
			}
			send_out(datas,4,0x15);//���ڷ���
			
			if(Single_ReadI2C(0xb4,0x08,raw_data,4))//��ȡɫ�£�����
			{
				datas[0]=Lux=(raw_data[0]<<8)|raw_data[1];
				datas[1]=CT=(raw_data[2]<<8)|raw_data[3];
			}
			if(Single_ReadI2C(0xb4,0x0f,raw_data,1))//��ȡ��ɫ
				datas[2]=color=raw_data[0];
			 send_out(datas,3,0x25);//���ڷ���
			
			if(Single_ReadI2C(0xb4,0x0c,raw_data,3))//��ȡ������rgb
			{
				rgb.Red=raw_data[0];
				rgb.Green=raw_data[1];
				rgb.Blue=raw_data[2];
			}
			send_3out(raw_data,3,0x45);//���ڷ���
			delay_ms(100);//��ʱ
		}
		
		if(Calibration==1)//����һ�ΰ�ƽ��ָ��
		{
			Single_WriteI2C_byte(0xb4,0x10,0x31);/*��010�Ĵ���д��0x31,3��ʾLED���ȵȼ�Ϊ3��1��ʾ���а�ƽ��*/
			Calibration=3;
		}
	}
}
