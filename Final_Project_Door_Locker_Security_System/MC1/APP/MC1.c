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
#include "avr/io.h"          // AVR I/O functions
#include <util/delay.h>      // Delay functions
#include "../HAL/lcd.h"      // LCD display library
#include "../HAL/keypad.h"   // Keypad library
#include "../MCAL/uart.h"    // UART (serial communication) library
#include "../MCAL/timer.h"   // Timer functions


/*******************Some definitions for using UART**************************************/
// Constants for signaling and communication
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
#define ReadyForPassCheckPassword    0x21     // Signal that the device is ready to receive a password for CheckPassword
#define doorReady                    0x22     // Signal indicating that the door is ready to open
#define BuzzerReady                  0x23     // Signal indicating that the buzzer is ready, possibly for a warning
#define UnMatched                    0x24     // Signal indicating a password mismatch
#define Matched                      0x25     // Signal indicating a password match

/***************************** Function prototypes*****************************************/
void CreatePassword(void);
void ValidatePassword(void);
void SendPassword(void);
void DetermineAccess(void);
void ManageSecurityOptions(const Timer1_ConfigType *Config_Ptr);
void CheckPassword(void);
uint8 DetermineAccess2(void);
void OpenDoor_Flag(void);
void Open_Door(const Timer1_ConfigType *Config_Ptr);

/****************************** Arrays to store passwords************************************/
uint8 First_Pass[]      = {0, 0, 0, 0, 0}; // First password
uint8 Second_Pass[]     = {0, 0, 0, 0, 0}; // Confirmation password
uint8 passcheck[]       = {0, 0, 0, 0, 0};  // Pass i take from user

/***********************************Global variables******************************************/
uint8 key = 0;
uint8 flag = 0;
uint8 doorOpenCounter = 0;
uint8 stayhere = 0;
uint8 counter = 0;

// Function to indicate that the door should open
void OpenDoor_Flag(void)
{
	doorOpenCounter++;
}
void CheckPassword (void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Plz Enter Pass:");

	LCD_moveCursor(1,0);

	for (uint8 i = 0; i < 5; i++)
	{

		key = KEYPAD_getPressedKey();

		while (!((key >= 0) && (key <= 9)))
		{
			key = KEYPAD_getPressedKey();
			_delay_ms(50);
		}
		passcheck[i]=key;
		LCD_displayStringRowColumn(1,i+5,"*");
		_delay_ms(250);

	}

	UART_sendByte(ReadyForPassCheckPassword);
	while(UART_recieveByte() != M2_READY);

	for(uint8 k = 0 ; k <= 4 ; k++)
	{
		UART_sendByte(passcheck[k]);
	}

	while (UART_recieveByte() != WAIT);

}
uint8 DetermineAccess2(void){
	if(UART_recieveByte() == Matched)
	{

		return 1;


	}
	else
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"INCORRECT PASS");
		_delay_ms(500);
		return 0;

	}
}
void Open_Door(const Timer1_ConfigType * Config_Ptr)
{
	UART_sendByte(doorReady);

	LCD_clearScreen();
	Timer1_init(Config_Ptr);
	doorOpenCounter =0;
	while(doorOpenCounter != 3)
	{
		LCD_displayStringRowColumn(0,0,"Opening Door..");
	}

	LCD_clearScreen();
	doorOpenCounter =0;

	while(doorOpenCounter != 3)
	{
		LCD_displayStringRowColumn(0,0,"Door Opened");
	}

	LCD_clearScreen();
	doorOpenCounter =0;

	while(doorOpenCounter!= 3)
	{
		LCD_displayStringRowColumn(0,0,"Closing Door..");
	}
}
void ManageSecurityOptions(const Timer1_ConfigType * Config_Ptr){
	while(stayhere == 0){
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "+ : Open Door");
		LCD_displayStringRowColumn(1, 0, "- : Change Pass");
		key = KEYPAD_getPressedKey();

		while (!((key == '+') || (key == '-')))
		{
			key = KEYPAD_getPressedKey();
			_delay_ms(50);
		}
		if(key == '+')
		{
			uint8 counter1 = 0;
			CheckPassword();
			int x=DetermineAccess2();

			if(x == 1)
			{
				counter1 = 0;
				Open_Door(Config_Ptr);
			}
			else
			{
				while(counter1 <= 2 )
				{
					CheckPassword();
					if(DetermineAccess2() == 1)
					{
						Open_Door(Config_Ptr);
						counter1 = 3;
					}
					else if(counter1 == 1)
					{
						UART_sendByte(BuzzerReady);
						while(UART_recieveByte() != M2_READY);

						LCD_clearScreen();

							LCD_clearScreen();
							LCD_displayStringRowColumn(0, 4, "WARNNING");
							LCD_displayStringRowColumn(1, 5, "BUZZER");
							_delay_ms(5000);

						counter1 = 3;
					}
					counter1++;
				}
			}

		}
		if(key == '-')
		{

			CheckPassword();
			if(DetermineAccess2() == 1)
			{
				stayhere=1;
				flag=0;

			}
			else
			{
				while(counter <= 3)
				{
					CheckPassword();
					if(DetermineAccess2() == 1)
					{
						stayhere=1;
						flag=0;
						counter = 4;
					}
					else if(counter == 1){
						UART_sendByte(BuzzerReady);
						while(UART_recieveByte() != M2_READY);

							LCD_clearScreen();
							LCD_displayStringRowColumn(0, 4, "WARNNING");
							LCD_displayStringRowColumn(1, 5, "BUZZER");
							_delay_ms(5000);

						stayhere=0;
						flag=1;
						counter = 4;
					}
					counter++;
				}
				counter = 0 ;
			}

		}
	}
}
void SendPassword(void){

	UART_sendByte(ReadyForPassone);
	while(UART_recieveByte() != M2_READY);

	for(uint8 k = 0 ; k <= 4 ; k++)
	{
		UART_sendByte(First_Pass[k]);
		while (UART_recieveByte() != WAIT);
	}



	for(uint8 k = 0 ; k <= 4 ; k++)
	{
		UART_sendByte(Second_Pass[k]);
		while (UART_recieveByte() != WAIT);

	}
	UART_sendByte(Done);

}
void DetermineAccess(void){
	if(UART_recieveByte() == Matched)
	{

		flag = 1 ;
		stayhere = 0;

	}
	else
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"NOT MATCHING");
		_delay_ms(1000);
		flag = 0 ;
		stayhere = 1;

	}
}
void ValidatePassword(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Plz Re-enter The");
	LCD_displayStringRowColumn(1, 0, "Same Pass:");
	for (uint8 i = 0; i < 5; i++)
	{

		key = KEYPAD_getPressedKey();
		while (!((key >= 0) && (key <= 9)))
		{
			key = KEYPAD_getPressedKey();
			_delay_ms(50);
		}
		Second_Pass[i]=key;
		LCD_displayCharacter('*');
		_delay_ms(250);

	}
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Plz Press =");
	while(key!='=')
	{
		key=KEYPAD_getPressedKey();
		_delay_ms(50);
	}
}
void CreatePassword(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Add 1st Pass :");

	LCD_moveCursor(1,5);
	for (uint8 i = 0; i < 5; i++)
	{

		key = KEYPAD_getPressedKey();

		while (!((key >= 0) && (key <= 9)))
		{
			key = KEYPAD_getPressedKey();
			_delay_ms(50);
		}
		LCD_displayStringRowColumn(1,i+5,"*");
		First_Pass[i]=key;
		_delay_ms(250);

	}
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Plz Press =");
	while(key!='=')
	{
		key=KEYPAD_getPressedKey();
		_delay_ms(50);
	}
}
int main()
{
	SREG|=(1<<7);
	LCD_init();
	Timer1_ConfigType Timer_Config = {CLK_1024,TIMER1_CTC_OCR1A,0,6000};
	Timer1_setCallBack(OpenDoor_Flag);
	Timer1_init(&Timer_Config);

	UART_ConfigType UART_Config = {Eight_Bit, Disabled, One_Bit, 9600};
	UART_init(&UART_Config);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 3, "Door Locker ");
	LCD_displayStringRowColumn(1, 1, "Security System");
	_delay_ms(500);
	UART_sendByte(M1_READY);

	while(1)
	{
		if(flag == 0)
		{
			CreatePassword();
			ValidatePassword();
			SendPassword();
			DetermineAccess();
		}
		if(flag == 1){
			ManageSecurityOptions(& Timer_Config);
		}

	}
}
