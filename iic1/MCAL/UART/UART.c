#include "UART.h"
#define BAUD_PRESCALE ((F_CPU / (UART_BAUDRATE * 8UL))-1)
void USART_Init (void)
{

	UCSRA = (1<<U2X);

	UCSRB = (1<<RXEN) | (1<<TXEN);


	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);

	UBRRH = BAUD_PRESCALE >> 8;
	UBRRL = BAUD_PRESCALE;

}

void USART_sendByte (u8 data)			// Function to send data byte
{

	UDR = data;
	while (BIT_IS_CLEAR(UCSRA,TXC));
	SET_BIT(UCSRA,TXC);

}

u8 USART_receiveByte (void)				// Function to receive data byte
{
	while (BIT_IS_CLEAR(UCSRA,RXC));	//Polling until UDR register is full with data
	return UDR;							// Return the data from UDR register
}

void USART_sendString (const u8 *str)	// Function to send string
{
	u8 i = 0;

	while (str[i] != '\0')
	{
		USART_sendByte(str[i]);
		i++;
	}
}

void USART_receiveString (u8 *str)		// Function to receive string
{

	u8 i = 0;
	str[i] = USART_receiveByte();
	while (str[i] != "#")
	{
		i++;
		str[i] =USART_receiveByte();
	}
	str[i] = '\0';
}
