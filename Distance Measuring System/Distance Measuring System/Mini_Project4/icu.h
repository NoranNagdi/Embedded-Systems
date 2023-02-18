 /******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.h
 *
 * Description: Header file for the AVR ICU driver
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ICU_PORT_ID        PORTD_ID
#define ICU_PIN_ID         PIN6_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Icu_Clock;

typedef enum
{
	FALLING,RISING
}Icu_EdgeType;

typedef struct
{
	Icu_Clock clock;
	Icu_EdgeType edge;
}Icu_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * initialize the ICU Driver.
 */
void ICU_init(const Icu_ConfigType *Config_Ptr);

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*a_ptr)(void));

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const Icu_EdgeType edgeType);

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void);

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInit(void);

#endif /* ICU_H_ */
