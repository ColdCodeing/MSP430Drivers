/*
 * tlc5615.c
 *
 *  Created on: 2017��6��29��
 *      Author: 10352
 */

#include <msp430F5529.h>
#include "tlc5615driver.h"

/*
 * �������ݵĳ���,�빤����ʽ��Ӧ
 */

/*
 * Used GPIO
 * 3.0 as CS
 * 3.1 as SCLK
 * 3.2 as DOUT
 * */
void GPIO_init(void){
	P3DIR = BIT0 + BIT1 + BIT2;   //��ʼ��ʱ�䣬ʹ�ܣ����������ܽ�
}

/*
 * SPI communication protocol
 */
void sendData(unsigned int num){

	unsigned char i ;
	unsigned int data;

	#ifdef MODE0
		data = MASK & num;
		data <<= LeftShift;
   	#else
		data = MASK & num;
		data <<= LeftShift;
	#endif

	CS_SET;
	DOUT_CLR;
	for(i = 0; i < LENGTH; i ++){
		if((data & 0x8000) == 0x8000)   {
			DOUT_SET;
		}else{
			DOUT_CLR;
		}
		SCLK_SET;
		data <<= 1;
		SCLK_CLR;
	}
	CS_CLR;
	P3OUT &= ~BIT1;
}
