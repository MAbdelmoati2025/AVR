/******************************************************************************
 *
 * File Name: ADC.h
 *
 * Created on: 10/10/2023
 *
 * Description: Header file for ADC (Analog to Digital Converter) Configuration
 *
 * Author: Mohamed A. Abdelmoati
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "../LIB/std_types.h"

#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

// Enumeration to define reference voltage sources for the ADC
typedef enum {
    AREF = 0,           // External reference voltage at AREF pin
    AVCC = 1,           // Voltage reference is the same as AVCC
    INTERNAL_2_56 = 3  // Internal reference voltage at 2.56V
} ADC_ReferenceVoltage;

// Enumeration to define prescaler values for the ADC
typedef enum {
    ADC_PRE_2 = 0,    // Division factor of 2
    ADC_PRE_4 = 2,    // Division factor of 4
    ADC_PRE_8 = 3,    // Division factor of 8
    ADC_PRE_16 = 4,   // Division factor of 16
    ADC_PRE_32 = 5,   // Division factor of 32
    ADC_PRE_64 = 6,   // Division factor of 64
    ADC_PRE_128 = 7   // Division factor of 128
} ADC_Prescaler;

// Structure to hold ADC configuration
typedef struct {
    ADC_ReferenceVoltage ref_volt; // Reference voltage source
    ADC_Prescaler prescaler;      // ADC prescaler value
} ADC_ConfigType;

extern ADC_ConfigType ADC_Config;

// Function to initialize the ADC with the specified configuration
void ADC_init(const ADC_ConfigType *Config_Ptr);

// Function to read the ADC value from the specified channel
uint16 ADC_readChannel(uint8 ch_num);

#endif /* ADC_H_ */
