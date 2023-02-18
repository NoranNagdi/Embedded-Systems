 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.c
 *
 * Description: source file for the DC Motor driver
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#include "dc_motor.h"
#include "gpio.h"
#include "common_macros.h"
#include <avr/io.h>
#include "timer.h"

/*
 * Description :
 * initialize the DC Motor.
 */
void DcMotor_Init(void)
{
	GPIO_setupPinDirection(DC_MOTOR_INPUT_PORT_ID,DC_MOTOR_INPUT1_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_INPUT_PORT_ID,DC_MOTOR_INPUT2_PIN_ID,PIN_OUTPUT);

	GPIO_writePin(DC_MOTOR_INPUT_PORT_ID,DC_MOTOR_INPUT1_PIN_ID,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_INPUT_PORT_ID,DC_MOTOR_INPUT2_PIN_ID,LOGIC_LOW);
}



/*
 * Description :
 * Rotate the DC Motor with any speed and in any direction.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	PORTB = (PORTB & 0xFC) | state;  /*adjust the direction of rotation*/

	PWM_Timer0_Start(speed);        /*adjust the speed*/
}
