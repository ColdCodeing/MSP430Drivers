#include <msp430f5529.h>
#include "max262.h"
/*
 * main.c
 */
long int AF,BF;
uchar AFC,BFC,QAC,QBC;
float QA,QB;



void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	MAX262_Init();
//	AF=40000;
//	BF=40000;
//	QA=32;
//	QB=32;
    for(;;){
	  SetAMode(MODE0);
	  SetAF(ComputeFN(0, 1000000, 20000));
	  SetAQ(ComputeQN(0, 10));
	  SetBMode(0);
	  SetBF(ComputeFN(0, 1000000, 20000));
	  SetBQ(ComputeQN(0, 10));//高通测试成功
    }
}
