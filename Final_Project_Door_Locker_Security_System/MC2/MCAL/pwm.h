/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: Header file for the PWM driver
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_
#include "../LIB/std_types.h"
  // Include the standard types header file.

/*start pwm mode for timer0*/
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
