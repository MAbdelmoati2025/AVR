#ifndef MCAL_UART_UART_H_
#define MCAL_UART_UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "avr/delay.h"
#include "../DIO/DIO.h"
#include "../../UTLIS/Common_Macros.h"
#include "../../UTLIS/Std_Types.h"


/***************************************************************************************************/
/*****************************************Preprocessor Macros****************************************/

#define UART_BAUDRATE 9600

/***************************************************************************************************/
/****************************************Function Prototypes****************************************/

void USART_Init (void);					// Function to initialize the USART
void USART_sendByte (u8 data);			// Function to send data byte
u8 USART_receiveByte (void);			// Function to receive data byte
void USART_sendString (const u8 *str);	// Function to send string
void USART_receiveString (u8 *str);		// Function to receive string

#endif /* MCAL_ADC_ADC_H_ */
