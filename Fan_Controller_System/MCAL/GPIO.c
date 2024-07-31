/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Created on: ٢٥‏/٠٩‏/٢٠٢٣
 *
 * Description: Source file for the AVR GPIO driver
 *
 * Author: Mohamed A.Abdelmoati
 *
 *******************************************************************************/

#include "GPIO.h"
#include "../LIB/common_macros.h"
#include "avr/io.h"

void GPIO_setupPinDirection(GroupName port_num, PIN_NO pin_num, GPIO_PinDirectionType direction)
{

	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRA,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRA,pin_num);
			}
			break;
		case PORTB_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRB,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRB,pin_num);
			}
			break;
		case PORTC_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRC,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRC,pin_num);
			}
			break;
		case PORTD_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRD,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRD,pin_num);
			}
			break;
		}
	}
}

void GPIO_writePin(GroupName port_num, PIN_NO pin_num, uint8 value)
{
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as required */
		switch(port_num)
		{
		case PORTA_ID:
			if( value == LOGIC_HIGH)
			{
				SET_BIT(PORTA,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTA,pin_num);
			}
			break;
		case PORTB_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTB,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTB,pin_num);
			}
			break;
		case PORTC_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTC,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTC,pin_num);
			}
			break;
		case PORTD_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTD,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTD,pin_num);
			}
			break;
		}
	}
}

uint8 GPIO_readPin(GroupName port_num, PIN_NO pin_num)
{
	if((port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as required */
		switch(port_num)
		{
		case PORTA_ID:
			if(PINA & (1<<pin_num))
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case PORTB_ID:
			if(PINB & (1<<pin_num))
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case PORTC_ID:
			if(PINC & (1<<pin_num))
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		case PORTD_ID:
			if(PIND & (1<<pin_num))
			{
				return 1;
			}
			else
			{
				return 0;
			}
			break;
		}
	}
	return 0;
}

void GPIO_setupPortDirection(GroupName port_num, GPIO_PortDirectionType direction)
{
	if(port_num >= NUM_OF_PORTS)
	{
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			DDRA=direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}

void GPIO_writePort(GroupName port_num, uint8 value)
{
	if((port_num >= NUM_OF_PORTS))
	{

	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}

uint8 GPIO_readPort(GroupName port_num)
{
	if((port_num >= NUM_OF_PORTS))
	{

	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			return PORTA;
		case PORTB_ID:
			return PORTB;
		case PORTC_ID:
			return PORTC;
		case PORTD_ID:
			return PORTD;
		}
	}
	return 0;
}





























