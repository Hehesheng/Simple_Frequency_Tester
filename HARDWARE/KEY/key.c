#include "key.h"
#include "delay.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//按键输入驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
#if KEY_NEED

//按键初始化函数
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOA,GPIOE时钟
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP对应引脚PA0
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA0
	
	//矩阵键盘函数开始
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11; //C4 C3 C2 C1 对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//速度100M
  GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIOD,8,9,10,11
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; //R1 R2 R3 R4 对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输入模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIOD,12,13,14,15
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，WKUP按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!

u8 KEY_Scan(u8 mode)
{	 
	u16 value,key;
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	
	//键盘扫描开始
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
	//键盘扫描结束
	
	if(key_up&&key)
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(key)return key;
		
	}else if(key==0)key_up=1; 	    
 	return 0x0000;// 无按键按下
}



#endif


