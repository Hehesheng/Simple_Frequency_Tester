#ifndef _TASK_H
#define _TASK_H
#include "sys.h"
#include "math.h"
#include "delay.h"
#include "usart.h"
#include "AD9959.h"
#include "ads1115.h"

//ad9959使用的通道
#define ad9959_ch0      2
#define ad9959_ch1      3

//task
#define Frequpdata_task     0x01
#define Freqscan_task       0x02

u32 string_2_val(u8 *string, u16 string_num);
void Freq_Updata(u32 freq);
double ADS_valget( u8 c );
void get_endval( void );

void draw_one_point(u16 x_val, u16 y_val);
u32 dB_2_xyCoordinate(double dB_dou, u16 n);
void draw_graph(double* dB_Data);

u32 translate_2_freq(u16 n);
double S_Ovalget ( void );
void S_DB_valget( void );
void S_O_valget( void );


#endif
