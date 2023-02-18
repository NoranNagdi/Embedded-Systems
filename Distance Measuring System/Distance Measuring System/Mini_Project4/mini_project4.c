 /******************************************************************************
 *
 * File Name: mini_project3.c
 *
 * Description: source file for the Distance Measuring Project
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/
#include "common_macros.h"
#include "gpio.h"
#include "lcd.h"
#include "icu.h"
#include "ultrasonic.h"
#include <util/delay.h> /* To use the delay functions */
#include <avr/io.h>


uint8 g_edgeCount;


int main(void)
{
	uint16 distance_cm = 0;
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	Ultrasonic_init();
	Ultrasonic_Trigger();

	LCD_init();
	LCD_displayString("Distance =    cm");


	while(1)
	{
		if(g_edgeCount == 2)
		{
			g_edgeCount = 0;

			distance_cm = Ultrasonic_readDistance();

			/* Display the distance value every time at same position */
			LCD_moveCursor(0,11);
			if(distance_cm >= 100)
			{
				LCD_intgerToString(distance_cm);
			}
			else
			{
				LCD_intgerToString(distance_cm);
				/* In case the digital value is two or one digits print space in the next digit place */
				LCD_displayCharacter(' ');
			}
		}
	}
}


