#include "pwm.h"
#include "usart.h"
 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ��PWM ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 


//TIM14 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
//void TIM14_PWM_Init(u32 arr_1,u32 psc_1)     //pf9
//{		 					 
//	GPIO_InitTypeDef GPIO_InitStructure_1;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure_1;
//	TIM_OCInitTypeDef  TIM_OCInitStructure_1;
//	//tim14 

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);  	//TIM14ʱ��ʹ��    
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 	//ʹ��PORTFʱ��	
//	
//	GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_TIM14); //GPIOF9����Ϊ��ʱ��14
//	
//	GPIO_InitStructure_1.GPIO_Pin = GPIO_Pin_9;           //GPIOF9
//	GPIO_InitStructure_1.GPIO_Mode = GPIO_Mode_AF;        //���ù���
//	GPIO_InitStructure_1.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
//	GPIO_InitStructure_1.GPIO_OType = GPIO_OType_PP;      //���츴�����
//	GPIO_InitStructure_1.GPIO_PuPd = GPIO_PuPd_UP;        //����
//	GPIO_Init(GPIOF,&GPIO_InitStructure_1);              //��ʼ��PF9

//		
//	TIM_TimeBaseStructure_1.TIM_Prescaler=psc_1;  //��ʱ����Ƶ
//	TIM_TimeBaseStructure_1.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
//	TIM_TimeBaseStructure_1.TIM_Period=arr_1;   //�Զ���װ��ֵ
//	TIM_TimeBaseStructure_1.TIM_ClockDivision=TIM_CKD_DIV1; 
//	
//	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseStructure_1);//��ʼ����ʱ��14
//	
//	//��ʼ��TIM14 Channel1 PWMģʽ	 
//	TIM_OCInitStructure_1.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
// 	TIM_OCInitStructure_1.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitStructure_1.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
//	TIM_OC1Init(TIM14, &TIM_OCInitStructure_1);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

//	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
// 
//  TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPEʹ�� 
//	

// 	//gpiof9 tim14 
//										  
//										  
//}  

//void TIM13_PWM_Init(u32 arr,u32 psc)			//pf8
//{		 					 
//	//�˲������ֶ��޸�IO������
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);  	//TIM14ʱ��ʹ��    
////	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 	//ʹ��PORTFʱ��	
//	
//	GPIO_PinAFConfig(GPIOF,GPIO_PinSource8,GPIO_AF_TIM14); //GPIOF9����Ϊ��ʱ��14
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           //GPIOF
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
//	GPIO_Init(GPIOF,&GPIO_InitStructure);              //��ʼ��PF9
//	  
//	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
//	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
//	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
//	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
//	
//	TIM_TimeBaseInit(TIM13,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
//	
//	//��ʼ��TIM14 Channel1 PWMģʽ	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
//	TIM_OC1Init(TIM13, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

//	TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
// 
//  TIM_ARRPreloadConfig(TIM13,ENABLE);//ARPEʹ�� 
//	

// 
//										  
//}  





//void TIM4_PWM_Init(u32 arr,u32 psc)			//pd12
//{		 					 
//	//�˲������ֶ��޸�IO������
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM14ʱ��ʹ��    
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//ʹ��PORTFʱ��	
//	
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //GPIOF9����Ϊ��ʱ��14
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;           //GPIOF
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
//	GPIO_Init(GPIOD,&GPIO_InitStructure);              //��ʼ��PF9
//	  
//	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
//	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
//	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
//	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
//	
//	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
//	
//	//��ʼ��TIM14 Channel1 PWMģʽ	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
//	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

//	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
// 
//  TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ�� 
//	

// 
//										  
//}  

