/******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.h
 *
 * Description: header file for the AVR timer driver
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TIMER0_MAX_VALUE       256

#define TIMER0_PWM_PORT_ID     PORTB_ID
#define TIMER0_PWM_PIN_ID      PIN3_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Generate a PWM signal from timer 0.
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* TIMER_H_ */
