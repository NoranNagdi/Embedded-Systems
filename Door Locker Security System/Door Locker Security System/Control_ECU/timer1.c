/******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.c
 *
 * Description: Source file for the AVR timer1 driver
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#include <avr/io.h>
#include "common_macros.h"
#include "timer1.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


/*
 * Description :
 * initialize the timer Driver.
 */
void TIMER1_init(const Timer1_ConfigType *Config_Ptr)
{
	/*set bits for non pwm mode*/
	TCCR1A |= (1<<FOC1A) | (1<<FOC1B);

	/*setup mode bits*/
	TCCR1A = (TCCR1A & 0xFC) | (Config_Ptr->mode);
	TCCR1B = (TCCR1B & 0xF3) | ((Config_Ptr->mode)<<3);

	/*setup the clock for timer1*/
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->prescaler);

	/*setup the initial value of timer1*/
	TCNT1 = (Config_Ptr->initial_value);

	if((Config_Ptr->mode) == CTC)
	{
		OCR1A = (Config_Ptr->compare_value);
		TIMSK |= (1<<OCIE1A);
	}
	else
	{
		TIMSK |= (1<<TOIE1);
	}
}

/*
 * Description :
 * function to disable timer1..
 */
void Timer1_deInit(void)
{
	TCCR1B = 0; /*clear clock to disable timer*/
}

/*
 * Description:
 * Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
