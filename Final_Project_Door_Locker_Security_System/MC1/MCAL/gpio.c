
#include <avr/io.h>                       // Include the AVR I/O library.
#include "gpio.h"                         // Include the GPIO header file.
#include "../LIB/common_macros.h"         // Include a file for common macros.

void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction) {
    if ((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT)) {
        // Check for valid port and pin numbers.
    }
    else {
        switch (port_num) {
            case PORTA_ID:
                if (direction == PIN_INPUT) {
                    CLEAR_BIT(DDRA, pin_num);  // Set the pin direction to input.
                }
                else {
                    SET_BIT(DDRA, pin_num);    // Set the pin direction to output.
                }
                break;
            case PORTB_ID:
                if (direction == PIN_INPUT) {
                    CLEAR_BIT(DDRB, pin_num);  // Set the pin direction to input.
                }
                else {
                    SET_BIT(DDRB, pin_num);    // Set the pin direction to output.
                }
                break;
            case PORTC_ID:
                if (direction == PIN_INPUT) {
                    CLEAR_BIT(DDRC, pin_num);  // Set the pin direction to input.
                }
                else {
                    SET_BIT(DDRC, pin_num);    // Set the pin direction to output.
                }
                break;
            case PORTD_ID:
                if (direction == PIN_INPUT) {
                    CLEAR_BIT(DDRD, pin_num);  // Set the pin direction to input.
                }
                else {
                    SET_BIT(DDRD, pin_num);    // Set the pin direction to output.
                }
                break;
        }
    }
}

void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value) {
    if ((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT)) {
        // Check for valid port and pin numbers.
    }
    else {
        switch (port_num) {
            case PORTA_ID:
                if (value == LOGIC_HIGH) {
                    SET_BIT(PORTA, pin_num);  // Set the pin to logic high.
                }
                else {
                    CLEAR_BIT(PORTA, pin_num);  // Set the pin to logic low.
                }
                break;
            case PORTB_ID:
                if (value == LOGIC_HIGH) {
                    SET_BIT(PORTB, pin_num);  // Set the pin to logic high.
                }
                else {
                    CLEAR_BIT(PORTB, pin_num);  // Set the pin to logic low.
                }
                break;
            case PORTC_ID:
                if (value == LOGIC_HIGH) {
                    SET_BIT(PORTC, pin_num);  // Set the pin to logic high.
                }
                else {
                    CLEAR_BIT(PORTC, pin_num);  // Set the pin to logic low.
                }
                break;
            case PORTD_ID:
                if (value == LOGIC_HIGH) {
                    SET_BIT(PORTD, pin_num);  // Set the pin to logic high.
                }
                else {
                    CLEAR_BIT(PORTD, pin_num);  // Set the pin to logic low.
                }
                break;
        }
    }
}

uint8 GPIO_readPin(uint8 port_num, uint8 pin_num) {
    if ((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT)) {
        return LOGIC_LOW;  // Return logic low for invalid port or pin.
    }
    else {
        switch (port_num) {
            case PORTA_ID:
                if (BIT_IS_SET(PINA, pin_num)) {
                    return LOGIC_HIGH;  // Return logic high if the pin is set.
                }
                else {
                    return LOGIC_LOW;   // Return logic low if the pin is clear.
                }
                break;
            case PORTB_ID:
                if (BIT_IS_SET(PINB, pin_num)) {
                    return LOGIC_HIGH;  // Return logic high if the pin is set.
                }
                else {
                    return LOGIC_LOW;   // Return logic low if the pin is clear.
                }
                break;
            case PORTC_ID:
                if (BIT_IS_SET(PINC, pin_num)) {
                    return LOGIC_HIGH;  // Return logic high if the pin is set.
                }
                else {
                    return LOGIC_LOW;   // Return logic low if the pin is clear.
                }
                break;
            case PORTD_ID:
                if (BIT_IS_SET(PIND, pin_num)) {
                    return LOGIC_HIGH;  // Return logic high if the pin is set.
                }
                else {
                    return LOGIC_LOW;   // Return logic low if the pin is clear.
                }
                break;
        }
    }
    return LOGIC_LOW;
}

void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction) {
    if (port_num >= NUM_OF_PORTS) {
        // Check for a valid port number.
    }
    else {
        switch (port_num) {
            case PORTA_ID:
                DDRA = direction;  // Set the direction of all pins of Port A.
                break;
            case PORTB_ID:
                DDRB = direction;  // Set the direction of all pins of Port B.
                break;
            case PORTC_ID:
                DDRC = direction;  // Set the direction of all pins of Port C.
                break;
            case PORTD_ID:
                DDRD = direction;  // Set the direction of all pins of Port D.
                break;
        }
    }
}

void GPIO_writePort(uint8 port_num, uint8 value) {
    if (port_num >= NUM_OF_PORTS) {
        // Check for a valid port number.
    }
    else {
        switch (port_num) {
            case PORTA_ID:
                PORTA = value;  // Set the output value for all pins of Port A.
                break;
            case PORTB_ID:
                PORTB = value;  // Set the output value for all pins of Port B.
                break;
            case PORTC_ID:
                PORTC = value;  // Set the output value for all pins of Port C.
                break;
            case PORTD_ID:
                PORTD = value;  // Set the output value for all pins of Port D.
                break;
        }
    }
}

uint8 GPIO_readPort(uint8 port_num) {
    if (port_num >= NUM_OF_PORTS) {
        // Check for a valid port number.
    }
    else {
        switch (port_num) {
            case PORTA_ID:
                return PORTA;  // Return the value of all pins in Port A.
            case PORTB_ID:
                return PORTB;  // Return the value of all pins in Port B.
            case PORTC_ID:
                return PORTC;  // Return the value of all pins in Port C.
            case PORTD_ID:
                return PORTD;  // Return the value of all pins in Port D.
        }
    }
    return LOGIC_LOW;
}
