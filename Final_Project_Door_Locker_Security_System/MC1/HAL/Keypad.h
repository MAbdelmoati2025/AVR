
#ifndef MYKEYPAD_H_
#define MYKEYPAD_H_

#include"../LIB/std_types.h"// Include the standard types header file.

#define NUM_OF_ROWS 					4
#define NUM_OF_COLUMNS    				4

#define KEYPAD_ROW_PORT_ID				PORTB_ID
#define KEYPAD_FIRST_ROW_PIN_ID			PIN0_ID

#define KEYPAD_COL_PORT_ID				PORTB_ID
#define KEYPAD_FIRST_COL_PIN_ID			PIN4_ID

#define KEYPAD_BUTTON_PRESSED			LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED			LOGIC_HIGH

uint8 KEYPAD_getPressedKey(void);

#endif /* MYKEYPAD_H_ */
