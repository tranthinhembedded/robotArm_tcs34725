#include <reg52.h>
#include "usart.h"
#include "iic.h"  
/*
Ӳ���ӷ���
GY-33---c51
1��GY-33_RX---c51_TX,c51��λ������A5 01 A6 ��ģ��
2��c51_TX---FT232,STM32�������ϴ�����λ��
3��GY-33_TX---c51_RX������ģ��Ƕ�����
���˵��:
�ó�����ô��ڷ�ʽ��ȡģ��rgb���ݣ�������9600
���Ե�����λ���Ƚ�ģ�鴮�����ó�9600��Ȼ���ٽ������ϲ�����
ָ��:A5 AE 53,ģ���踴λ��Ч

ע���жϺ���λ��stc_it.c
��ϵ��ʽ��
http://shop62474960.taobao.com/?spm=a230r.7195193.1997079397.2.9qa3Ky&v=1
*/
void send_com(u8 datas)
{
	u8 bytes[3]={0};
	bytes[0]=0xa5;
	bytes[1]=datas;//�����ֽ�
	USART_Send(bytes,3);//����֡ͷ�������ֽڡ�У���
}
typedef struct
{
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
} RGB;
int main(void)
{

    u8 sum=0,i=0;
	RGB rgb={0,0,0};
	Usart_Int(9600);
	send_com(0x01);//���Ͷ���λ��ָ��
 	while(1)
	{
		if(Receive_ok)//���ڽ������
		{
			for(sum=0,i=0;i<(rgb_data[3]+4);i++)//rgb_data[3]=3
			sum+=rgb_data[i];
			if(sum==rgb_data[i])//У����ж�
			{
				rgb.Red=rgb_data[4];
				rgb.Green=rgb_data[5];
                rgb.Blue=rgb_data[6];
				send_3out(&rgb_data[4],3,0x45);//�ϴ�����λ��
			}
			Receive_ok=0;//����������ϱ�־
		}	
	}
}
