
#ifndef UART_H_
#define UART_H_

#include "../LIB/std_types.h"  // Include the standard types header file.

typedef enum{
	Disabled,Reserved,Even_Parity,Odd_Parity
}UART_Parity;

typedef enum{
	One_Bit,Two_Bit
}UART_StopBit;

typedef enum{
	Five_Bit,Six_Bit,Seven_Bit,Eight_Bit,Rreserved1,Rreserved2,Rreserved3,Nine_Bit
}UART_BitData;

typedef struct{
 UART_BitData bit_data;
 UART_Parity parity;
 UART_StopBit stop_bit;
 uint32 baud_rate;
}UART_ConfigType;

void UART_init(const UART_ConfigType * Config_Ptr);

void UART_sendByte(const uint8 data);


uint8 UART_recieveByte(void);


void UART_sendString(const uint8 *Str);


void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
