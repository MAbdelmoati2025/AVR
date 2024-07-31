#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../HAL/LCD/LCD.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/ADC/ADC.h"
#include "../../MCAL/UART/UART.h"
#include "../../UTLIS/Std_Types.h"
#include "../../UTLIS/Common_Macros.h"

int main ()
{
    u16 adc_value;
    u8 Temperature;
    u16 ADC_Reading;
    u16 mv_Value;
    u16 LDR_Value;
    ADC_Init();
    USART_Init();
    LCD_Init();

    while (1)
    {
        adc_value = ADC_readChannel(1);        // read adc value at PA0
        Temperature = adc_value / 2.01;        // finding the temperature

        Go_To_Row_Col(0,0);  // Position for temperature display
        Display_Str("Temp:  ");  // Display "Temp: "
        Integer_TO_String(Temperature);  // Display temperature value
        Display_Str(" C     ");  // Display " C"

        if(Temperature > 30 && Temperature > 50)
        {
            USART_sendByte('H');    // Alarm On

        }
        else if(Temperature > 30)
        {
            USART_sendByte('F');    // Fan On
        }
        else
        {
            USART_sendByte('X');
        }


        // LDR Code LDR ADC conversion
        ADC_Reading = ADC_readChannel(0);
        mv_Value=(ADC_Reading * 5000)/256;
        LDR_Value = mv_Value * 3.8;


        if(LDR_Value < 400)
        {
            USART_sendByte('L');    // Led On
        }
        else
        {
            USART_sendByte('X');
        }

    }
    return 0;
}
