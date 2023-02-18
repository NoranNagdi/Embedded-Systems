 /******************************************************************************
 *
 * File Name: Control_Ecu.c
 *
 * Description: Source file for the Control ECU
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/
#include "uart.h"
#include "buzzer.h"
#include "dc_motor.h"
#include "timer1.h"
#include "i2c.h"
#include "eeprom.h"
#include <util/delay.h>
#include <avr/io.h>
#include <String.h>

#define RATE400K 400000UL

#define MATCHING 0x11
#define NOT_MATCHING 0x00

#define DOOR_OPENING 0x01
#define DOOR_OPENED  0xc1
#define DOOR_CLOSING 0xc2
#define DOOR_DONE 0xFF


uint8 pass1_ctrl[5], pass2_ctrl[5], permanent_pass[5];

void Receive_pass(uint8 *pass)
{
	for (uint8 i=0;i<5;i++)
	{
		pass[i] = UART_recieveByte();
		/* receive the password byte by byte from MC1 */
	}
}

void Store_pass(uint8 *pass)
{
	for(uint8 i=0;i < 5;i++)
	{
		EEPROM_writeByte(0x0311+i, pass[i]);
		_delay_ms(100);
	}
}

void Read_pass(uint8 *pass)
{
	for(uint8 i=0;i < 5;i++)
	{
		EEPROM_readByte(0x0311+i, pass[i]);
		_delay_ms(100);
	}
}

uint8 Compare_pass(uint8 *pass1,uint8 *pass2)
{
	for(uint8 i=0;i<5;i++)
	{
		if(pass1[i]!= pass2[i])
		{
			return NOT_MATCHING;
		}
	}
	return MATCHING;
}

int main(void)
{
	uint8 key_ctrl;
	uint8 saved_pass[5];
	uint8 false_attempts=0;

	SREG |= (1<<7); //enable i_bit

	Timer1_ConfigType timer1_config_type = {0,0,F_CPU_1024,NORMAL};

	TWI_ConfigType twi_config = {RATE400K,0x01};
	TWI_init(&twi_config);

	UART_ConfigType uart_config_type = {eight_bits,disabled,one_bit,9600};
	UART_init(&uart_config_type);

	DcMotor_Init();
	Buzzer_init();


	while(1)
	{
		Receive_pass(pass1_ctrl);
		Receive_pass(pass2_ctrl);


		if(Compare_pass(pass1_ctrl,pass2_ctrl) == MATCHING)
		{
			Store_pass(pass1_ctrl);
			UART_sendByte(MATCHING);
		}
		else
		{
			UART_sendByte(NOT_MATCHING);
		}
		while(1)
		{
			key_ctrl = UART_recieveByte();

			if(key_ctrl == '+')
			{
				while(1)
				{
					Read_pass(saved_pass);
					Receive_pass(pass1_ctrl);
					UART_sendByte(Compare_pass(pass1_ctrl,saved_pass));

					if(Compare_pass(pass1_ctrl,saved_pass) == MATCHING)
					{
						false_attempts = 0;
						UART_sendByte(DOOR_OPENING);
						DcMotor_Rotate(CW,100);
						_delay_ms(5000);
						UART_sendByte(DOOR_OPENED);
						DcMotor_Rotate(STOP,0);
						_delay_ms(3000);
						UART_sendByte(DOOR_CLOSING);
						DcMotor_Rotate(A_CW,100);
						_delay_ms(5000);
						UART_sendByte(DOOR_DONE);
						break;
					}
					else
					{
						false_attempts++;
						if(false_attempts == 3)
						{
							Buzzer_on();                 /*Turn the buzzer on*/
							_delay_ms(6000);
							Buzzer_off();               /*Turn the buzzer off*/
							false_attempts = 0;         /*Set the variable to value zero*/
						}
					}
					break;
				}
			}
			else if(key_ctrl == '-')
			{
				while(1)
				{
					Read_pass(saved_pass);
					Receive_pass(pass1_ctrl);
					UART_sendByte(Compare_pass(pass1_ctrl,saved_pass));

					if(Compare_pass(pass1_ctrl,saved_pass) == MATCHING)
					{
						false_attempts = 0;
						UART_recieveString(pass1_ctrl);
						UART_recieveString(pass2_ctrl);

						if(Compare_pass(pass1_ctrl,pass2_ctrl) == MATCHING)
						{
							Store_pass(pass1_ctrl);
							UART_sendByte(MATCHING);
						}
						else
						{
							UART_sendByte(NOT_MATCHING);
						}
						break;
					}
					else
					{
						false_attempts++;
						if(false_attempts == 3)
						{
							Buzzer_on();                 /*Turn the buzzer on*/
							_delay_ms(6000);
							Buzzer_off();               /*Turn the buzzer off*/
							false_attempts = 0;         /*Set the variable to value zero*/
						}
					}
					break;
				}
			}
		}
	}
}

