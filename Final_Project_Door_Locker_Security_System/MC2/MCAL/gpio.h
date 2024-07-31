
#ifndef GPIO_H_
#define GPIO_H_

#include "../LIB/std_types.h"
 // Include the standard types header file.

#define NUM_OF_PORTS          		4              // Define the number of available ports.
#define NUM_OF_PINS_PER_PORT  		8              // Define the number of pins per port.

#define PORTA_ID					0              // Define the identifier for Port A.
#define PORTB_ID					1              // Define the identifier for Port B.
#define PORTC_ID					2              // Define the identifier for Port C.
#define PORTD_ID					3              // Define the identifier for Port D.

#define PIN0_ID						0              // Define the identifier for Pin 0.
#define PIN1_ID						1              // Define the identifier for Pin 1.
#define PIN2_ID						2              // Define the identifier for Pin 2.
#define PIN3_ID						3              // Define the identifier for Pin 3.
#define PIN4_ID						4              // Define the identifier for Pin 4.
#define PIN5_ID						5              // Define the identifier for Pin 5.
#define PIN6_ID						6              // Define the identifier for Pin 6.
#define PIN7_ID						7              // Define the identifier for Pin 7.

typedef enum {
    PIN_INPUT, PIN_OUTPUT  // Enumeration for specifying pin direction (input or output).
} GPIO_PinDirectionType;

typedef enum {
    PORT_INPUT, PORT_OUTPUT = 0xFF  // Enumeration for specifying port direction (input or output).
} GPIO_PortDirectionType;

void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);
// Function to set the direction of a specific pin.

void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);
// Function to write a value to a specific pin.

void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);
// Function to set the direction of an entire port.

void GPIO_writePort(uint8 port_num, uint8 value);
// Function to write a value to an entire port.

uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);
// Function to read the value of a specific pin.

uint8 GPIO_readPort(uint8 port_num);
// Function to read the value of an entire port.

#endif /* GPIO_H_ */
