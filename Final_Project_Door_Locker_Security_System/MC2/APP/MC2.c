/******************************************************************************
 *
 * File Name: Door Locker Security System
 *
 * Created on: 1/11/2023
 *
 * Author: Mohamed A. Abdelmoati
 *
 *******************************************************************************/

// Include necessary libraries for the Door Locker Security System
#include <avr/io.h>                   // Include AVR I/O library for AVR microcontrollers.
#include <util/delay.h>               // Include delay library for creating time delays.
#include "../MCAL/uart.h"             // Include a custom UART (Universal Asynchronous Receiver-Transmitter) library.
#include "../MCAL/twi.h"              // Include a custom TWI (Two-Wire Interface) library.
#include "../HAL/external_eeprom.h"    // Include a custom library for interfacing with an external EEPROM.
#include "../HAL/DCMOTOR.h"           // Include a custom library for controlling a DC motor.
#include "../HAL/Buzzer.h"            // Include a custom library for controlling a buzzer.
#include "../MCAL/timer.h"            // Include a custom library for working with timers.


/*******************Some definitions for using UART**************************************/
// Constants for signaling and communication
// Define various status codes for communication.

#define M1_READY                     0x10     // Signal that the device is ready to receive the initial password
#define M2_READY                     0x11     // Signal that the device is ready to receive the password for confirmation
#define MATCHED                      0x12     // Signal indicating a password match
#define Finish                       0x13     // Unused constant, possibly for future features
#define Done                         0x15     // Signal indicating a task is done or complete
#define WAIT                         0x16     // Signal indicating to wait for a response
#define Test1                        0x17     // Test signal, purpose unclear
#define PLAYMOTOR                    0x18     // Signal to play the motor, purpose unclear
#define PLAYMOTOR1                   0x19     // Another signal to play the motor, purpose unclear
#define ReadyForPassone              0x20     // Signal that the device is ready to receive the first password
#define ReadyForPasschecking         0x21     // Signal that the device is ready to receive a password for CheckPassword
#define doorReady                    0x22     // Signal indicating that the door is ready to open
#define BuzzerReady                  0x23     // Signal indicating that the buzzer is ready, possibly for a warning
#define UnMatched                    0x24     // Signal indicating a password mismatch
#define Matched                      0x25     // Signal indicating a password match
/***************************** Function prototypes*****************************************/
void ReceiveInitialPassword(void);
void SaveInitialPassword (void);
void CheckPasswords(void);
void ReceivePasswordForVerification (void);
void CompareReceivedPassword (void);
void OpenDoor();
void Buzzer (void);
void OpenDoor_Flag(void);
/****************************** Arrays to store passwords************************************/
uint8 First_Pass[]      = {0, 0, 0, 0, 0}; // First password
uint8 Second_Pass[]     = {0, 0, 0, 0, 0}; // Confirmation password
uint8 passcheck[]       = {0, 0, 0, 0, 0};  // Pass i take from user
uint8 EEPROM_Storage[]  = {0, 0, 0, 0, 0}; // Data from external EEPROM
/***********************************Global variables******************************************/
uint8 x = 0;     // Counter variable
uint8 doorOpenCounter = 0;  // Motor rotation control variable

// Function to receive the first and confirmation passwords from a remote device.
void ReceiveInitialPassword(void){

	UART_sendByte(M2_READY);

	for(uint8 i = 0; i <= 4; i++){
		First_Pass[i] = UART_recieveByte();
		UART_sendByte(WAIT);
	}


	for(uint8 i = 0; i <= 4; i++){
		Second_Pass[i] = UART_recieveByte();
		UART_sendByte(WAIT);

	}
	while (UART_recieveByte() != Done);

}
// Function to save the first password in an external EEPROM and then read it back to verify.
void SaveInitialPassword (void){
	for(uint8 i = 0 ; i < 5 ; i++){
		EEPROM_writeByte(0x0311+i,First_Pass[i]);
        _delay_ms(50); // Delay to ensure write completion.
	}
	for(uint8 i = 0 ; i < 5 ; i++){
		EEPROM_readByte(0x0311+i,&EEPROM_Storage[i]);
        _delay_ms(50); // Delay to ensure read completion.
	}
}
// Function to check if the first and confirmation passwords match and send a response accordingly.
void CheckPasswords(void){
	uint8 Counter = 0;

	for(uint8 i = 0; i < 5; i++){
		if(First_Pass[i] != Second_Pass[i]){
			Counter++;// Increment the counter for each mismatch
		}
	}
	if(Counter == 0){
        UART_sendByte(Matched); // Send a signal indicating that passwords match.
		SaveInitialPassword ();// Save the first password to EEPROM
	}
	else {
        UART_sendByte(UnMatched); // Send a signal indicating that passwords do not match.
	}

}
// Function to receive a password for checking from a remote device.
void ReceivePasswordForVerification (void){
	UART_sendByte(M2_READY); // Signal that the receiver is ready to receive.

	    for(uint8 i = 0; i <= 4; i++) {
	        passcheck[i] = UART_recieveByte(); // Receive and store each character of the password for checking.
	    }

	    UART_sendByte(WAIT); // Acknowledge receipt.
}
// Function to compare the received password with the one stored in EEPROM and send a response accordingly.

void CompareReceivedPassword (void){
    uint8 Counter = 0; // Counter to track the number of mismatched characters.

	for(uint8 i = 0; i < 5; i++){
		if(passcheck[i] != EEPROM_Storage[i]){
            Counter++; // Increment the counter for each mismatch.
		}
	}
	if(Counter == 0){
        UART_sendByte(Matched); // Send a signal indicating that the passwords match.
	}
	else {
        UART_sendByte(UnMatched); // Send a signal indicating that the passwords do not match.
	}

}
// Function to control a DC motor to open a door.

void OpenDoor(const Timer1_ConfigType * Config_Ptr)
{

    Timer1_init(Config_Ptr); // Initialize Timer1 with the provided configuration.

	doorOpenCounter =0; // Reset the motor rotation control variable.
	while(doorOpenCounter != 3)
	{
        DcMotor_Rotate(DCMOTOR_CW, 100); // Rotate the DC motor clockwise at 100% speed.
	}


	doorOpenCounter =0;// Reset the motor rotation control variable.

	while(doorOpenCounter != 3)
	{
        DcMotor_Rotate(DCMOTOR_STOP, 0); // Stop the DC motor.
	}


	doorOpenCounter =0;

	while(doorOpenCounter != 3)
	{
        DcMotor_Rotate(DCMOTOR_ACW, 100); // Rotate the DC motor anti-clockwise at 100% speed.
	}

    DcMotor_Rotate(DCMOTOR_STOP, 0); // Stop the DC motor.

}
// Function to activate a buzzer for 60 seconds.

void Buzzer (void)
{
	//while (UART_recieveByte()!= M2_READY);

	buzzer_ON();
	_delay_ms(5000);//5SEC BUT SHOULD BE 60000
	buzzer_OFF();

}
// Function to increment the motor rotation control variable when called as a timer callback.

void OpenDoor_Flag(void)
{
	doorOpenCounter++;// Increment the motor rotation control variable.
}


int main()
{
	SREG |= (1 << 7); // Enable global interrupts.

	    // Configure and initialize Timer1 for controlling the DC motor.
	    Timer1_ConfigType Timer_Config = {CLK_1024, TIMER1_CTC_OCR1A, 0, 6000};
	    Timer1_setCallBack(OpenDoor_Flag);
	    Timer1_init(&Timer_Config);

	    // Configure and initialize UART for communication.
	    UART_ConfigType UART_Config = {Eight_Bit, Disabled, One_Bit, 9600};
	    UART_init(&UART_Config);

	    // Configure and initialize TWI (Two-Wire Interface).
	    TWI_ConfigType twi_config = {0x02, 0x02};
	    TWI_init(&twi_config);

	    DcMotor_Init(); // Initialize the DC motor.
	    buzzer_init();  // Initialize the buzzer.

	    // Wait for a signal indicating readiness from the remote device (M1_READY).
	    while (UART_recieveByte() != M1_READY);

	    // Main program loop.
	    while (1) {
	        // Switch based on the command received over UART.
	        switch (UART_recieveByte())
	        {
		case ReadyForPassone:
			ReceiveInitialPassword();//sendpass
			CheckPasswords();
			break;
		case ReadyForPasschecking:
			ReceivePasswordForVerification ();
			CompareReceivedPassword ();
			break;
		case doorReady:
			OpenDoor(& Timer_Config);
			break;
		case BuzzerReady:
			UART_sendByte(M2_READY);
			Buzzer();
			break;
		}
	}
}











