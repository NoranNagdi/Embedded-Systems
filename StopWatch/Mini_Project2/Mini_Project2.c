/*
 * Mini_Project2.c
 *
 *  Created on: Sep 17, 2022
 *      Author: DELL
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


unsigned char sec = 0;
unsigned char min = 0;
unsigned char hour = 0;

ISR(TIMER1_COMPA_vect)
{
	sec++;

	if(sec == 60)
	{
		min++;
		sec = 0;
	}

	else if(min == 60)
	{
		hour++;
		min = 0;
		sec = 0;
	}
}

ISR(INT0_vect)
{
	sec = 0;
	min = 0;
	hour = 0;
}

ISR(INT1_vect)
{
	TCCR1B &= (~((1<<CS10) | (1<<CS11) | (1<<CS12)));
}

ISR(INT2_vect)
{
	TCCR1B |= (1<<CS12);
}

void Timer1_init()
{
	TCNT1 = 0;		/* Set timer1 initial count to zero */

	OCR1A = 3906;    /* Set the Compare value to 125 ((125/500) * 100 = 25%) */
	//OCR1AH = 125;

	TIMSK |= (1<<OCIE1A); /* Enable Timer1 Compare A Interrupt */

	/* Configure timer control register TCCR1A
	 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
	 * 2. FOC1A=1 FOC1B=0
	 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
	 */
	TCCR1A = (1<<FOC1A); // CTC mode

	/* Configure timer control register TCCR1B
	 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
	 * 2. Prescaler = F_CPU/8 CS10=0 CS11=1 CS12=0
	 */
	TCCR1B = (1<<WGM12) | (1<<CS12);
}

void INT0_init()
{
	DDRD  &= (~(1<<PD2));               // Configure INT0/PD2 as input pin
	PORTD |= (1<<PD2);          // activate internal pull up
	MCUCR |= (1<<ISC01);   // Trigger INT0 with the falling edge
	GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0

}

void INT1_init()
{
	DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
	MCUCR |= (1<<ISC11) | (1<<ISC10);  // Trigger INT1 with the rising edge
	GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
}

void INT2_init()
{
	DDRB   &= (~(1<<PB2));   // Configure INT2/PB2 as input pin
	PORTB |= (1<<PB2);          // activate internal pull up
	MCUCSR &= (~(1<<ISC2));     // Trigger INT2 with the falling edge
	GICR   |= (1<<INT2);	 // Enable external interrupt pin INT2
}

int main()
{
	DDRC |= 0x0F; // make 1st 4 pins of portc output for decoder
	PORTC |= 0x0F; // initialize 1st 4 pins of portc with 0

	DDRA |= 0x3F; //make 1st 6 pins of porta output for 7segment enable
    PORTA |= 0xc0;

	SREG |= (1<<7); //enable i_bit

	Timer1_init();
	INT0_init();
	INT1_init();
	INT2_init();

	while(1)
	{
		PORTA = (1<<PA0);
		// Display the required number on the 7-segment
		PORTC = (PORTC & 0xF0) | ((sec%10) & 0x0F) ;
		_delay_ms(2);

		PORTA = (1<<PA1);
		// Display the required number on the 7-segment
		PORTC = (PORTC & 0xF0) | ((sec/10) & 0x0F) ;
		_delay_ms(2);


		PORTA = (1<<PA2);
		// Display the required number on the 7-segment
		PORTC = (PORTC & 0xF0) | ((min%10) & 0x0F) ;
		_delay_ms(2);


		PORTA = (1<<PA3);
		// Display the required number on the 7-segment
		PORTC = (PORTC & 0xF0) | ((min/10) & 0x0F) ;
		_delay_ms(2);

		PORTA = (1<<PA4);
		// Display the required number on the 7-segment
		PORTC = (PORTC & 0xF0) | ((hour%10) & 0x0F) ;
		_delay_ms(2);


		PORTA = (1<<PA5);
		// Display the required number on the 7-segment
		PORTC = (PORTC & 0xF0) | ((hour/10) & 0x0F) ;
		_delay_ms(2);
	}
}

