#ifndef MCAL_DIO_H_
#define MCAL_DIO_H_

#include "../../UTLIS/Common_Macros.h"
#include "../../UTLIS/Std_Types.h"

typedef enum
{
	LOW,
	HIGH,
}PinLevel_t;

typedef enum
{
	INPUT,
	OUTPUT,
}PinDir_t;

typedef enum
{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D,
}GroupName_t;

typedef enum
{
	LOW_VALUE,
	HIGH_VALUE,
}RET_VALUE_t;

typedef enum
{
	Pin_0,
	Pin_1,
	Pin_2,
	Pin_3,
	Pin_4,
	Pin_5,
	Pin_6,
	Pin_7,
}PIN_NO_t;


//	For Certain Bit
void Set_PinDir (GroupName_t group, PIN_NO_t number, PinDir_t direction);	// Function to set direction of certain bit
void Set_PinLevel (GroupName_t group, PIN_NO_t number, PinLevel_t level );	// Function to set level of certain bit
RET_VALUE_t Read_PinLevel (GroupName_t group, PIN_NO_t number);				// Function to read level of certain bit

//	 For Group Of Pins
void Set_GroupDir (GroupName_t group, u8 value);							// Function to set direction of group of pins
void Set_GroupLevel (GroupName_t group, u8 value);							// Function to set level of group of pins
#endif
