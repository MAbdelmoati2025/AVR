#include "LCD.h"
#include <avr/delay.h>
#include <stdio.h>
/**************************************************************************************************/
/****************************************Function Definition***************************************/

void LCD_Init (void)				// Function to initialize the LCD
{
	Set_GroupDir (LCD_DATA_PORT_DIR,0xFF);			//Set PORTC as o/p port
	LCD_CTRL_PORT_DIR = (1<<EN) | (1<<RS) | (1<<RW);//Set RS, RW, E pins as o/p port
	// OR  Set_GroupDir (LCD_CTRL_PORT,0x6F);
	_delay_ms(50); 								//Delay 50ms before function initialization
	Send_CMD (TWO_LINE_LCD_EIGHT_BIT_MODE);		//Set LCD mode as 8-bit mode, 2-lines, 5*8 Dots
	_delay_ms(1);
	Send_CMD (CURSOR_OFF);						//Choose Cursor as off
	_delay_ms(1);
	Send_CMD (CLEAR_COMMAND);					//Clear LCD at initialization
	_delay_ms(2);
}

void Send_CMD (u8 cmd)				// Function to send commands to LCD
{
	CLEAR_BIT(LCD_CTRL_PORT, RS);	//Send RS Pin = 0 (Command Instruction)
	CLEAR_BIT(LCD_CTRL_PORT, RW);	//Send RW Pin = 0 (Write Mood)
	_delay_ms(1);					//Delay 40ns until Enable Start
	SET_BIT(LCD_CTRL_PORT, EN);		//Send E Pin = 1 (Enable LCD)
	_delay_ms(1);					//Delay 1500ns until Enable Start
	LCD_DATA_PORT = cmd; 			//Send command through data pins
	_delay_ms(1);					//Delay 10ns until data sending is finished
	CLEAR_BIT(LCD_CTRL_PORT, EN);	//Send E Pin = 0 (Disable LCD)
}

void Send_DATA (u8 data)			// Function to send data to LCD
{
	SET_BIT(LCD_CTRL_PORT, RS);		//Send RS Pin = 1 (Command Instruction)
	CLEAR_BIT(LCD_CTRL_PORT, RW);	//Send RW Pin = 0 (Write Mood)
	_delay_ms(1);					//Delay 40ns until Enable Start
	SET_BIT(LCD_CTRL_PORT, EN);		//Send E Pin = 1 (Enable LCD)
	_delay_ms(1);					//Delay 1500ns until Enable Start
	LCD_DATA_PORT = data; 			//Send data through data pins
	_delay_ms(1);					//Delay 10ns until data sending is finished
	CLEAR_BIT(LCD_CTRL_PORT, EN);	//Send E Pin = 0 (Disable LCD)
}

void Display_Str (const u8 *str)	// Function to send data to LCD
{
	u8 i=0;
	while (str[i] != '\0')
	{
		Send_DATA (str[i]);
		i++;
	}
}

void Go_To_Row_Col (u8 row, u8 col)	// Function to move to certain column and row on LCD
{
	u8 Address;
	switch (row)
	{
	case 0:
		Address = col;
		break;
	case 1:
		Address = col + 0x40;
		break;
	case 2:
		Address = col + 0x10;
		break;
	case 3:
		Address = col + 0x50;
		break;
	}
	Send_CMD (Address | SET_CURSOR_LOCATION); //To move cursor to the Address location
}

void LCD_CLEAR (void)
{
	Send_CMD (CLEAR_COMMAND);
}

void Display_Str_Row_Col (u8 row, u8 col, const u8 *str)	//Display string at specified row and column
{
	Go_To_Row_Col (row,col);
	Display_Str (str);
}

void Integer_TO_String (u8 value)	// Display certain integer value on screen
{
	u8 number_str[30];
	itoa (value, number_str, 10);
	Display_Str (number_str);
}
