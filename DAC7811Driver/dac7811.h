/*
 * driver.h
 *
 *  Created on: 2017Äê5ÔÂ12ÈÕ
 *      Author: Tom
 */

#ifndef DAC7811_H_
#define DAC7811_H_

#define	Default			0x0000
#define LoadAndUpdate 	0x1000
#define	IniReadback		0x2000
#define	DisDaisyChain	0x9000
#define RisEdgeLatch	0xA000
#define DACout2zero		0xB000
#define DACout2mid		0xC000


void SPI_Init();
void send16Bit(unsigned int data16);
void loadAndUpdate(unsigned int data12);
void clearOutputToZero();
void clearOutputTomidScale();
void dataReadBack(unsigned int data12);
#endif /* DAC7811_H_ */
