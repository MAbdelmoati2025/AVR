/******************************************************************************
 *
 * File Name: LM35.c
 *
 * Created on: 10/10/2023
 *
 * Description: Header file for DC Motor Control
 *
 * Author: Mohamed A. Abdelmoati
 *
 *******************************************************************************/

#include "lm315.h"               // Include LM35 temperature sensor interface
#include "../MCAL/adc.h"         // Include ADC (Analog to Digital Converter) interface

uint8 LM35_getTemperature(void)
{
    uint8 temp_value = 0;         // Variable to store the temperature value

    uint16 adc_value = 0;        // Variable to store the ADC reading

    adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);  // Read the LM35 sensor value

    // Calculate temperature using the LM35 formula
    // The formula is: (ADC_Value / ADC_Max_Value) * (Sensor_Max_Temperature / Sensor_Max_Voltage) * ADC_Reference_Voltage
    // where ADC_Value is the LM35 output, ADC_Max_Value is the maximum ADC value (e.g., 1023 for 10-bit ADC),
    // Sensor_Max_Temperature is the maximum temperature value (e.g., 100°C for LM35), Sensor_Max_Voltage is the voltage at which Sensor_Max_Temperature occurs (e.g., 1.0V for LM35),
    // and ADC_Reference_Voltage is the reference voltage for the ADC (e.g., 5.0V for most applications).

    temp_value = (uint8)(((float32)adc_value * SENSOR_MAX_TEMPERATURE * ADC_REF_VOLT_VALUE) / (ADC_MAXIMUM_VALUE * SENSOR_MAX_VOLT_VALUE));

    return temp_value;  // Return the temperature value
}
