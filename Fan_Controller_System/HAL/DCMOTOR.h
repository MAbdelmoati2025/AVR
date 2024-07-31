/******************************************************************************
 *
 * File Name: DCMOTOR.h
 *
 * Created on: 10/10/2023
 *
 * Description: Header file for DC Motor Control
 *
 * Author: Mohamed A. Abdelmoati
 *
 *******************************************************************************/

#ifndef DCMOTOR_INTERFACE_H_
#define DCMOTOR_INTERFACE_H_

#include "../LIB/STD_TYPEs.h"

// Enumeration to define the state of the DC motor
typedef enum
{
    DCMOTOR_CW,   // Clockwise rotation
    DCMOTOR_ACW,  // Anti-clockwise (Counter-clockwise) rotation
    DCMOTOR_STOP, // Motor stopped
} DcMotor_State;

// Define the port and pins for motor control
#define motor_port    PORTB_ID   // Port used for motor control       (example: PORTB)
#define motor_output3 PIN0_ID    // Pin for motor output 3            (example: Pin 0 of the chosen port)
#define motor_output4 PIN1_ID    // Pin for motor output 4            (example: Pin 1 of the chosen port)
#define speed_motor   PIN3_ID    // Pin for controlling motor speed   (example: Pin 3 of the chosen port)

// Function to initialize the DC motor
void DcMotor_Init(void);

// Function to rotate the DC motor based on the given state and speed
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif
