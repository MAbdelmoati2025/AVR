

#include "avr/io.h"
#include <util/delay.h>
#include "Keypad.h"
#include "../MCAL/gpio.h"
#include "../LIB/common_macros.h"

#ifndef STANDARD_KEYPAD

#if(NUM_OF_COLUMNS == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);

#elif(NUM_OF_COLUMNS == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);

#endif

#endif
uint8 KEYPAD_getPressedKey(void){
	uint8 row , col ;
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+1,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+2,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+3,PIN_INPUT);

	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+1,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+2,PIN_INPUT);
#if(NUM_OF_COLUMNS == 4)
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+3,PIN_INPUT);
#endif
	while(1){
		for(row=0 ; row < NUM_OF_ROWS ; row++){

			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_OUTPUT);
			GPIO_writePin(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID,KEYPAD_BUTTON_PRESSED);

			for(col = 0 ; col <NUM_OF_COLUMNS ;col++){
				if(GPIO_readPin(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+col) == KEYPAD_BUTTON_PRESSED)
				{
#if (NUM_OF_COLUMNS == 3)
#ifdef STANDARD_KEYPAD
					return ((row*NUM_OF_COLUMNS)+col+1);
#else
					return KEYPAD_4x3_adjustKeyNumber((row*NUM_OF_COLUMNS)+col+1);
#endif
#elif (NUM_OF_COLUMNS == 4)
#ifdef STANDARD_KEYPAD
					return ((row*NUM_OF_COLUMNS)+col+1);
#else
					return KEYPAD_4x4_adjustKeyNumber((row*NUM_OF_COLUMNS)+col+1);
#endif
#endif
				}
			}
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_INPUT);
			_delay_ms(5);
		}
	}
}
#ifndef STANDARD_KEYPAD
#if(NUM_OF_COLUMNS == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number){
	uint8 adjustedKey=0;
	switch(button_number){
	case 1: adjustedKey = 7;
	break;
	case 2: adjustedKey = 8;
	break;
	case 3: adjustedKey = 9;
	break;
	case 4: adjustedKey = '%'; // ASCII Code of %
	break;
	case 5: adjustedKey = 4;
	break;
	case 6: adjustedKey = 5;
	break;
	case 7: adjustedKey = 6;
	break;
	case 8: adjustedKey = '*'; /* ASCII Code of '*' */
	break;
	case 9:adjustedKey = 1;
	break;
	case 10: adjustedKey = 2;
	break;
	case 11: adjustedKey = 3;
	break;
	case 12:adjustedKey  = '-'; /* ASCII Code of '-' */
	break;
	case 13: adjustedKey = 13;  /* ASCII of Enter */
	break;
	case 14:adjustedKey  = 0;
	break;
	case 15: adjustedKey = '='; /* ASCII Code of '=' */
	break;
	case 16: adjustedKey = '+'; /* ASCII Code of '+' */
	break;
	default:adjustedKey= button_number;
	break;
	}
	return adjustedKey;
}
#elif(NUM_OF_COLUMNS == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
{
	uint8 adjustedKey = 0;
	switch(button_number)
	{
		case 10: adjustedKey= '*'; // ASCII Code of *
				 break;
		case 11: adjustedKey= 0;
				 break;
		case 12: adjustedKey = '#'; // ASCII Code of #
				 break;
		default: adjustedKey= button_number;
				break;
	}
	return keypad_button;
}
#endif
#endif
