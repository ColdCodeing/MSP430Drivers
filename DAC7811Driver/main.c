#include <msp430.h> 

#include "dac7811.h"
/*
 * main.c
 */
unsigned int i = 4000;
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    SPI_Init();
	P2REN |= BIT1;					//配置为内部上拉
	P2OUT |= BIT1;
	P2IES |= BIT1;					//下降沿触发
	P2IFG = 0x00;					//中断标志位清0
	P2IE |= BIT1;					//中端使能
	P1DIR |= 0x01;					// Set P1.0 to output direction
	_EINT();

    for(;;){
    	loadAndUpdate(i);
    	__delay_cycles(100);
    }
}


#pragma vector = PORT2_VECTOR     	//固定格式，声明中断向量地址，不能变
__interrupt void codeADD(void) 		//函数名，可以任意定义
{
	if(P2IFG & BIT1)
	{
		i += 200;
		P1OUT ^= BIT0;
	}
	P2IFG &= ~BIT1;
}
