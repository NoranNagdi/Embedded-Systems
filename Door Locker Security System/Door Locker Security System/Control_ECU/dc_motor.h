 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the DC Motor driver
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"


/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/
#define DC_MOTOR_INPUT_PORT_ID       PORTB_ID

#define DC_MOTOR_INPUT1_PIN_ID       PIN0_ID
#define DC_MOTOR_INPUT2_PIN_ID       PIN1_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	STOP,A_CW,CW
}DcMotor_State;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * initialize the DC Motor.
 */
void DcMotor_Init(void);


/*
 * Description :
 * Rotate the DC Motor.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
