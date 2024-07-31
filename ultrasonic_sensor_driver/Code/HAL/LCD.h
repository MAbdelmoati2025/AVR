/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "../LIB/std_types.h"

/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define LCD_DATA_BITS_MODE 8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))
#error "Number of Data bits should be equal to 4 or 8"
#endif

/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT_ID                 PORTB_ID // this way is used to make a static config so that I could be able to connect
                                              // the LCD on any pins without editing the code
#define LCD_RS_PIN_ID                  PIN0_ID

#define LCD_E_PORT_ID                  PORTB_ID
#define LCD_E_PIN_ID                   PIN1_ID

#define LCD_DATA_PORT_ID               PORTA_ID

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID

#endif

/* LCD Commands */
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
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *Str);
void LCD_moveCursor(uint8 row, uint8 col);
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *Str);
void LCD_intgerToString(int data);
void LCD_clearScreen(void);

/******************************************************************************************************************/

/*
 * Description:
 * Convert a floating-point number to a string with a specified number of decimal places.
 */
void LCD_floatToString(float data, char *buffer, uint8 decimalPlaces);

/*
 * Description:
 * Display a floating-point number with a specified number of decimal places on the screen.
 */
void LCD_displayFloat(float data, uint8 decimalPlaces);

#endif /* LCD_H_ */
