/******************************************************************************
 *
 * File Name: ADC.c
 *
 * Created on: 10/10/2023
 *
 * Description: ADC (Analog to Digital Converter) Configuration and Read Functions
 *
 * Author: Mohamed A. Abdelmoati
 *
 *******************************************************************************/
#include "avr/io.h"
#include "../MCAL/adc.h"
#include "../LIB/common_macros.h"
#include "../MCAL/gpio.h"

// Function to initialize the ADC with the specified configuration
void ADC_init(const ADC_ConfigType *Config_Ptr)
{
    // Enable the ADC module
    SET_BIT(ADCSRA, ADEN);

    // Configure the reference voltage
    if (Config_Ptr->ref_volt == AREF)
    {
        CLEAR_BIT(ADMUX, REFS0);
        CLEAR_BIT(ADMUX, REFS1);
    }
    else if (Config_Ptr->ref_volt == AVCC)
    {
        SET_BIT(ADMUX, REFS0);
        CLEAR_BIT(ADMUX, REFS1);
    }
    else if (Config_Ptr->ref_volt == INTERNAL_2_56)
    {
        SET_BIT(ADMUX, REFS0);
        SET_BIT(ADMUX, REFS1);
    }
    else
    {
        // Handle other cases or errors if needed
    }

    // Configure the ADC prescaler
    if (Config_Ptr->prescaler == ADC_PRE_2)
    {
        ADCSRA = (ADCSRA & 0xF8) | 0x01;
    }
    else if (Config_Ptr->prescaler == ADC_PRE_4)
    {
        ADCSRA = (ADCSRA & 0xF8) | 0x02;
    }
    else if (Config_Ptr->prescaler == ADC_PRE_8)
    {
        ADCSRA = (ADCSRA & 0xF8) | 0x03;
    }
    else if (Config_Ptr->prescaler == ADC_PRE_16)
    {
        ADCSRA = (ADCSRA & 0xF8) | 0x04;
    }
    else if (Config_Ptr->prescaler == ADC_PRE_32)
    {
        ADCSRA = (ADCSRA & 0xF8) | 0x05;
    }
    else if (Config_Ptr->prescaler == ADC_PRE_64)
    {
        ADCSRA = (ADCSRA & 0xF8) | 0x06;
    }
    else if (Config_Ptr->prescaler == ADC_PRE_128)
    {
        ADCSRA = (ADCSRA & 0xF8) | 0x07;
    }
    else
    {
        // Handle other cases or errors if needed
    }
}

// Function to read the ADC value from the specified channel
uint16 ADC_readChannel(uint8 ch_num)
{
    // Configure the ADC multiplexer to select the desired channel
    ADMUX = (ADMUX & 0xF8) | (ch_num & 0x07);

    // Start the ADC conversion
    ADCSRA |= (1 << ADSC);

    // Wait for the conversion to complete
    while (ADCSRA & (1 << ADSC));

    // Return the ADC result
    return ADC;
}
