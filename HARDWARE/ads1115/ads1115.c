#include "sys.h"
#include "delay.h"
#include "ads1115.h"


/************************************
 *   ADDR---> GND
 *   VDD ---> 3.3V
 *   SCL ---> PE9
 *   SDA ---> PE10
 *   AINp=AIN0, AINn=GND
 ************************************/




//注意更改时钟使能！！！！!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#define SCL_SEL         RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);			//时钟线时钟使能
#define SCL_DDR_OUT  	 	PBout(8)	//设置时钟线为输出模式


#define SCL_H    	 			GPIO_SetBits(GPIOB,GPIO_Pin_8)			//时钟线拉高
#define SCL_L	 	   			GPIO_ResetBits(GPIOB,GPIO_Pin_8)						//时钟线拉低


#define SDA_SEL         RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);			//数据时钟使能
#define SDA_DDR_OUT   	PBout(9)		//数据线设置为输出
#define SDA_DDR_IN      PBin(9)		//数据线设置为读入

#define SDA_OUT 	 			GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_9)									//读取输出值	
#define SDA_IN         	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);									//读取输入值
#define SDA_H    	 			GPIO_SetBits(GPIOB,GPIO_Pin_9)			//数据线拉高
#define SDA_L	  	 			GPIO_ResetBits(GPIOB,GPIO_Pin_9)		//数据线拉低

#define TRUE   1
#define FALSE  0
#define DA 		-1					///??????

/*************ADDR Initial********************/
#define ADDRESS    ADDRESS_0   //ADDR PIN ->GND
#define ADDRESS_W  ADDRESS|0x00  //写地址
#define ADDRESS_R  ADDRESS|0x01    //读地址

/*************Config Initial*********************/
#define OS         OS_1
//#define MUX        MUX_4      //AINp=AIN0, AINn=GND
#define PGA        PGA_0      //FS=6.144V
#define DR         DR_7       //Data Rate = 860
#define COMP_QUE   COMP_QUE_3


unsigned int Config;
unsigned char Writebuff[4],Readbuff[3];
unsigned int Result[2]; 
int D_ADS; //转换的数字量
float VIN_DAS; //输入的电压值
unsigned char  t_DAS; 
int  Format[5]={0};  //转换的数字量转换成十进制

///*******************************************
//函数名称：delay
//功    能：延时约15us的时间
//参    数：无
//返回值  ：无
//********************************************/
//void Delay(void)
//{
//    unsigned char i;
//    
//    for(i = 0;i < 15;i++)
//     delay_us(5);
//}	

///******************延时1ms的时间*********************/
//void Delay_1ms(void)
//{
//	unsigned char i;
//	for(i = 150;i > 0;i--)	  delay_us(5);
//}


/*******************************************
函数名称：Start
功    能：完成IIC的起始条件操作
参    数：无
返回值  ：无
********************************************/
void Start(void)
{
        SCL_H;
        SDA_H;
        delay_us(15);
	SDA_L;
        delay_us(15);
	SCL_L;
        delay_us(15);
}

/*******************************************
函数名称：Stop
功    能：完成IIC的终止条件操作
参    数：无
返回值  ：无
********************************************/
void Stop(void)
{ 
        SDA_L;
        delay_us(15);
        SCL_H;
        delay_us(15);
	SDA_H;
        delay_us(15);
}


/*******************************************
函数名称：ACK
功    能：完成IIC的主机应答操作
参    数：无
返回值  ：无
********************************************/
void ACK(void)
{
        SDA_L;
				delay_us(5);delay_us(5);
        SCL_H;
        delay_us(15);
        SCL_L;
				delay_us(5);delay_us(5);
				SDA_H;
        delay_us(15);
}

/*******************************************
函数名称：NACK
功    能：完成IIC的主机无应答操作
参    数：无
返回值  ：无
********************************************/
void NACK(void)
{
	SDA_H;
	delay_us(5);delay_us(5);
	SCL_H;
	delay_us(15);
	SCL_L;
	delay_us(5);delay_us(5);
	SDA_L;   
	delay_us(15);       
}

/**********检查应答信号函数******************/
/*如果返回值为1则证明有应答信号，反之没有*/
/*******************************************
函数名称：Check
功    能：检查从机的应答操作
参    数：无
返回值  ：从机是否有应答：1--有，0--无
********************************************/
unsigned char Check(void)
{
    unsigned char slaveack;
    
    SDA_H;
		delay_us(5);delay_us(5);
    SCL_H;
		delay_us(5);delay_us(5);
	
    SDA_DDR_IN;
		delay_us(5);delay_us(5);
	
    slaveack = SDA_IN;
    SCL_L;
    delay_us(15);
    SDA_DDR_OUT;
	
    if(slaveack)  
		{			
			return FALSE;
		}
    else      
		{      
			return TRUE;
		}
}

/***************Write a Byte****************/
void Write_1_Byte(unsigned char DataByte)
{
	int i;

	for(i=0;i<8;i++)
	{
		if(DataByte&0x80) //if((DataByte<<i)&0x80)
		{			
		  SDA_H;
		}
		else
		{
		  SDA_L;
		}
		
    delay_us(15);
		SCL_H;
    delay_us(15);
    SCL_L;
    delay_us(15);
		
    DataByte <<= 1;
	}
     SDA_H;
     delay_us(5);delay_us(5);
}

/***************Write N Byte****************/
unsigned char Write_N_Byte(unsigned char *writebuffer,unsigned char n)
{
	int i;

	for(i=0;i<n;i++)
	{
		Write_1_Byte(*writebuffer);
		if(Check())//检查返回真时是有应答
		{
			writebuffer ++;
		}
		else
		{
			Stop();
		  return DA;
		}
	}
	
	Stop();
	return TRUE;
}

/***************Read a Byte****************/
unsigned char Read_1_Byte(void)
{
    unsigned char data=0,FLAG, i;
	
    for(i=0;i<8;i++)
    {
        
			SDA_H;
			delay_us(15);
      
			SCL_H;
			SDA_DDR_IN; //端口为输入
			delay_us(15);
      FLAG=SDA_IN;
      data <<= 1;
			
			if( FLAG)
				data |= 0x01;//如果这一位为零那就不用加，下一次左移时会自动变为0
			
			SDA_DDR_OUT;
      SCL_L;
      delay_us(15);
    }
    return data;
}

/***************Read N Byte****************/
void Read_N_Byte(unsigned int*readbuff,unsigned char n)
{
	unsigned char i;
	
	for(i=0;i<n;i++)
	{
		readbuff[i]=Read_1_Byte();
		
		if(i==n-1)
			NACK();  //不连续读字节，最后一个数据时停一下，
							//猜：AD的寄存器是一直有数据的，如果应答了直接中断，或许会让他的下一组数据只传了一部分，导致部分丢失，
							//毕竟停止操作的开始部分会拉高SCL如果应答了，那么AD就会开始传数据了
		else 
			ACK(); //连续读字节，给予应答
	}
	Stop();

}


/*****************初始化******************/
//////////////////////////////////////////////////////////需要main()调用的都在下面
void InitADS1115(int x)
{
	int MU;
    SCL_SEL;
    SDA_SEL;
    SCL_DDR_OUT;
    SDA_DDR_OUT;	
    SDA_H;//SCL不管了？
		switch(x)
    {
    case 0:MU=0x4000;break;
    case 1:MU=0x5000;break;
    case 2:MU=0x6000;break;		//AINp=AIN2, AINn=GND
    case 3:MU=0x7000;break;
    }
	
    Config = OS+MU+PGA+DR+COMP_QUE;
    Writebuff[0]=ADDRESS_W;
    Writebuff[1]=Pointer_1;
    Writebuff[2]=Config/256;
    Writebuff[3]=Config%256;
        
    Readbuff[0]=ADDRESS_W;
    Readbuff[1]=Pointer_0;
        
    Readbuff[2]=ADDRESS_R;
}

/***************Write a Word***********************/
void WriteWord(void)
{
     int t;
     Start();   //写入4个字节
     do
     {
          t=Write_N_Byte(Writebuff,4); 
     }while(t==0);
}

/***************Read Word***********************/
void ReadWord(void)
{
    int t;
    Start();  //写入2个字节
    do
    {
      t=Write_N_Byte(Readbuff,2);
    }while(t==0);

    Start();   //写入2个字节
    do
    {
      t=Write_N_Byte(&Readbuff[2],1);
    }while(t==0);
    
    Read_N_Byte(Result,2);  //读出2个字节

}

/***************ADS1115********************/
void ADS1115(int a)
{
    InitADS1115 (a);
    WriteWord();//用于修改AD的配置
		delay_ms(1);
    ReadWord();
		
    D_ADS=Result[0]*256+Result[1];  //转换的数字量：第一个元素乘以2的8次方变为高位
    t_DAS=0;
    ShowInt(D_ADS);    //转换的数字量转换成十进制，，，，，，意义何在！？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
    VIN_DAS=6.144*D_ADS/32768;  //输入的电压值
	//2的16次方为32768，所以6.144为AD的参考电压
}

//用递归方法将正整数x转换为10进制格式
void ShowInt(long int x)
{
	if(x)
	{
          Format[t_DAS]= x%10;
          t_DAS  ++;//设为全局是为了递归方便，t_DAS能直接传入下一层
          ShowInt(x/10);
	}
}
float ads_filter(int a)//中位值平均滤波法
{
  char count,i,j;
  char No=10;
  float value_buf[24],temp;
  float sum=0;
  for (count=0;count<No;count++)
  {
    delay_us(15);
    ADS1115(a);
    value_buf[count]=VIN_DAS;//转化后的电压值    
  }
	//下面是选择排序法
  for (j=0;j<No;j++)
  {
    for (i=0;i<No-j;i++)
    {
      if (value_buf[i]>value_buf[i+1])
      {
        temp=value_buf[i];
        value_buf[i]=value_buf[i+1];
        value_buf[i+1]=temp;
      }      
    }
  }
	
  //去掉一个最大值去掉一个最小值取平均。。。
  for (count=1;count<No-1;count++)
  {
    sum+=value_buf[count];
  }
  VIN_DAS=sum/(No-2);
	return VIN_DAS;
  //sum=sum*1.492-35.55;//-0.0016*sum*sum;
  //sum=(uint)sum;
  
}
