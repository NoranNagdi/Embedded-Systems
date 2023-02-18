 /******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.c
 *
 * Description: source file for the AVR ICU driver
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#include "common_macros.h"
#include "gpio.h"
#include "icu.h"
#include <avr/io.h>
#include <avr/interrupt.h> /* For ICU ISR */


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*
 * Description :
 * initialize the ICU Driver.
 */
void ICU_init(const Icu_ConfigType *Config_Ptr)
{
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = (TCCR1B & 0xF8) | Config_Ptr->clock;
	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge)<<6);
	TCNT1 = 0;
	ICR1 = 0;
	TIMSK |= (1<<TICIE1);
	GPIO_setupPinDirection(ICU_PORT_ID,ICU_PIN_ID,PIN_INPUT);
}

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const Icu_EdgeType edgeType)
{
	TCCR1B = (TCCR1B & 0XBF) | (edgeType<<6);
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void)
{
	TCNT1 = 0;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);

}
