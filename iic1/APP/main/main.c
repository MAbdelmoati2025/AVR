
#include <avr/delay.h>
#include "../../HAL/LCD/LCD.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../HAL/Keypad/keypad.h"
#include "../../HAL/Keypad/keypad_config.h"

int main ()
{
	u8 key;
	u8 mode = 1;
	u32 Saved_Pass = 1234;
	u32 Temp_Pass = 0;
	u32 Comp_Pass = 0;
	u8 motor_steps[2] = {6, 3};
	u8 incorrectAttempts = 0; // Variable to count incorrect attempts
	Set_GroupDir(PORT_C, 0x0F);
	Set_GroupLevel(PORT_C, 0xF0);
	LCD_Init ();
	Display_Str("Welcome Home");
	_delay_ms(500);
	while(1)
	{
		LCD_CLEAR();

		if (mode)
		{
			LCD_CLEAR();
			Display_Str("Password : \n");
			for (u8 i = 0; i<4 ;i++)
			{
				Send_CMD(CURSOR_ON);
				_delay_ms(100);
				Send_CMD(CURSOR_OFF);

				key = Keypad_GetPressedKey();
				if ((key >= 0) && (key <= 9))
				{
					Integer_TO_String (key);
					_delay_ms(200);
					Display_Str_Row_Col(0, 11+i, "*");
				}
				else
				{
					LCD_CLEAR();
					Display_Str_Row_Col(0, 1, "Invalid Input");
					_delay_ms(500);
					break;
				}
				Comp_Pass += key;
				Comp_Pass = Comp_Pass * 10;
			}
			Comp_Pass = Comp_Pass / 10;
			_delay_ms(500);
			LCD_CLEAR();
			if (Saved_Pass == Comp_Pass)
			{
				Display_Str("Welcome Back");
				PORTC |= (PORTC & 0xF0) | (motor_steps[1] & 0b00001111);  // 90
				_delay_ms(10000);
				PORTC = (PORTC & 0xF0)  | (motor_steps[0] & 0b00001111);  // 0
				LCD_CLEAR();
				Comp_Pass = 0;
				incorrectAttempts = 0; // Reset incorrect attempts count
			}
			else
			{
				Display_Str_Row_Col(0,1,"Wrong Password");
				_delay_ms(50);
				LCD_CLEAR();
				Comp_Pass = 0;
				incorrectAttempts++; // Increase incorrect attempts count
				if (incorrectAttempts >= 3) // If 3 or more incorrect attempts, activate the buzzer
				{
					LCD_CLEAR();

					Display_Str("Alarm On");

					Set_PinLevel(PORT_D,3,HIGH);
					_delay_ms(1000000); // Buzzer on
					Set_PinLevel(PORT_D,3,LOW);
					// If 3 or more incorrect attempts, shut down the system
					LCD_CLEAR();

					Display_Str("System Shutdown");
					_delay_ms(1000); // Add a delay for visibility
					// Perform the system shutdown procedure here (e.g., turning off power or any necessary actions).
					while (1)
					{
						// The system is shut down; you can add any additional code here if needed.
					}
				}
			}
		}
	}
}

