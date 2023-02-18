 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: source file for the ADC driver
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#include <avr/io.h>
#include "adc.h"
#include "common_macros.h"

void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 to choose ref volt
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = (ADMUX & 0x3F) | ((Config_Ptr->ref_volt)<<6);

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 to choose ADC_Clock
	 */
	ADCSRA = (1<<ADEN) ;
	ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr->prescaler);
}


uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX = (ADMUX & 0xE0) | channel_num;
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}



