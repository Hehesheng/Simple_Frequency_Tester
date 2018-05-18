#include "GPIO.h"
/////////////////////////////////////////////////
//ͨ����GPIO��ʼ������
//�迥��Ʒ
/////////////////////////////////////////////////

/////////////////////////////////////////////////
//���Լ��������壬ʾ�����£�
#define   GPIOA_NEED			1
#define 	GPIOA_Pin 			GPIO_Pin_2|GPIO_Pin_3						//����ʹ�õ�����
#define	  GPIOA_Mode 			GPIO_Mode_OUT						//����˿�ģʽ��ͨ���������λ״̬�����롢���ù���ģʽ��ģ������ģʽ
#define   GPIOA_OType			GPIO_OType_PP						//����������ͣ�����ģʽ��pp������©��od�� 
#define   GPIOA_Speed			GPIO_Speed_100MHz				//��������ٶȣ�2/25/50/100��
#define		GPIOA_PuPd			GPIO_PuPd_UP						//����IO�ڵ�����������NOPULL��UP��DOWN��
/////////////////////////////////////////////////

void GPIO_UNIVERSAL_SET (void)
{
//	GPIO_InitTypeDef	GPIOA_InitStructure
	
//ʱ��ʹ������������
#if GPIOA_NEED
	GPIO_InitTypeDef  GPIOA_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//���������GPIOA����ʹ��GPIOAʱ��
#endif 	

#if GPIOB_NEED
	GPIO_InitTypeDef  GPIOB_InitStructure;	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//���������GPIOB����ʹ��GPIOBʱ��
#endif 	
	
#if GPIOC_NEED
	GPIO_InitTypeDef  GPIOC_InitStructure;		
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//���������GPIOC����ʹ��GPIOCʱ��

#endif 
	
#if GPIOD_NEED
	GPIO_InitTypeDef  GPIOD_InitStructure;	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//���������GPIOD����ʹ��GPIODʱ��

#endif 

#if GPIOE_NEED
	GPIO_InitTypeDef  GPIOE_InitStructure;	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//���������GPIOE����ʹ��GPIOEʱ��

#endif 

#if GPIOF_NEED
	GPIO_InitTypeDef  GPIOF_InitStructure;	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//���������GPIOF����ʹ��GPIOFʱ��

#endif 	

#if GPIOG_NEED
	GPIO_InitTypeDef  GPIOG_InitStructure;	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//���������GPIOF����ʹ��GPIOFʱ��

#endif 

//GPIO_Init������д��

#if GPIOA_NEED	//���������GPIOA����ִ�б���
  GPIOA_InitStructure.GPIO_Pin = GPIOA_Pin;
  GPIOA_InitStructure.GPIO_Mode = GPIOA_Mode;
	#ifdef	GPIOA_OType
  GPIOA_InitStructure.GPIO_OType = GPIOA_OType;
	#endif
  GPIOA_InitStructure.GPIO_Speed = GPIOA_Speed;
  GPIOA_InitStructure.GPIO_PuPd = GPIOA_PuPd;
  GPIO_Init(GPIOA, &GPIOA_InitStructure);
#endif

#if GPIOB_NEED	//���������GPIOB����ִ�б���
  GPIOB_InitStructure.GPIO_Pin = GPIOB_Pin;
  GPIOB_InitStructure.GPIO_Mode = GPIOB_Mode;
	#ifdef	GPIOB_OType
  GPIOB_InitStructure.GPIO_OType = GPIOB_OType;
	#endif
  GPIOB_InitStructure.GPIO_Speed = GPIOB_Speed;
  GPIOB_InitStructure.GPIO_PuPd = GPIOB_PuPd;
  GPIO_Init(GPIOB, &GPIOB_InitStructure);
#endif

#if GPIOC_NEED	//���������GPIOC����ִ�б���
  GPIOC_InitStructure.GPIO_Pin = GPIOC_Pin;
  GPIOC_InitStructure.GPIO_Mode = GPIOC_Mode;
	#ifdef	GPIOC_OType
  GPIOC_InitStructure.GPIO_OType = GPIOC_OType;
	#endif
  GPIOC_InitStructure.GPIO_Speed = GPIOC_Speed;
  GPIOC_InitStructure.GPIO_PuPd = GPIOC_PuPd;
  GPIO_Init(GPIOC, &GPIOC_InitStructure);
#endif

#if GPIOD_NEED	//���������GPIOD����ִ�б���
  GPIOD_InitStructure.GPIO_Pin = GPIOD_Pin;
  GPIOD_InitStructure.GPIO_Mode = GPIOD_Mode;
	#ifdef	GPIOD_OType
  GPIOD_InitStructure.GPIO_OType = GPIOD_OType;
	#endif
  GPIOD_InitStructure.GPIO_Speed = GPIOD_Speed;
  GPIOD_InitStructure.GPIO_PuPd = GPIOD_PuPd;
  GPIO_Init(GPIOD, &GPIOD_InitStructure);
#endif

#if GPIOE_NEED	//���������GPIOE����ִ�б���
  GPIOE_InitStructure.GPIO_Pin = GPIOE_Pin;
  GPIOE_InitStructure.GPIO_Mode = GPIOE_Mode;
	#ifdef	GPIOE_OType
  GPIOE_InitStructure.GPIO_OType = GPIOE_OType;
	#endif
  GPIOE_InitStructure.GPIO_Speed = GPIOE_Speed;
  GPIOE_InitStructure.GPIO_PuPd = GPIOE_PuPd;
  GPIO_Init(GPIOE, &GPIOE_InitStructure);
#endif

#if GPIOF_NEED	//���������GPIOF����ִ�б���
  GPIOF_InitStructure.GPIO_Pin = GPIOF_Pin;
  GPIOF_InitStructure.GPIO_Mode = GPIOF_Mode;
	#ifdef	GPIOF_OType
  GPIOF_InitStructure.GPIO_OType = GPIOF_OType;
	#endif
  GPIOF_InitStructure.GPIO_Speed = GPIOF_Speed;
  GPIOF_InitStructure.GPIO_PuPd = GPIOF_PuPd;
  GPIO_Init(GPIOF, &GPIOF_InitStructure);
#endif

#if	GPIOG_NEED	//���������GPIOG����ִ�б���
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






