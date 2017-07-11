/*
 * DAC8571.h
 *
 *  Created on: 2017年7月11日
 *      Author: mmOrz
 */

#ifndef DAC8571_H_
#define DAC8571_H_

unsigned char checkbit;
#define SCL_H   (P1OUT |= BIT3)     // P10.2为SCL
#define SCL_L   (P1OUT &= ~BIT3)
#define SDA_H   (P1OUT |= BIT2)     //p10.1为SDA
#define SDA_L   (P1OUT &= ~BIT2)
#define A0_H   	(P1OUT |= BIT4)		//A0
#define A0_L   	(P1OUT &= ~BIT4)
#define SCL_OUT  (P1DIR |= BIT3)
#define SDA_OUT  (P1DIR |= BIT2)
#define SDA_IN  (P1DIR &= ~ BIT2)
#define A0_OUT  (P1DIR |= BIT4)
#define SCL_REN (P1REN |= BIT3)
#define SDA_REN (P1REN |= BIT2)

#define WRITE_AND_LOAD 0x10
#define ADDR_8571 	0x98			//1 0 0 1 1 A0 0 R/W (A0 set as 0)
#define ADDR_A0 0x0						//define A0,address = ADDDR_8571 + A0,A0 = 0x0 or 0x04

void I2C_WRITE(unsigned char data);
void I2C_STOP(void);
void send8571Data(unsigned int data16);
void I2C_ACK(void);
unsigned char testACK(void);
void I2C_Start(void);

#endif /* DAC8571_H_ */
