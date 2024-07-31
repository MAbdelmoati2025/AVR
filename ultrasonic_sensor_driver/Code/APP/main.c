/******************************************************************************
 *
 * File Name: Main.c
 *
 * Created on: 15/10/2023
 *
 * Description:  ultrasonic sensor
 *
 * Author: Mohamed A. Abdelmoati
 *
 *******************************************************************************/

#include "../HAL/lcd.h"         // Include the LCD header file
#include <avr/io.h>             // Include AVR I/O library
#include "../HAL/Ultrasonic.h"  // Include the ultrasonic sensor header file

int main()
{
    float32 distance = 0;   // Initialize a variable to store the distance

    LCD_init();             // Initialize the LCD
    Ultrasonic_init();      // Initialize the ultrasonic sensor
    LCD_displayString("Distance=     Cm");  // Display a message on the LCD
    SREG |= (1 << 7);       // Enable global interrupts
    while (1)
    {
        distance = Ultrasonic_readDistance();  // Read the distance from the ultrasonic sensor
        LCD_moveCursor(0, 10);                 // Move the cursor to the specified position on the LCD

        if (distance >= 100)
        {
        	LCD_intgerToString(distance);      // Display the distance with one decimal place
        }
        else
        {
        	LCD_intgerToString(distance);      // Display the distance with one decimal place
            LCD_displayCharacter(' ');         // Display a space
        }
    }
}
