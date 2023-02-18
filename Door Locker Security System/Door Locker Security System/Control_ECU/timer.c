/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.c
 *
 * Description: Source file for the AVR timer driver
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#include "timer.h"
#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the Timer Registers */


/*
 * Description :
 * Generate a PWM signal from timer 0.
 */
void PWM_Timer0_Start(uint8 duty_cycle)
{
	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);

	TCNT0 = 0; // Set Timer Initial Value to 0

	OCR0  = (uint8)(((uint32)duty_cycle * TIMER0_MAX_VALUE)/100); // Set Compare Value

	GPIO_setupPinDirection(TIMER0_PWM_PORT_ID,TIMER0_PWM_PIN_ID,PIN_OUTPUT); // Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC
}


