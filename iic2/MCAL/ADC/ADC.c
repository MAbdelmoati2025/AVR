/*
 * ADC.c
 *
 *  Created on: Aug 25, 2021
 *      Author: Hello
 */
#include "ADC.h"

void ADC_Init(void)
{
 // AREF = AVcc
 ADMUX = (1<<REFS0);
 // ADC Enable and prescaler of 128

 ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}
u16 ADC_readChannel (u8 channel)
{
	// select the corresponding channel 0~7

	channel &= 0b00000111;  // AND operation with 7
	 ADMUX = (ADMUX & 0xF8)|channel;
	 // start single conversion
	 // write '1' to ADSC
	 ADCSRA |= (1<<ADSC);

	 // wait for conversion to complete
	 // ADSC becomes '0' again
	 while(ADCSRA & (1<<ADSC));
	 return (ADC);
	}
