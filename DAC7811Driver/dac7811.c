#include <msp430.h>
#include "dac7811.h"
/*
 * driver.c
 *
 *  Created on: 2017��5��12��
 *      Author: Tom
 */

/*******************************************
�������ƣ�SPI_Init()
��    �ܣ���ʼ��SPIͨ��
��    ������
����ֵ  ����
********************************************/
void SPI_Init(){
	P3DIR |= BIT2;					  		  //3.2��ΪƬѡ,3.3��ΪSPI SIMO
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
�������ƣ�send16Bit
��    �ܣ�����16λ���ݵ�7811,��λ��ǰ
��    ����unsigned int
����ֵ  ����
********************************************/
void send16Bit(unsigned int data16){
	//��8λ�ȷ�
	while(!(UCA0IFG & UCTXIFG));			//�ȴ����ͻ�������
	P3OUT &= ~BIT2;							//�͵�ƽд������
	UCA0TXBUF = (data16 >> 8);
	//��8λ��
	while(!(UCA0IFG & UCTXIFG));			//�ȴ����ͻ�������
	UCA0TXBUF = data16;
	P3OUT |= BIT2;							//�ߵ�ƽ����
}

/*******************************************
�������ƣ�loadAndUpdate
��    �ܣ�DAC�������
��    ����unsigned int data
����ֵ  ����
********************************************/
void loadAndUpdate(unsigned int data12){
	unsigned int data16 = LoadAndUpdate;
	data12 = 0x0FFF & data12;
	data16 = LoadAndUpdate | data12;
	send16Bit(data16);
}
/*******************************************
�������ƣ�clearOutputToZero
��    �ܣ�DAC�����Ϊ0
��    ������
����ֵ  ����
********************************************/
void clearOutputToZero(){
	send16Bit(DACout2zero);
}

/*******************************************
�������ƣ�clearOutputTomidScale
��    �ܣ�DAC�����Ϊһ��
��    ������
����ֵ  ����
********************************************/
void clearOutputTomidScale(){
	send16Bit(DACout2mid);
}
/*******************************************
�������ƣ�dataRideBack
��    �ܣ���ʼ��ReadBack
��    ������
����ֵ  ����
********************************************/
void dataRideBack(unsigned int data12){
	//1001
	unsigned int data16 = IniReadback;
	data12 = 0x0FFF & data12;
	data16 = IniReadback | data12;
	send16Bit(data16);
}





