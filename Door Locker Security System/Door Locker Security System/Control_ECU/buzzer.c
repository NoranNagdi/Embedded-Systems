 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.c
 *
 * Description: source file for the BUZZER driver
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#include "common_macros.h"
#include "gpio.h"
#include "buzzer.h"
#include <avr/io.h>
/*
 * Description :
 * Functional responsible for Setup the direction for the buzzer pin as output pin through the
 * GPIO driver.
 * Turn off the buzzer through the GPIO.
 */
void Buzzer_init()
{
	GPIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}

/*
 * Description :
 * Functional responsible for enable the Buzzer through the GPIO.
 */
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH);
}

/*
 * Description :
 * Functional responsible for disable the Buzzer through the GPIO.
 */
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}
