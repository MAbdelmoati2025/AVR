#include <avr/io.h>
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/UART/UART.h"
int main()
{
	USART_Init();
	Set_PinDir(PORT_B,Pin_0,OUTPUT);
	Set_PinDir(PORT_B,Pin_1,OUTPUT);
	Set_GroupDir(PORT_C,0x0F);
	//char receivedData;
	while(1)
	{

		//        receivedData = USART_receiveByte();


		if(USART_receiveByte() == 'H')			// Alarm On
		{
			Set_PinLevel(PORT_B,Pin_0,HIGH);
			Set_PinLevel(PORT_B,Pin_1,HIGH);
		}
		else if(USART_receiveByte() == 'F')		// Fan On
		{
			Set_PinLevel(PORT_B,Pin_0,HIGH);
			Set_PinLevel(PORT_B,Pin_1,LOW);
		}
		else
		{
			Set_PinLevel(PORT_B,Pin_0,LOW);
			Set_PinLevel(PORT_B,Pin_1,LOW);
		}

		if(USART_receiveByte() == 'L')			// Led On
		{

			Set_PinLevel(PORT_C,Pin_0,HIGH);

		}
		else
		{
			Set_PinLevel(PORT_C,Pin_0,LOW);

		}

	}
}

