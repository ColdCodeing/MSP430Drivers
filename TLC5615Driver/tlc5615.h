/*
 * tlc5615.h
 *
 *  Created on: 2017年6月29日
 *      Author: 10352
 */

#ifndef TLC5615DRIVER_H_
#define TLC5615DRIVER_H_

/*
 * ADC的工作方式
 * MODE0 == 1	12-Bit Input Data Sequence
 * MODE0 == 0	16-Bit Input Data Sequence
 */
#define MODE0 0

#ifdef MODE0
	#define 			LENGTH 12
	#define				LeftShift 6
	#define 			MASK 0x3FF
#else
	#define 			LENGTH 16
	#define				LeftShift 2
	#define		 		MASK 0x3FFF
#endif

#define GPIO_DEFAULT 0

#ifdef GPIO_DEFAULT
	#define CS_SET			P3OUT |= BIT0
	#define CS_CLR			P3OUT &= ~BIT0
	#define SCLK_SET		P3OUT |= BIT1
	#define SCLK_CLR		P3OUT &= ~BIT1
	#define DOUT_SET		P3OUT |= BIT2
	#define DOUT_CLR		P3OUT &= ~BIT2
#else
	#error "GPIO have not been define"
#endif

void GPIO_init(void);
void sendData(unsigned int num);
/*
 * TODO 14bit send data method
 * */

#endif /* TLC5615DRIVER_H_ */
