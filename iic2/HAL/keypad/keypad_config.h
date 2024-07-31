

#ifndef HAL_KEYPAD_KEYPAD_CONFIG_H_
#define HAL_KEYPAD_KEYPAD_CONFIG_H_

#include <avr/io.h>

#define KEYPAD_PORT_DIR		DDRA
#define KEYPAD_PORT_OUT		PORTA
#define KEYPAD_PORT_IN		PINA

#define	N_ROW 4
#define N_COL 4

#endif
