
//	Library
#include "../../UTLIS/Std_Types.h"
#include "../../UTLIS/Common_Macros.h"
//	HAL
#include "keypad_config.h"
#include "keypad.h"
//	MCAL
#include "../../MCAL/DIO/DIO.h"
#include <avr/delay.h>
#include <avr/io.h>



#if (N_COL == 3)

static u8 Keypad_4x3_adjustKeyNumber (u8 button_number);


#elif (N_COL == 4)

static u8 Keypad_4x4_adjustKeyNumber (u8 button_number);

#endif


u8 Keypad_GetPressedKey (void)
{
	u8 row, col;
	while(1)
	{
		for (col = 0; col < N_COL; col++)
		{
			KEYPAD_PORT_DIR = (0b00010000<< col);

			KEYPAD_PORT_OUT = (~(0b00010000<< col));
			for (row = 0; row < N_ROW; row++)
			{
				if (BIT_IS_CLEAR(KEYPAD_PORT_IN,row))
				{
					#if (N_COL == 3)

					return Keypad_4x3_adjustKeyNumber (((row*N_COL)+col+1));
					#elif (N_COL == 4)

					return Keypad_4x4_adjustKeyNumber (((row*N_COL)+col+1));

					#endif
				}
			}
		}
	}
}

#if (N_COL == 3)

static u8 Keypad_4x3_adjustKeyNumber (u8 button_number)
{
	switch (button_number)
	{
	case 10:
		return '*'; //	ASCII code of *
		break;
	case 11:
		return 0;
		break;
	case 12:
		return '#'; //	ASCII code of #
		break;
	default:
		return button_number;
		break;
	}
}


#elif (N_COL == 4)

static u8 Keypad_4x4_adjustKeyNumber (u8 button_number)
{
	switch (button_number)
	{
	case 1:		return 7;
	break;
	case 2:		return 8;
	break;
	case 3:		return 9;
	break;
	case 4:		return '/';
	break;
	case 5:		return 4;
	break;
	case 6:		return 5;
	break;
	case 7:		return 6;
	break;
	case 8:		return '*';
	break;
	case 9:		return 1;
	break;
	case 10:	return 2;
	break;
	case 11:	return 3;
	break;
	case 12:	return '-';
	break;
	case 13:	return 'c';
	break;
	case 14:	return 0;
	break;
	case 15:	return '=';
	break;
	case 16:	return '+';
	break;
	}
}

#endif
