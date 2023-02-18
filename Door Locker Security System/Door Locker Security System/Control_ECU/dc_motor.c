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
 * Rotate the DC Motor.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	PWM_Timer0_Start(speed);

	switch(state)
	{
	default:
	case STOP:
		GPIO_writePin(DC_MOTOR_INPUT_PORT_ID,DC_MOTOR_INPUT1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_INPUT_PORT_ID,DC_MOTOR_INPUT2_PIN_ID,LOGIC_LOW);
		break;
	case A_CW:
		GPIO_writePin(DC_MOTOR_INPUT_PORT_ID,DC_MOTOR_INPUT1_PIN_ID,LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_INPUT_PORT_ID,DC_MOTOR_INPUT2_PIN_ID,LOGIC_LOW);
		break;
	case CW:
		GPIO_writePin(DC_MOTOR_INPUT_PORT_ID,DC_MOTOR_INPUT1_PIN_ID,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_INPUT_PORT_ID,DC_MOTOR_INPUT2_PIN_ID,LOGIC_HIGH);
		break;
	}
}
