#include <reg52.h>
#include "usart.h"
#include "iic.h"  
/*
Ӳ���ӷ���
GY-33----C51
SCL---P3^6
SDA---P3^7
C51---FT232
TX ---RX
RX ---TX
���˵����
�ó������IIC��GY-33���ж�ȡ����
������λ�����Ͷ�Ӧָ�
A5 51 F6 ----�ϴ�����
A5 BB 60 ----��ƽ��
ע��
	IICʱ��Ƶ�������100Khz��
	�жϺ���λ��stc_it.c
��ϵ��ʽ��
http://shop62474960.taobao.com/?spm=a230r.7195193.1997079397.2.9qa3Ky&v=1
*/
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
void delay(unsigned int x)
{
	while(x--);
}
int main(void)
{
	unsigned char  raw_data[9]={0};
	unsigned int datas[4]={0};
	RGBC rgbc={0,0,0,0};
	RGB rgb={0,0,0};
	uint16_t CT=0,Lux=0;
	u8 color=0;

	Usart_Int(9600);
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
			
		}
		delay(5000);
		if(Calibration==1)//����һ�ΰ�ƽ��ָ��
		{
			Single_WriteI2C_byte(0xb4,0x10,0x31);
			Calibration=3;
		}
	}
}
