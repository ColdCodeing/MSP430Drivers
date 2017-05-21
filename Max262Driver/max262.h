
#ifndef _MAX262_DRIVER_H
#define _MAX262_DRIVER_H

//=================================头文件=============================//

#include "msp430f5529.h"


//========================频率、Q值计算所需常量========================//
#define uchar unsigned char
#define PI 3.1415926

//模式
#define MODE0 0
#define MODE1 1
#define MODE2 2
#define MODE3 3



//1K-20K截止频率,fclk频率

//uchar LPFclk[]={102,204,306,408,510,612,714,816,918,1020,1122,1224,1326,1428,1530,1632,1734,1836,1938,2040};
//
//uchar HPFclk[]={97,193,290,385,480,575,670,760,850,950,1050,1140,1240,1330,1420,1500,1610,1720,1830,1940};

//=================================引脚分配=============================//

//4位地址线
#define Addr0_H     P3OUT|=BIT3
#define Addr0_L     P3OUT&=~BIT3
#define Addr1_H     P1OUT|=BIT6
#define Addr1_L     P1OUT&=~BIT6
#define Addr2_H     P2OUT|=BIT7
#define Addr2_L     P2OUT&=~BIT7
#define Addr3_H     P6OUT|=BIT6
#define Addr3_L     P6OUT&=~BIT6

//两位数据线
#define Data0_H     P6OUT|=BIT5
#define Data0_L     P6OUT&=~BIT5
#define Data1_H     P3OUT|=BIT2
#define Data1_L     P3OUT&=~BIT2

//控制线
#define DataWR_H    P3OUT|=BIT4
#define DataWR_L    P3OUT&=~BIT4

//底层驱动函数
void MAX262_Init(void);
void WriteAddr(uchar addr);
void WriteData(uchar data);

//基本功能函数
void  SetAMode(uchar mode);//A通道设置函数
void  SetAF(uchar freq);
void  SetAQ(uchar Qvalue);
void  SetBMode(uchar mode);//B通道设置函数
void  SetBF(uchar freq);
void  SetBQ(uchar Qvalue);

uchar ComputeFN(uchar mode,long int fclk,long int f0);
uchar ComputeQN(uchar mode,float Q);

#endif
