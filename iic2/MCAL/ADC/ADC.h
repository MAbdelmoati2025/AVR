/*
 * ADC.h
 *
 *  Created on: Aug 25, 2021
 *      Author: Hello
 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

#include "../../UTLIS/Common_Macros.h"
#include "../../UTLIS/Std_Types.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "../../MCAL/DIO/DIO.h"

/*******************FUNCTION DEF***********/

void ADC_Init(void); //function to intialize ADC

u16 ADC_readChannel (u8 channel); //function to read data from specific channel




#endif /* MCAL_ADC_ADC_H_ */
