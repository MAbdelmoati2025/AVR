/******************************************************************************
 *
 * File Name: Buzzer.h
 *
 * Created on: 24/10/2023
 *
 * Description:  Drive Buzzer
 *
 * Author: Mohamed A. Abdelmoati
 *
 *******************************************************************************/
#ifndef buzzer_H_
#define buzzer_H_

#include "../LIB/std_types.h"


#define Buzzer_PORT_ID  PORTA_ID
#define Buzzer_PIN_ID	PIN0_ID


void buzzer_init(void);

void buzzer_ON(void);

void buzzer_OFF(void);

#endif
