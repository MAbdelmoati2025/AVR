/******************************************************************************
 *
 * File Name: Main.c
 *
 * Created on: 10/10/2023
 *
 * Description:
 *
 * Author: Mohamed A. Abdelmoati
 *
 *******************************************************************************/


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include"../LIB/std_types.h"

/*******************definition************************************************/
#define ULTRA_SONIC_TRIGGER_PORT_ID   PORTB_ID
#define ULTRA_SONIC_TRIGGER_PIN_ID    PIN5_ID

#define ULTRA_SONIC_ECHO_PORT_ID      PORTD_ID
#define ULTRA_SONIC_ECHO_PIN_ID    PIN6_ID



/*******************FUNCTION PROTOTYPE********************************/


/* Description:
 * -Initialize the ICU driver
 * -Initialize  ICU call back function.
 * -Setup the direction for the trigger as output
 * -Setup the direction for the Echo as Input FOR ATMEgA32
 */

void Ultrasonic_init(void);

/* Description:
 * -SEND TRIGGER PLUSE TO SENSOR
 */

void Ultrasonic_Trigger(void);

/* Description:
 *-Initialize trigger function
 *-Start the measurements by the ICU
 */
uint32 Ultrasonic_readDistance(void);
/* if we made this function float32 it made the project more sensitive
 * but in requirement must be uint16
 * but i add small part to try to solve this problem by using #if
 */


#endif /* ULTRASONIC_H_ */
