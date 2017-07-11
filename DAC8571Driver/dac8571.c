/*
 * DAC8571.c
 *
 *  Created on: 2017��7��11��
 *      Author: mmOrz
 */

#include "DAC8571.h"
#include <msp430f5529.h>

void I2C_Start(void)    //I2C��ʼ�ź�
{
	 SDA_OUT;
	 SCL_L;
	 SDA_H;
	 __delay_cycles(1);
	 SCL_H;
	 __delay_cycles(1);
	 SDA_L;
	 __delay_cycles(1);
	 SCL_L;
	 __delay_cycles(1);
}

unsigned char testACK(void) {
	 SDA_IN;
	 __delay_cycles(1);
	 SCL_H;
	 __delay_cycles(1);
	 checkbit = (P1IN & BIT3) >> 4;
	 __delay_cycles(1);
	 SCL_L;
	 __delay_cycles(1);
	 return (checkbit);
}

void I2C_ACK(void)                //Ӧ���ź�
{
	 SDA_OUT;
	 SCL_L;
	 SDA_L;
	 __delay_cycles(1);
	 SCL_H;
	 __delay_cycles(1);
	 SCL_L;
	 __delay_cycles(1);
	 SDA_H;
}
void I2C_STOP(void)             //���������ź�
{
	 SCL_L;
	 __delay_cycles(1);
	 SDA_L;
	 __delay_cycles(1);
	 SCL_H;
	 __delay_cycles(1);
	 SDA_H;
	 __delay_cycles(1);
}
void I2C_WRITE(unsigned char data){
	 SDA_OUT;
	 unsigned char i;
	 for (i = 8; i > 0; i--){
		 if (data & 0x80){
			 SDA_H;           //��λ����д1
		 }else{
			 SDA_L;
		 }
		 SCL_H;
		 __delay_cycles(1);  //��������
		 SCL_L;
		 __delay_cycles(1);
		 data <<= 1;
	 }
}

void send8571Data(unsigned int data16){
	SCL_REN;
	SDA_REN;
	SCL_OUT;
	A0_OUT;
	unsigned char address = ADDR_8571 + ADDR_A0;
	unsigned char commond = WRITE_AND_LOAD;
	if(address & 0x04){			//�豸ѡ��
		A0_H;
	}else{
		A0_L;
	}

	I2C_Start();
	I2C_WRITE(address);		//1 0 0 1 1 A0 0 R/W
	I2C_ACK();
	I2C_WRITE(commond);
	I2C_ACK();
	I2C_WRITE(data16 >> 8);	//MSB first
	I2C_ACK();
	I2C_WRITE(data16);
	I2C_ACK();
	I2C_STOP();
}

















