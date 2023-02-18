 /******************************************************************************
 *
 * File Name: mini_project3.c
 *
 * Description: source file for the fan controllerproject
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/
#include "common_macros.h"
#include "gpio.h"
#include "lcd.h"
#include "adc.h"
#include "dc_motor.h"
#include "lm35.h"
#include "timer.h"
#include <util/delay.h> /* To use the delay functions */

typedef enum
{
	OFF,ON
}Fan_State;

int main(void)
{
	ADC_ConfigType adc_config = {F_CPU_8,INTERNAL_REF_VOLT};
	Fan_State fan_state = OFF;

	DcMotor_Init();
	ADC_init(&adc_config);
	LCD_init();

	LCD_displayString("FAN is    ");
	LCD_displayStringRowColumn(1,0,"Temp =     C");
	while(1)
	{
		uint8 temp;
		temp = LM35_getTemperature();

		if(temp < 30)
		{
			DcMotor_Rotate(STOP,0);
			fan_state = OFF;
		}
		if(temp >= 30)
		{
			DcMotor_Rotate(CW,25);
			fan_state = ON;
		}
		if(temp >= 60)
		{
			DcMotor_Rotate(CW,50);
			fan_state = ON;
		}
		if(temp >= 90)
		{
			DcMotor_Rotate(CW,75);
			fan_state = ON;
		}
		if(temp >= 120)
		{
			DcMotor_Rotate(CW,100);
			fan_state = ON;
		}

		/* Display the state every time at same position */
		LCD_moveCursor(0,8);
		if(fan_state == OFF)
		{
			LCD_displayString("OFF");
		}
		else
		{
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
		}

		/* Display the temperature value every time at same position */
		LCD_moveCursor(1,7);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
	}
}
