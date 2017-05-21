#include <msp430.h> 

#include "dac7811.h"
/*
 * main.c
 */
unsigned int i = 4000;
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    SPI_Init();
	P2REN |= BIT1;					//����Ϊ�ڲ�����
	P2OUT |= BIT1;
	P2IES |= BIT1;					//�½��ش���
	P2IFG = 0x00;					//�жϱ�־λ��0
	P2IE |= BIT1;					//�ж�ʹ��
	P1DIR |= 0x01;					// Set P1.0 to output direction
	_EINT();

    for(;;){
    	loadAndUpdate(i);
    	__delay_cycles(100);
    }
}


#pragma vector = PORT2_VECTOR     	//�̶���ʽ�������ж�������ַ�����ܱ�
__interrupt void codeADD(void) 		//���������������ⶨ��
{
	if(P2IFG & BIT1)
	{
		i += 200;
		P1OUT ^= BIT0;
	}
	P2IFG &= ~BIT1;
}
