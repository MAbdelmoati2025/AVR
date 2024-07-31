/******************************************************************************
 *
 * File Name: Main.c
 *
 * Created on: 10/10/2023
 *
 * Description:  Fan Controller System
 *
 * Author: Mohamed A. Abdelmoati
 *
 *******************************************************************************/

// Include necessary libraries and header files
#include "../HAL/lm315.h"
#include "../HAL/lcd.h"
#include "../HAL/DCMOTOR.h"
#include "../mcal/pwm.h"

int main(void)
{
    // Initialize the LCD display and the DC motor
    LCD_RW();
    DcMotor_Init();

    // Configure the Analog to Digital Converter (ADC)
    ADC_ConfigType myConfig = { INTERNAL_2_56, ADC_PRE_8 };
    ADC_init(&myConfig);

    // Initialize the LCD display and show initial messages
    LCD_init();
    LCD_moveCursor(0, 3);
    LCD_displayString("FAN IS   ");
    LCD_moveCursor(1, 3);
    LCD_displayString("Temp =    C");

    // Start PWM Timer 0
    PWM_Timer0_Start(0);

    uint8 temp;

    while(1)
    {
        // Read temperature from LM35 sensor
        temp = LM35_getTemperature();
        LCD_moveCursor(1, 10);

        // Display the temperature on the LCD
        if(temp >= 100)
        {
            LCD_intgerToString(temp);
        }
        else
        {
            LCD_intgerToString(temp);
            LCD_displayCharacter(' ');
        }

        // Control the fan based on temperature
        if (temp < 30 && temp > 0)
        {
            LCD_moveCursor(0, 9);
            LCD_displayString(" OFF");
            DcMotor_Rotate(DCMOTOR_STOP, 0);
        }
        else if (temp >= 30 && temp < 60)
        {
            LCD_moveCursor(0, 9);
            LCD_displayString(" ON");
            DcMotor_Rotate(DCMOTOR_CW, 25);
            LCD_moveCursor(0, 11);
        }
        else if (temp >= 60 && temp < 90)
        {
            LCD_moveCursor(0, 9);
            LCD_displayString(" ON");
            DcMotor_Rotate(DCMOTOR_CW, 50);
            LCD_displayCharacter(' ');
        }
        else if (temp >= 90 && temp < 120)
        {
            LCD_moveCursor(0, 9);
            LCD_displayString(" ON");
            DcMotor_Rotate(DCMOTOR_CW, 75);
            LCD_displayCharacter(' ');
        }
        else if (temp >= 120)
        {
            LCD_moveCursor(0, 9);
            LCD_displayString(" ON");
            DcMotor_Rotate(DCMOTOR_CW, 100);
            LCD_displayCharacter(' ');
        }
    }
}
