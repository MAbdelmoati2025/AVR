 /******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: gpio.h
 *
 * Created on: ٢٥‏/٠٩‏/٢٠٢٣
 *
 * Description: types for AVR
 *
 * Author: Mohamed A.Abdelmoati
 *
 *******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "../LIB/STD_TYPEs.h"

#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

typedef enum
{
	LOW,
	HIGH,
}PinLevel_t;

typedef enum
{
	PORTA_ID,
	PORTB_ID,
	PORTC_ID,
	PORTD_ID,
}GroupName;

typedef enum
{
	PIN0_ID,
	PIN1_ID,
	PIN2_ID,
	PIN3_ID,
	PIN4_ID,
	PIN5_ID,
	PIN6_ID,
	PIN7_ID,
}PIN_NO;

typedef enum
{
	PIN_INPUT,
	PIN_OUTPUT,
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

void GPIO_setupPinDirection(GroupName port_num, PIN_NO pin_num, GPIO_PinDirectionType direction);

void GPIO_writePin(GroupName port_num, PIN_NO pin_num, uint8 value);

uint8 GPIO_readPin(GroupName port_num, PIN_NO pin_num);

void GPIO_setupPortDirection(GroupName port_num, GPIO_PortDirectionType direction);

void GPIO_writePort(GroupName port_num, uint8 value);

uint8 GPIO_readPort(GroupName port_num);

#endif /* GPIO_H_ */
