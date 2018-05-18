///////////////////////////////////////////////////////////////////////////
////以完成通用性集成模块：串口屏、通用性GPOI设定、ads1115驱动、按键
//	#define	IIC_NEED							0 						//是否需要iic（需要（1）/不需要（0））
//	#define	ADS_1115_NEED					1							//是否需要ads1115（需要（1）/不需要（0）） 
//	#define HMI_SET         		  1							//是否需要串口屏	（需要（1）/不需要（0）） 
//	#define KEY_NEED         		  0							//是否需要按键	（需要（1）/不需要（0）） 	
////////////////////////////////////////////////////////////////////////////

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"
#include "key.h"
#include "adc.h"
#include "GPIO.h"
#include "ads1115.h"
#include "myiic.h"
#include "AD9959.h"

#define HMISendend		printf("\xff\xff\xff")

int main(void)			
{ 
	//int final1;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);//初始化串口波特率为115200	pa10rx  pa9tx
//ad9959的初始化//////////////////////////////////////////
	Init_AD9959();	//模块初始化
//			Write_frequence();	//写入初始频率
//			Write_Amplitude():		//写入初始幅值
//			Write_Phase();				//写入初始相位
////////////////////////////////////////////////////////
	//GPIO_UNIVERSAL_SET( );

	while(1)
	{	
//		ads_filter(2);				//ads1115的初始化被包括进去了，需要取出来吗？
//		final1=(int)( VIN_DAS*1000);
//		
//		if( final1==0 )
//		{
//			printf("n0.val=1");
//			HMISendend;
//		}else
//		{
//			printf("n0.val=%d",final1);
//			HMISendend;			
//		}
		 
	}
	
}




