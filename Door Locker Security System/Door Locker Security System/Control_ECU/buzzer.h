 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the BUZZER driver
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/

#define BUZZER_PIN       PIN0_ID
#define BUZZER_PORT      PORTA_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Setup the direction for the buzzer pin as output pin through the
 * GPIO driver.
 * Turn off the buzzer through the GPIO.
 */
void Buzzer_init();

/*
 * Description :
 * Functional responsible for enable the Buzzer through the GPIO.
 */
void Buzzer_on(void);

/*
 * Description :
 * Functional responsible for disable the Buzzer through the GPIO.
 */
void Buzzer_off(void);


#endif /* BUZZER_H_ */
