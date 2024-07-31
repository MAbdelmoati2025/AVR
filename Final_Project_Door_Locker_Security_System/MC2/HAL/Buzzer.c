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

#include "../MCAL/gpio.h"
#include "Buzzer.h"

#include <util/delay.h>

void buzzer_init()
{
	GPIO_setupPinDirection(Buzzer_PORT_ID, Buzzer_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(Buzzer_PORT_ID, Buzzer_PIN_ID,LOGIC_LOW);
}

void buzzer_ON()
{
	GPIO_writePin(Buzzer_PORT_ID, Buzzer_PIN_ID, LOGIC_HIGH);
}

void buzzer_OFF(void)
{
	GPIO_writePin(Buzzer_PORT_ID, Buzzer_PIN_ID,LOGIC_LOW);
}
