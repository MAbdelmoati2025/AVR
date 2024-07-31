/******************************************************************************
 *
 * File Name: PWM.h
 *
 * Created on: 10/10/2023
 *
 * Description: Header file for PWM (Pulse Width Modulation) Configuration and Control
 *
 * Author: Mohamed A. Abdelmoati
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "../LIB/STD_TYPEs.h"

// Function prototype for starting PWM on Timer0 with a specified duty cycle
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
