/******************************************************************************
 *
 * File Name: Miniproject2
 *
 * Description: Digital Stopwatch System
 *
 * Author: Mohamed Ahmed Abdelmoati
 *
 * Created: 14/09/2023 2:24:15 AM
 *
 *******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int Flag = 0;          // A Flag to signal the timer interrupt
unsigned int Seven_Segment[6];  // Array to store the 6 digits to be displayed

// Function to initialize Timer1 for interrupt generation
void Timer1(void)
{
	TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);     // Selects CTC mode & 1024 Prescaler
	TCNT1  = 0;                                            // Initial comparison value
	OCR1A  = 1000;                                         // 1 Second
	TIMSK |= (1 << OCIE1A);                                // Enables compare mode interrupt
	SREG  |= (1 << 7);
}
// Timer1 Compare Match interrupt handler
ISR(TIMER1_COMPA_vect)
{
	Flag=1;
}
// Function to initialize External Interrupt 0 (INT0)
void INT0_Init(void)
{
	MCUCR |= (1<<ISC11);   // Trigger INT0 with the falling edge
	GICR  |= (1<<INT0);    // Enable external interrupt pin INT0
	SREG  |= (1<<7);       // Enable interrupts by setting I-bit
}
// INT0 interrupt handler
ISR(INT0_vect)
{
	// Reset the Seven_Segment array to all zeros
	Seven_Segment[0]=0;
	Seven_Segment[1]=0;
	Seven_Segment[2]=0;
	Seven_Segment[3]=0;
	Seven_Segment[4]=0;
	Seven_Segment[5]=0;
}
// Function to initialize External Interrupt 1 (INT1)
void INT1_Init(void)
{

	MCUCR|=(1<<ISC11)|(1<<ISC10);   // Trigger INT1 with the raising edge
	GICR  |= (1<<INT1);             // Enable external interrupt pin INT1
	SREG  |= (1<<7);                // Enable interrupts by setting I-bit
}
// INT1 interrupt handler
ISR(INT1_vect)
{
	// Disable Timer1 stop the stopwatch (paused)
	TIMSK &=~ (1 << OCIE1A);
}
// Function to initialize External Interrupt 2 (INT2)
void INT2_Init(void)
{
	MCUCR &=~ (1<<ISC2);    // Trigger INT1 with the falling edge
	GICR  |= (1<<INT2);    // Enable external interrupt pin INT1
	SREG  |= (1<<7);       // Enable interrupts by setting I-bit
}
// INT2 interrupt handler
ISR(INT2_vect)
{
	// (resume the stopwatch)
	TIMSK |= (1 << OCIE1A);
}
// Function to display the digits on a 7-segment display
void Display()
{
	for (int i =0 ;i<6;i++)
	{
		PORTA =(1<<i);               // pin[i] = 1 and 4 pin = 0
		PORTC = Seven_Segment[i];    // Display the corresponding digit
		_delay_ms(1);                // Delay to Display the Digit
	}
}
// Function to update the stopwatch time
void Stop_Watch(void)
{
	//SECOND
	Seven_Segment[0]++;
	if (Seven_Segment[0]>9)
	{
		Seven_Segment[1]++;
		Seven_Segment[0]=0;
		if(Seven_Segment[1]==6)
		{
			Seven_Segment[2]++;
			Seven_Segment[0]=0;
			Seven_Segment[1]=0;
		}
	}
	// MIN
	if(Seven_Segment[2] > 9)
	{
		Seven_Segment[3]++;
		Seven_Segment[2] = 0;

		if(Seven_Segment[3] == 6)
		{
			Seven_Segment[4]++;
			Seven_Segment[3] = 0;
		}
	}
	//HOUR
	if(Seven_Segment[4] > 9)
	{
		Seven_Segment[5]++;
		Seven_Segment[4] = 0;
	}
	else if(Seven_Segment[5] == 2 && Seven_Segment[4] == 4)
	{
		// Reset the stopwatch
		Seven_Segment[0] = 0;
		Seven_Segment[1] = 0;
		Seven_Segment[2] = 0;
		Seven_Segment[3] = 0;
		Seven_Segment[4] = 0;
		Seven_Segment[5] = 0;
	}
}
/*********************************start*****************************************/
int main()
{
	/*Initialization Values*/

	DDRC  |= 0x0F ;        // 4 pins in Portc are outputs
	PORTC &= 0xF0;         // volt 0

	DDRA  |= 0b00111111;   // first 6 pins in PORTA are outputs
	PORTA |= 0xFF;         // volt 1

	DDRD  &=~(1<<PD2);     // Configure INT0/PD2 as input pin (reset)
	PORTD|=(1<<2);         //enable internal pull up resistor

	DDRD  &=~(1<<PD3);     // Configure INT1/PD3 as input pin (stop/paused)

	DDRB  &=~(1<<PB2);     // Configure INT2/PB2 as input pin (resumed)
	PORTB|=(1<<2);         //enable internal pull up resistor


	Timer1();    // Initialize Timer1
	INT0_Init(); // Initialize INT0
	INT1_Init(); // Initialize INT1
	INT2_Init(); // Initialize INT2
	while(1)
	{
		Display();
		if (Flag==1)
		{
			Stop_Watch();
			Flag = 0;   // Reset the Flag
		}
	}
}

/*******************************************************************************/
