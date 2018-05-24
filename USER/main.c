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
//#include "pwm.h"
//#include "key.h"
//#include "adc.h"
#include "GPIO.h"
#include "ads1115.h"
#include "myiic.h"
#include "AD9959.h"
#include "task.h"

#define HMISendend		printf("\xff\xff\xff")
extern double DB_S[450];//电压增益转化数组
extern u8 DB_OK;//电压增益转化数组得到成功
int main(void)			
{ 
	//int final1;

	GPIO_UNIVERSAL_SET();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);//初始化串口波特率为115200	pa10rx  pa9tx
//ad9959的初始化//////////////////////////////////////////
	Init_AD9959();	//模块初始化
	Freq_Updata(50000);
    //ads_filter(0);
    //ads_filter(3);
//			Write_frequence();	//写入初始频率
//			Write_Amplitude():		//写入初始幅值
//			Write_Phase();				//写入初始相位
////////////////////////////////////////////////////////
	//GPIO_UNIVERSAL_SET( );
printf("t7.txt=\"db\"");
HMISendend;
	while(1)
	{	
		

		if(USART_RX_STA & 0x8000)//接收到了信息
		{
			u8 task = 0;
			u32 need_sol_num;
			task = USART_RX_BUF[0];
			need_sol_num = string_2_val(USART_RX_BUF, (u8)USART_RX_STA);//提取字符串内容
			switch(task)
			{
				case Frequpdata_task:
				{
					Freq_Updata(need_sol_num);
					delay_ms(100);
					get_endval( );		
					break;
				}
				case Freqscan_task:
				{
					printf("n0.val=1");//表示正在转换
					HMISendend;
					S_DB_valget();
					while(DB_OK == 0);
					printf("n0.val=0");//表示转换结束
					HMISendend;
					draw_graph(DB_S);//画图
					DB_OK = 0;//清空标志
				}
			}
            USART_RX_STA = 0;//清空接收

		}
	}
	
}

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
		 


