/******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.h
 *
 * Description: header file for the AVR timer1 driver
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_


#include "std_types.h"

#define MODE  NORMAL
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer1_Prescaler;


typedef enum
{
	NORMAL,CTC=4
}Timer1_Mode;


typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
}Timer1_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * initialize the timer Driver.
 */
void TIMER1_init(const Timer1_ConfigType *Config_Ptr);

/*
 * Description :
 * function to disable timer1..
 */
void Timer1_deInit(void);

/*
 * Description:
 * Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
