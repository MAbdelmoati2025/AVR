
#ifndef LCD_H_
#define LCD_H_

#include"../LIB/std_types.h"// Include the standard types header file.

#define LCD_DATA_BITS_MODE  8  // Set the data bits mode (8 bits or 4 bits).

#if ((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))
// Check if the data bits mode is not 4 bits or 8 bits, and raise an error if not.
#error ("LCD_DATA_BITS_MODE must be 4 bits or 8 bits")
#endif

#define LCD_RS_PORT_ID      PORTD_ID  // Define the RS (Register Select) pin's port ID.
#define LCD_RS_PIN_ID       PIN4_ID   // Define the RS (Register Select) pin's ID.

#define LCD_E_PORT_ID       PORTD_ID  // Define the E (Enable) pin's port ID.
#define LCD_E_PIN_ID        PIN5_ID   // Define the E (Enable) pin's ID.

#define LCD_DATA_PORT_ID    PORTA_ID  // Define the port used for data communication.

#if (LCD_DATA_BITS_MODE == 4)
// If using 4-bit data mode, define the individual data pins.
#define LCD_DB4_PIN_ID      PIN4_ID
#define LCD_DB5_PIN_ID      PIN5_ID
#define LCD_DB6_PIN_ID      PIN6_ID
#define LCD_DB7_PIN_ID      PIN7_ID
#endif

// Define common LCD commands.
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

void LCD_init(void);

void LCD_sendCommand(uint8 command);

void LCD_displayCharacter(uint8 character);

void LCD_dispalyString(const char *str);

void LCD_moveCursor(uint8 row, uint8 column);

void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *str);

void LCD_clearScreen(void);

void LCD_intgerToString(int data);

void LCD_defineCustomChar(uint8 location, const uint8 *pattern) ;
#endif /* LCD_H_ */
