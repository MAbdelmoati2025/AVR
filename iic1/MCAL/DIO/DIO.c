#include "DIO.h"
#include <avr/io.h>


//	For Certain Bit

void Set_PinDir (GroupName_t group, PIN_NO_t number, PinDir_t direction)	// Function to set direction of certain bit
{
	if(direction == OUTPUT)
	{
		switch (group)
		{
		case PORT_A:
			SET_BIT(DDRA,number);
			break;
		case PORT_B:
			SET_BIT(DDRB,number);
			break;
		case PORT_C:
			SET_BIT(DDRC,number);
			break;
		case PORT_D:
			SET_BIT(DDRD,number);
			break;
		}
	}
	else
	{
		switch (group)
		{
		case PORT_A:
			CLEAR_BIT(DDRA,number);
			break;
		case PORT_B:
			CLEAR_BIT(DDRB,number);
			break;
		case PORT_C:
			CLEAR_BIT(DDRC,number);
			break;
		case PORT_D:
			CLEAR_BIT(DDRD,number);
			break;
		}
	}
}

void Set_PinLevel (GroupName_t group, PIN_NO_t number, PinLevel_t level )	// Function to set level of certain bit
{
	if (level == HIGH)
	{
		switch (group)
		{
		case PORT_A:
			SET_BIT(PORTA,number);
			break;
		case PORT_B:
			SET_BIT(PORTB,number);
			break;
		case PORT_C:
			SET_BIT(PORTC,number);
			break;
		case PORT_D:
			SET_BIT(PORTD,number);
			break;
		}
	}
	else
	{
		switch (group)
		{
		case PORT_A:
			CLEAR_BIT(PORTA,number);
			break;
		case PORT_B:
			CLEAR_BIT(PORTB,number);
			break;
		case PORT_C:
			CLEAR_BIT(PORTC,number);
			break;
		case PORT_D:
			CLEAR_BIT(PORTD,number);
			break;
		}
	}
}

RET_VALUE_t Read_PinLevel (GroupName_t group, PIN_NO_t number)		// Function to read level of certain bit
{
	RET_VALUE_t ret;
	switch (group)
	{
	case PORT_A:
		ret = BIT_IS_SET(PINA,number);
		break;
	case PORT_B:
		ret = BIT_IS_SET(PINB,number);
		break;
	case PORT_C:
		ret = BIT_IS_SET(PINC,number);
		break;
	case PORT_D:
		ret = BIT_IS_SET(PIND,number);
		break;
	}
	return ret;
}

//	 For Group Of Pins

void Set_GroupDir (GroupName_t group, u8 value)							// Function to set direction of group of pins
{
	switch (group)
	{
	case PORT_A:
		DDRA = value;
		break;
	case PORT_B:
		DDRB = value;
		break;
	case PORT_C:
		DDRC = value;
		break;
	case PORT_D:
		DDRD = value;
		break;
	}
}

void Set_GroupLevel (GroupName_t group, u8 value)							// Function to set level of group of pins
{
	switch (group)
	{
	case PORT_A:
		PORTA = value;
		break;
	case PORT_B:
		PORTB = value;
		break;
	case PORT_C:
		PORTC = value;
		break;
	case PORT_D:
		PORTD = value;
		break;
	}
}
