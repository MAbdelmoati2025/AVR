/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the PWM driver
 *
 *******************************************************************************/

#include "../MCAL/pwm.h"
#include "gpio.h"
#include "avr/io.h"

void PWM_Timer0_Start(uint8 duty_cycle)
{
	GPIO_setupPinDirection(PORTB_ID,PIN3,PIN_OUTPUT);
	TCNT0 = 0;
	OCR0  =((float)duty_cycle/100)*255;
	TCCR0 =(1<<WGM00)|(1<<WGM01)|(1<<CS01)|(1<<COM01);
}
