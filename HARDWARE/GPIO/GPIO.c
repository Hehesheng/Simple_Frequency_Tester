#include "GPIO.h"
/////////////////////////////////////////////////
//通用性GPIO初始化函数
//麒骏出品
/////////////////////////////////////////////////

/////////////////////////////////////////////////
//按自己的需求定义，示例如下：
#define   GPIOA_NEED			1
#define 	GPIOA_Pin 			GPIO_Pin_2|GPIO_Pin_3						//定义使用的引脚
#define	  GPIOA_Mode 			GPIO_Mode_OUT						//定义端口模式：通用输出、复位状态的输入、复用功能模式、模拟输入模式
#define   GPIOA_OType			GPIO_OType_PP						//定义输出类型：推挽模式（pp）、开漏（od） 
#define   GPIOA_Speed			GPIO_Speed_100MHz				//定义输出速度（2/25/50/100）
#define		GPIOA_PuPd			GPIO_PuPd_UP						//定义IO口的上下拉：（NOPULL、UP、DOWN）
/////////////////////////////////////////////////

void GPIO_UNIVERSAL_SET (void)
{
//	GPIO_InitTypeDef	GPIOA_InitStructure
	
//时钟使能条件编译区
#if GPIOA_NEED
	GPIO_InitTypeDef  GPIOA_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//如果定义了GPIOA，就使能GPIOA时钟
#endif 	

#if GPIOB_NEED
	GPIO_InitTypeDef  GPIOB_InitStructure;	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//如果定义了GPIOB，就使能GPIOB时钟
#endif 	
	
#if GPIOC_NEED
	GPIO_InitTypeDef  GPIOC_InitStructure;		
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//如果定义了GPIOC，就使能GPIOC时钟

#endif 
	
#if GPIOD_NEED
	GPIO_InitTypeDef  GPIOD_InitStructure;	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//如果定义了GPIOD，就使能GPIOD时钟

#endif 

#if GPIOE_NEED
	GPIO_InitTypeDef  GPIOE_InitStructure;	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//如果定义了GPIOE，就使能GPIOE时钟

#endif 

#if GPIOF_NEED
	GPIO_InitTypeDef  GPIOF_InitStructure;	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//如果定义了GPIOF，就使能GPIOF时钟

#endif 	

#if GPIOG_NEED
	GPIO_InitTypeDef  GPIOG_InitStructure;	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//如果定义了GPIOF，就使能GPIOF时钟

#endif 

//GPIO_Init函数编写区

#if GPIOA_NEED	//如果定义了GPIOA，就执行编译
  GPIOA_InitStructure.GPIO_Pin = GPIOA_Pin;
  GPIOA_InitStructure.GPIO_Mode = GPIOA_Mode;
	#ifdef	GPIOA_OType
  GPIOA_InitStructure.GPIO_OType = GPIOA_OType;
	#endif
  GPIOA_InitStructure.GPIO_Speed = GPIOA_Speed;
  GPIOA_InitStructure.GPIO_PuPd = GPIOA_PuPd;
  GPIO_Init(GPIOA, &GPIOA_InitStructure);
#endif

#if GPIOB_NEED	//如果定义了GPIOB，就执行编译
  GPIOB_InitStructure.GPIO_Pin = GPIOB_Pin;
  GPIOB_InitStructure.GPIO_Mode = GPIOB_Mode;
	#ifdef	GPIOB_OType
  GPIOB_InitStructure.GPIO_OType = GPIOB_OType;
	#endif
  GPIOB_InitStructure.GPIO_Speed = GPIOB_Speed;
  GPIOB_InitStructure.GPIO_PuPd = GPIOB_PuPd;
  GPIO_Init(GPIOB, &GPIOB_InitStructure);
#endif

#if GPIOC_NEED	//如果定义了GPIOC，就执行编译
  GPIOC_InitStructure.GPIO_Pin = GPIOC_Pin;
  GPIOC_InitStructure.GPIO_Mode = GPIOC_Mode;
	#ifdef	GPIOC_OType
  GPIOC_InitStructure.GPIO_OType = GPIOC_OType;
	#endif
  GPIOC_InitStructure.GPIO_Speed = GPIOC_Speed;
  GPIOC_InitStructure.GPIO_PuPd = GPIOC_PuPd;
  GPIO_Init(GPIOC, &GPIOC_InitStructure);
#endif

#if GPIOD_NEED	//如果定义了GPIOD，就执行编译
  GPIOD_InitStructure.GPIO_Pin = GPIOD_Pin;
  GPIOD_InitStructure.GPIO_Mode = GPIOD_Mode;
	#ifdef	GPIOD_OType
  GPIOD_InitStructure.GPIO_OType = GPIOD_OType;
	#endif
  GPIOD_InitStructure.GPIO_Speed = GPIOD_Speed;
  GPIOD_InitStructure.GPIO_PuPd = GPIOD_PuPd;
  GPIO_Init(GPIOD, &GPIOD_InitStructure);
#endif

#if GPIOE_NEED	//如果定义了GPIOE，就执行编译
  GPIOE_InitStructure.GPIO_Pin = GPIOE_Pin;
  GPIOE_InitStructure.GPIO_Mode = GPIOE_Mode;
	#ifdef	GPIOE_OType
  GPIOE_InitStructure.GPIO_OType = GPIOE_OType;
	#endif
  GPIOE_InitStructure.GPIO_Speed = GPIOE_Speed;
  GPIOE_InitStructure.GPIO_PuPd = GPIOE_PuPd;
  GPIO_Init(GPIOE, &GPIOE_InitStructure);
#endif

#if GPIOF_NEED	//如果定义了GPIOF，就执行编译
  GPIOF_InitStructure.GPIO_Pin = GPIOF_Pin;
  GPIOF_InitStructure.GPIO_Mode = GPIOF_Mode;
	#ifdef	GPIOF_OType
  GPIOF_InitStructure.GPIO_OType = GPIOF_OType;
	#endif
  GPIOF_InitStructure.GPIO_Speed = GPIOF_Speed;
  GPIOF_InitStructure.GPIO_PuPd = GPIOF_PuPd;
  GPIO_Init(GPIOF, &GPIOF_InitStructure);
#endif

#if	GPIOG_NEED	//如果定义了GPIOG，就执行编译
  GPIOG_InitStructure.GPIO_Pin = GPIOG_Pin;
  GPIOG_InitStructure.GPIO_Mode = GPIOG_Mode;
	#ifdef	GPIOG_OType
  GPIOG_InitStructure.GPIO_OType = GPIOG_OType;
	#endif
  GPIOG_InitStructure.GPIO_Speed = GPIOG_Speed;
  GPIOG_InitStructure.GPIO_PuPd = GPIOG_PuPd;
  GPIO_Init(GPIOG, &GPIOG_InitStructure);
#endif

}






