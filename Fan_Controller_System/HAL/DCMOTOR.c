/******************************************************************************
 *
 * File Name: DCMOTOR.c
 *
 * Created on: 10/10/2023
 *
 * Description:  DC Motor Control Functions
 *
 * Author: Mohamed A. Abdelmoati
 *
 *******************************************************************************/

// Include necessary libraries and header files
#include "../MCAL/gpio.h"
#include <avr/io.h>
#include "DCMOTOR.h"
#include "../MCAL/PWM.h"

void DcMotor_Init(void)
{
	// Set the motor control pins as output and initialize them to low
	GPIO_setupPinDirection(motor_port, motor_output4, LOGIC_HIGH);
	GPIO_setupPinDirection(motor_port, motor_output3, LOGIC_HIGH);
	GPIO_writePin(motor_port, motor_output3, LOGIC_LOW);
	GPIO_writePin(motor_port, motor_output4, LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{
	// Depending on the specified state, control the motor and set the speed

	switch (state)
	{
	case DCMOTOR_CW:
		// Clockwise rotation
		GPIO_writePin(motor_port, motor_output3, LOGIC_LOW);
		GPIO_writePin(motor_port, motor_output4, LOGIC_HIGH);
		PWM_Timer0_Start(speed);  // Start PWM with the specified speed
		break;

	case DCMOTOR_ACW:
		// Anti-clockwise rotation
		GPIO_writePin(motor_port, motor_output3, LOGIC_HIGH);
		GPIO_writePin(motor_port, motor_output4, LOGIC_LOW);
		PWM_Timer0_Start(speed);  // Start PWM with the specified speed
		break;

	case DCMOTOR_STOP:
		// Stop the motor
		GPIO_writePin(motor_port, motor_output3, LOGIC_LOW);
		GPIO_writePin(motor_port, motor_output4, LOGIC_LOW);
		PWM_Timer0_Start(speed);  // Start PWM with the specified speed (typically 0 for stop)
		break;
	}
}
