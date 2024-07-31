/******************************************************************************
 *
 * File Name: Timer.c
 *
 * Created on: 24/10/2023
 *
 * Description:  Drive Timer1
 *
 * Author: Mohamed A. Abdelmoati
 *
 *******************************************************************************/

#include "timer.h"
#include "../LIB/common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>
static volatile void(*g_callback_ptr) (void)=NULL_PTR;

ISR(TIMER1_COMPA_vect)
{
	if(g_callback_ptr != NULL_PTR)
	{
		(*g_callback_ptr)();
	}
}
ISR(TIMER1_OVF_vect)
{
	if(g_callback_ptr != NULL_PTR)
	{
		(*g_callback_ptr)();
	}
}
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCNT1=Config_Ptr->initial_value;
	OCR1A=Config_Ptr->compare_value;
	TCCR1A= (1<<FOC1A)|(1<<FOC1B);
	TCCR1B= (0xFF & Config_Ptr->prescaler);
	if(Config_Ptr->mode==NORMAL_MODE)
	{
		TCCR1A|= (Config_Ptr->mode);
		TIMSK|= (1<<TOIE1);
	}
	else if(Config_Ptr->mode==TIMER1_CTC_OCR1A)
	{
		TCCR1B|=(1<<WGM12);
		TIMSK|= (1<<OCIE1A);
	}
}

void Timer1_deInit(void)
{
	TCCR1B= CLK_STOP;
	TCNT1=0;
	OCR1A=0;
}

void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callback_ptr = (volatile void (*)(void))a_ptr;
}
