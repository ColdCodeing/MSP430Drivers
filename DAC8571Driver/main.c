#include <msp430.h> 
#include "DAC8571.h"
/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	unsigned i = 0x0;
    while(1){

    	send8571Data(i);
    	i += 6000;
    }
}
