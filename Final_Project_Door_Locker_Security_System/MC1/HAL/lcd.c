
#include <util/delay.h>            // Include the delay library for _delay_ms function.
#include "../MCAL/gpio.h"          // Include the GPIO header file.
#include "../HAL/lcd.h"            // Include the LCD header file.
#include "../LIB/common_macros.h"  // Include common macros for bit manipulation.

void LCD_init(void){
    // Initialize the LCD module.

    // Set the direction of RS and E pins as output.
    GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);

    _delay_ms(20); // Wait for the LCD to power up.

#if (LCD_DATA_BITS_MODE == 4)
    // If using 4-bit data mode, set the direction of DB4, DB5, DB6, and DB7 pins as output.
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, PIN_OUTPUT);

    // Send initialization commands for 4-bit mode.
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

    // Set the LCD to 4-bit mode.
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#endif

#if (LCD_DATA_BITS_MODE == 8)
    // If using 8-bit data mode, set the direction of the data port as output.
    GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);

    // Send initialization command for 8-bit mode.
    LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#endif
    // Turn off the cursor.
    LCD_sendCommand(LCD_CURSOR_OFF);

    // Clear the screen.
    LCD_sendCommand(LCD_CLEAR_COMMAND);
}

void LCD_sendCommand(uint8 command){
    // Send a command to the LCD.

    // Set RS pin to low to indicate a command.
    GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
    _delay_ms(1);

    // Set E pin to high to enable the LCD.
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
    _delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
    // If using 4-bit data mode, send each nibble separately.

    // Send the high nibble (4 bits) of the command.
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command, 4));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command, 5));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command, 6));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command, 7));
    _delay_ms(1);

    // Clear the E pin to disable the LCD.
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
    _delay_ms(1);

    // Set E pin to high to enable the LCD again.
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
    _delay_ms(1);

    // Send the low nibble (4 bits) of the command.
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command, 0));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command, 1));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command, 2));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command, 3));
    _delay_ms(1);

    // Clear the E pin to disable the LCD.
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
    _delay_ms(1);

#endif

#if (LCD_DATA_BITS_MODE == 8)
    // If using 8-bit data mode, send the entire byte as a command.

    // Send the entire command byte to the data port.
    GPIO_writePort(LCD_DATA_PORT_ID, command);
    _delay_ms(1);

    // Clear the E pin to disable the LCD.
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
    _delay_ms(1);

#endif
}

void LCD_displayCharacter(uint8 character){
    // Display a character on the LCD.

    // Set RS pin to high to indicate data (character).
    GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
    _delay_ms(1);

    // Set E pin to high to enable the LCD.
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
    _delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
    // If using 4-bit data mode, send each nibble separately.

    // Send the high nibble (4 bits) of the character.
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(character, 4));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(character, 5));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(character, 6));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(character, 7));
    _delay_ms(1);

    // Clear the E pin to disable the LCD.
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
    _delay_ms(1);

    // Set E pin to high to enable the LCD again.
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
    _delay_ms(1);

    // Send the low nibble (4 bits) of the character.
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(character, 0));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(character, 1));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(character, 2));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(character, 3));
    _delay_ms(1);

    // Clear the E pin to disable the LCD.
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
    _delay_ms(1);

#endif

#if (LCD_DATA_BITS_MODE == 8)
    // If using 8-bit data mode, send the entire character byte as data.

    // Send the entire character byte to the data port.
    GPIO_writePort(LCD_DATA_PORT_ID, character);
    _delay_ms(1);

    // Clear the E pin to disable the LCD.
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
    _delay_ms(1);

#endif
}

void LCD_dispalyString(const char *str){
    // Display a string on the LCD.

    while (*str != '\0') {
        // Iterate through each character in the string and display it.
        LCD_displayCharacter(*str++);
    }
}

void LCD_moveCursor(uint8 row, uint8 column){
    // Move the cursor to a specific row and column on the LCD.

    uint8 LCD_CursorPosition = 0;

    // Calculate the cursor position based on the row and column.
    switch (row) {
        case 0:
            LCD_CursorPosition = column + (0x00);
            break;
        case 1:
            LCD_CursorPosition = column + (0x40);
            break;
        case 2:
            LCD_CursorPosition = column + (0x10);
            break;
        case 3:
            LCD_CursorPosition = column + (0x50);
            break;
    }

    // Send the command to set the cursor position.
    LCD_sendCommand(LCD_CursorPosition | 0x80);
}

void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *str){
    // Display a string at a specific row and column on the LCD.
    LCD_moveCursor(row, col);
    LCD_dispalyString(str);
}

void LCD_clearScreen(void){
    // Clear the entire LCD screen.
    LCD_sendCommand(LCD_CLEAR_COMMAND);
}

void LCD_intgerToString(int data){
    // Convert an integer to a string and display it on the LCD.
    char buff[16];
    itoa(data, buff, 10);
    LCD_dispalyString(buff);
}
