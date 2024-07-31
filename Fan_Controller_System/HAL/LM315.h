/******************************************************************************
 *
 * File Name: LM35.h
 *
 * Created on: 10/10/2023
 *
 * Description: Header file for DC Motor Control
 *
 * Author: Mohamed A. Abdelmoati
 *
 *******************************************************************************/

#ifndef LM35_SENSOR_H_
#define LM35_SENSOR_H_

#include "../lib/std_types.h"
#include "../MCAL/adc.h"

#define SENSOR_CHANNEL_ID         2
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150

// Function to get the temperature from an LM35 temperature sensor
uint8 LM35_getTemperature(void);

#endif
