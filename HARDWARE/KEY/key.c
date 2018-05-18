#include "key.h"
#include "delay.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//����������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
#if KEY_NEED

//������ʼ������
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIOA,GPIOEʱ��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //KEY0 KEY1 KEY2��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP��Ӧ����PA0
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA0
	
	//������̺�����ʼ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11; //C4 C3 C2 C1 ��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//�ٶ�100M
  GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIOD,8,9,10,11
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; //R1 R2 R3 R4 ��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIOD,12,13,14,15
} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��WKUP���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>WK_UP!!

u8 KEY_Scan(u8 mode)
{	 
	u16 value,key;
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	
	//����ɨ�迪ʼ
		GPIO_Write(GPIOD,0X0f00);
		delay_us(1);
		value=GPIO_ReadInputData(GPIOD);
		value&=0x0f00;
		switch(value)
		{
			case 0x0700:
				key=1;
				break;
			case 0x0B00:
				key=2;
				break;
			case 0x0D00:
				key=3;
				break;
			case 0x0E00:
				key=4;
				break;
			default:
				key=0;
				break;
		}
		if(key)
		{
				GPIO_Write(GPIOD,0Xf000);
				delay_us(1);
				value=GPIO_ReadInputData(GPIOD);
				value&=0xf000;
				switch(value)
				{
					case 0xE000:
						key+=0;
						break;
					case 0xD000:
						key+=4;
						break;
					case 0xB000:
						key+=8;
						break;
					case 0x7000:
						key+=12;
						break;
					default:
						key=0;
						break;
				}
		}
			if(KEY0==1||KEY1==1)
			{
				delay_ms(1);
				if(KEY0==1) key=17;
				else if(KEY1==1)key=18;
			}
	//����ɨ�����
	
	if(key_up&&key)
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(key)return key;
		
	}else if(key==0)key_up=1; 	    
 	return 0x0000;// �ް�������
}



#endif


