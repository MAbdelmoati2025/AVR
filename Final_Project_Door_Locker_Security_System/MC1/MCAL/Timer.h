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
#ifndef TIMER_H_
#define TIMER_H_
#include "../LIB/std_types.h"

//This is the most configurable drive around Timer1.
//I will complete this drive and add Timer0 and Timer2 but the requirement in this project is Timer1 only
//but I am using timer0 drive temporarily from driver (fan controller project)

/***********************  Types Declaration   ***************************/

/**********************************************************/

/***************************IMPORTANT TO SETTING THIS**********/
//TIMER1_OUTPUT_MODE output_mode = TIMER1_OC1_NON_INVERTING_or_CLEAR;
/**************************************************************/
typedef enum
{
	TIMER1_OC1_DISCONNECTED,
	TIMER1_OC1_TOGGLE,
	TIMER1_OC1_NON_INVERTING_or_CLEAR,
	TIMER1_OC1_INVERING_or_SET,

}TIMER1_OUTPUT_MODE;

typedef enum
{
	CLK_STOP,
	CLK_1,
	CLK_8,
	CLK_64,
	CLK_256,
	CLK_1024,
}Timer1_Prescaler;

typedef enum
{
	NORMAL_MODE,
	TIMER1_PWM_PHASE_CORRECT_8BIT,
	TIMER1_PWM_PHASE_CORRECT_9BIT,
	TIMER1_PWM_PHASE_CORRECT_10BIT,
	TIMER1_CTC_OCR1A,
	TIMER1_FAST_PWM_8BIT,
	TIMER1_FAST_PWM_9BIT,
	TIMER1_FAST_PWM_10BIT,
	TIMER1_PWM_PHASE_FREQUANCY_CORRECT_ICR1,
	TIMER1_PWM_PHASE_FREQUANCY_CORRECT_OCR1A,
	TIMER1_PWM_PHASE_CORRECT_ICR1,
	TIMER1_PWM_PHASE_CORRECT_OCR1A,
	TIMER1_CTC_ICR1,
	TIMER1_FAST_PWM_ICR1,
	TIMER1_FAST_PWM_OCR1A,

}Timer1_Mode;


typedef struct {
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
	uint16 initial_value;
	uint16 compare_value; // it will be used in compare mode only.
} Timer1_ConfigType;





void Timer1_init(const Timer1_ConfigType *Config_Ptr);

void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));



#endif /* TIMER1_H_ */
