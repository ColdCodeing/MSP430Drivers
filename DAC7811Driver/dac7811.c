#include <msp430.h>
#include "dac7811.h"
/*
 * driver.c
 *
 *  Created on: 2017年5月12日
 *      Author: Tom
 */

/*******************************************
函数名称：SPI_Init()
功    能：初始化SPI通信
参    数：无
返回值  ：无
********************************************/
void SPI_Init(){
	P3DIR |= BIT2;					  		  //3.2作为片选,3.3作为SPI SIMO
	P3SEL |= BIT3+BIT4;                       // P3.3,4 option select
	P2SEL |= BIT7;                            // P2.7 option select
	UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCA0CTL0 |= UCMST+UCSYNC+UCMSB;    // 3-pin, 8-bit SPI master
											  // Clock polarity high, MSB
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 = 0x16;                           // /2
	UCA0BR1 = 0;                              //
	UCA0MCTL = 0;                             // No modulation
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

/*******************************************
函数名称：send16Bit
功    能：发送16位数据到7811,高位在前
参    数：unsigned int
返回值  ：无
********************************************/
void send16Bit(unsigned int data16){
	//高8位先发
	while(!(UCA0IFG & UCTXIFG));			//等待发送缓冲区空
	P3OUT &= ~BIT2;							//低电平写入数据
	UCA0TXBUF = (data16 >> 8);
	//低8位后发
	while(!(UCA0IFG & UCTXIFG));			//等待发送缓冲区空
	UCA0TXBUF = data16;
	P3OUT |= BIT2;							//高电平锁存
}

/*******************************************
函数名称：loadAndUpdate
功    能：DAC更新输出
参    数：unsigned int data
返回值  ：无
********************************************/
void loadAndUpdate(unsigned int data12){
	unsigned int data16 = LoadAndUpdate;
	data12 = 0x0FFF & data12;
	data16 = LoadAndUpdate | data12;
	send16Bit(data16);
}
/*******************************************
函数名称：clearOutputToZero
功    能：DAC输出设为0
参    数：无
返回值  ：无
********************************************/
void clearOutputToZero(){
	send16Bit(DACout2zero);
}

/*******************************************
函数名称：clearOutputTomidScale
功    能：DAC输出设为一半
参    数：无
返回值  ：无
********************************************/
void clearOutputTomidScale(){
	send16Bit(DACout2mid);
}
/*******************************************
函数名称：dataRideBack
功    能：初始化ReadBack
参    数：无
返回值  ：无
********************************************/
void dataRideBack(unsigned int data12){
	//1001
	unsigned int data16 = IniReadback;
	data12 = 0x0FFF & data12;
	data16 = IniReadback | data12;
	send16Bit(data16);
}





