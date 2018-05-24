#include "task.h"
#define HMISendend		printf("\xff\xff\xff")
double DB_S[450]={0} ;
u8 DB_OK =0;
double O_S[450]={0} ;
u8 O_OK =0;
//	double  ch_A,ch_B;
//	double tanO,o,O,DB;
/*
 *@brief
 *@funna
 *@param
 *@retval
 */

/*
 *@brief 将字符串转化为数字
 *@funna string_2_val
 *@param 字符串(string), 长度(string_num)
 *@retval 数字
 */
u32 string_2_val(u8 *string, u16 string_num)
{
    u8 i;
    u32 result = 0;
    for(i = 1;i < string_num;i++)
    {
        result *= 10;
        result += string[i] - 48;
    }
    return result;
}

/*
 *@brief 改变输出的频率
 *@funna Freq_Updata
 *@param 频率(freq)
 *@retval NONE
 */
void Freq_Updata(u32 freq)
{
    u8 CFTW0_DATA[4] ={0x00,0x00,0x00,0x00};  //中间变量
    u8 channel_sele[1] = {0xC0};
    u32 Temp;            
    Temp=(u32)freq*8.589934592;    //将输入频率因子分为四个字节  4.294967296=(2^32)/500000000
    CFTW0_DATA[3]=(u8)Temp;
    CFTW0_DATA[2]=(u8)(Temp>>8);
    CFTW0_DATA[1]=(u8)(Temp>>16);
    CFTW0_DATA[0]=(u8)(Temp>>24);
    WriteData_AD9959(CSR_ADD,1,channel_sele,0);
    WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1); 
}

/*
 *@brief	利用ads1115测量指定通道输入，获取电压值
 *@funna	ADS_valget
 *@param	通道值
 *@retval	正常电压值
 */

double ADS_valget( u8 c )
{
	double  v_val;
	ads_filter(c);				//ads1115的初始化被包括进去了，需要取出来吗？
/*此处可能拖慢速度*/
	v_val=(double)VIN_DAS-1.5; 
	return v_val;
}

/*
 *@brief	根据获得的两路电压值，转换得电压增益，相移等数据
 *@funna	get_endval
 *@param	void
 *@retval	void
 */
//默认A是sin B是cos
void get_endval( void )
{
	double  ch_A,ch_B;
	double tanO,o,O,DB,A;
	ch_A=ADS_valget(0);
		printf("t0.txt=\"%.3lf\"",VIN_DAS);
	HMISendend;
	ch_B=ADS_valget(3);
		printf("t0.txt=\"%.3lf\"",VIN_DAS);
	HMISendend;
	tanO = ch_A/ch_B;
	o=atan (tanO);
	
	O=	(o *180.0)/3.1416;	//获得相移角度
	delay_us(10);
	A=((ch_A*2)*1000)/(sin(o)*1000);
	delay_us(10);
	DB=20*log10(fabs(A));		//获得相应电压增益

		printf("t12.txt=\"%.2lf\"",O);	//发送相移角
		HMISendend;
		printf("t11.txt=\"%.2lf\"",DB);	//发送电压增益值
		HMISendend;

}
//--------------------NEW!!!---------------------------------------
/*
 *幅频特性,像素:
 *10dB & 10: x=245, y=23
 *0dB & 10k: x=245, y=103
 *-40dB & 10K: x=245, y=422
 *-40dB & 10M: x=695, y=422
 *80像素10dB, 0.125dB/像素
 */

/*
 *@brief    在图上连接两点
 *@funna    draw_one_point
 *@param    点坐标(x_val, y_val)
 *@retval   NONE
 */
void draw_one_point(u16 x_val, u16 y_val)
{
    static u16 x_last, y_last;
    if(x_last == 0)
    {
        x_last = x_val;
        y_last = y_val;//第一次进入,记录第一个点
        return;
    }
    if(x_val == 0 && y_val == 0)
    {
        x_val = x_last;
        y_val = y_last;
    }
    printf("line %d,%d,%d,%d,RED",x_last, y_last, x_val, y_val);//画线指令
    HMISendend;
    x_last = x_val;
    y_last = y_val;
    return;
}

/*
 *@brief    根据dB获得对应坐标位置
 *@funna    dB_2_xyCoordinate
 *@param    倍数(dB_dou), 第n个点(n)
 *@retval   坐标, 写入32位数据中, 前16为x轴, 后16为y轴, 如果数据超出坐标轴, 返回0值
 */
u32 dB_2_xyCoordinate(double dB_dou, u16 n)
{
    u32 x_y_coordinate = 0;

	if(dB_dou>=-40 && dB_dou<=10 && n>=0 && n<=225)//控制数据在合理范围
    {
        x_y_coordinate = (4*n + 245)<<16;//写入x轴
        x_y_coordinate |= (u16)((10 - dB_dou)/0.125 + 23);//计算y轴和写入
    }
    return x_y_coordinate;
}

/*
 *@brief    根据数组在坐标上画图
 *@funna    draw_graph
 *@param    dB数组(*dB_Data)
 *@retval   NONE
 */
void draw_graph(double* dB_Data)
{
    u16 i;
    u32 xy_temp = 0;
    for(i = 0;i < 112;++i)
    {
        xy_temp = dB_2_xyCoordinate(dB_Data[i], i);
        draw_one_point((u16)(xy_temp>>16), (u16)xy_temp);
    }
    // printf("line 334,262,356,180,RED");
    // HMISendend;
    // printf("line 505,263,528,340,RED");
    // HMISendend;
}

/*
 *@brief    每一个点换成对应频率, freq = 9999.8e^(0.0153n)
 *@funna    translate_2_freq
 *@param    第n个点(n)
 *@retval   频率(freq)
 */
u32 translate_2_freq(u16 n)
{
    return (u32)(9999.8*exp(0.0153*4*n));
}

/*
 *@brief    每一个点换成对应频率, freq = 9999.8e^(0.0153n)
 *@funna    translate_2_freq
 *@param    第n个点(n)
 *@retval   频率(freq)
 */
//--------------------NEW!!!---------------------------------------






 /*
 *@brief	扫频模式下获得对应相移角
 *@funna	S_Ovalget
 *@param	void
 *@retval	double
 */
double S_Ovalget ( void )
{
	double ch_A,ch_B;
	double tanO,o,O;	
	ch_A=ADS_valget(0);
//		printf("t0.txt=\"%.3lf\"",VIN_DAS);
//	HMISendend;
	ch_B=ADS_valget(3);
//		printf("t0.txt=\"%.3lf\"",VIN_DAS);
	// HMISendend;
	
	tanO = ch_A/ch_B;
	o=atan (tanO);
	
	O=	(o *180.0)/3.1416;	//获得相移角度
	return O;
}
 /*
 *@brief	扫频模式下获得对应电压增益
 *@funna	S_DBvalget
 *@param	void
 *@retval	double
 */
double S_DBvalget ( void )
{
	double ch_A,ch_B;
	double tanO,o,DB;	
	ch_A=ADS_valget(0);
//		printf("t0.txt=\"%.3lf\"",VIN_DAS);
//	HMISendend;
	ch_B=ADS_valget(3);
//		printf("t0.txt=\"%.3lf\"",VIN_DAS);
//	HMISendend;
	
	tanO = ch_A/ch_B;
	o=atan (tanO);
	
	DB=20*log10((ch_A*2)/sin(o));		//获得相应电压增益
	return DB;
}
 /*
 *@brief	开始扫频，获得电压增益
 *@funna	S_DB_valget
 *@param	void
 *@retval	void
 */
void S_DB_valget( void )
{
	u16 i;
	u32 freq;
	for(i=0;i<=450;i++)
	{
	freq = translate_2_freq(i);
	Freq_Updata(freq);	
    if(freq < 50000 | freq > 300000)
    {
        delay_ms(1);
    }
    else
    {
        delay_us(15);
    }
	DB_S[i]	=	S_DBvalget();
	}
	DB_OK=1;
}
 /*
 *@brief	开始扫频，获得相移
 *@funna	S_O_valget
 *@param	void
 *@retval	void
 */
void S_O_valget( void )
{
	u16 i;
	u32 freq;
	for(i=0;i<=450;i++)
	{
	freq = translate_2_freq(i);
	Freq_Updata(freq);	
    if(freq < 50000)
    {
        delay_ms(1);
    }	
    else
    {
        delay_us(15);
    }
	O_S[i]	=	S_Ovalget();
	}
	O_OK=1;
}

/*guopi
 *起始:x=356, y=180
 *瓜皮点1:x=334, y=262
 *
 *起始;x=505, y=263
 *瓜皮点2:x=528, y=340
 */

