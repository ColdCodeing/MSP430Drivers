#include <msp430.h> 

#include "tlc5615driver.h"
/*
 * main.c
 */
void main(void) {

	WDTCTL = WDTPW + WDTHOLD;
	GPIO_init();
	while(1){
		sendData(1023);
	}
}
