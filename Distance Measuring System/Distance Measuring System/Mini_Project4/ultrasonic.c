 /******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.h
 *
 * Description: source file for ultrasonic driver
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/
#include "gpio.h"
#include "icu.h"
#include "ultrasonic.h"
#include "common_macros.h"
#include <util/delay.h>


uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;

Icu_ConfigType icu_config = {F_CPU_8,RISING};

/*
 * Description :
 * initialize the ultrasonic Driver.
 */
void Ultrasonic_init(void)
{
	ICU_init(&icu_config);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,PIN_OUTPUT);
}


/*
 * Description :
 * send the trigger pulse to the ultrasonic.
 */
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_LOW);
}


/*
 * Description :
 * Send the trigger pulse by using Ultrasonic_Trigger function.
 * Start the measurements by the ICU from this moment.
 */
uint16 Ultrasonic_readDistance(void)
{
	uint16 ultrasonic_value = 0;
	Ultrasonic_Trigger();
	ultrasonic_value = (0.017 * g_timeHigh);
    return ultrasonic_value;
}


/*
 * Description :
 * This is the call back function called by the ICU driver.
 * This is used to calculate the high time generated by the ultrasonic.
 */
void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		ICU_clearTimerValue();
		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = ICU_getInputCaptureValue();
		/* Clear the timer counter register to start measurements again */
		ICU_clearTimerValue();
		/* Detect rising edge */
		ICU_setEdgeDetectionType(RISING);
	}
}



