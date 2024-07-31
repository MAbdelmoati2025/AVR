/******************************************************************************
 *
 * File Name: PWM.c
 *
 * Created on: 10/10/2023
 *
 * Description: PWM (Pulse Width Modulation) Configuration and Control for Fan Controller
 *
 * Author: Mohamed A. Abdelmoati
 *
 *******************************************************************************/
#include <avr/io.h>  // Include AVR I/O library for register access
#include "PWM.h"     // Include PWM header file
#include "../HAL/DCMOTOR.h" // Include DC motor interface for port configuration
#include "../MCAL/gpio.h" // Include GPIO library for pin control

// Function to start PWM on Timer0 with the specified duty cycle
void PWM_Timer0_Start(uint8 duty_cycle)
{
    TCNT0 = 0; // Set Timer Initial value to 0

    // Calculate the Compare Value based on the desired duty cycle (0-100%)
    // It's a floating-point calculation, so we round to the nearest integer using 0.5
    OCR0 = (uint16)(((float)duty_cycle / 100) * 255 + 0.5); // Set Compare Value

    // Set the motor speed control pin as an output
    GPIO_setupPinDirection(motor_port, speed_motor, LOGIC_HIGH);

    // Configure Timer0 for Fast PWM mode with non-inverted output and prescaler 8
    TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01); // Prescaler 8
}
