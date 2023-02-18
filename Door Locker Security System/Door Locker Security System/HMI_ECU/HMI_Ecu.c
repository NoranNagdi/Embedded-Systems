 /******************************************************************************
 *
 * File Name: HMI_Ecu.c
 *
 * Description: Source file for the Human Machine Interface ECU
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "timer1.h"
#include <util/delay.h>
#include <avr/io.h>


#define MATCHING 0x11
#define NOT_MATCHING 0x00

#define DOOR_OPENING 0x01
#define DOOR_OPENED  0xc1
#define DOOR_CLOSING 0xc2
#define DOOR_DONE 0xFF

uint16 g_tick = 0;
uint8 *pass1,*pass2;

void tick(void)
{
	g_tick++;
}

void enterPassword(uint8 *password1)
{
	for(uint8 i=0; i<5; i++)
	{
		password1[i] = KEYPAD_getPressedKey();
		//_delay_ms(1000);
		LCD_displayCharacter('*');
		//_delay_ms(500);
	}
	/*wait for enter button to be pressed*/
	while(KEYPAD_getPressedKey() != '=');
	//_delay_ms(1000);
}

void sendPassword(uint8 *pass)
{
	for(uint8 i=0; i < 5;i++)/*loop for send the password*/
	{
		UART_sendByte(pass[i]);/* send the password by U-ART byte by byte */
	}
	//UART_sendString(pass);
}


int main(void)
{
	uint8 key_hmi;
	uint8 false_attempts=0;

	SREG |= (1<<7); //enable i_bit

	Timer1_ConfigType timer1_config_type = {0,0,F_CPU_1024,NORMAL};

	UART_ConfigType uart_config_type = {eight_bits,disabled,one_bit,9600};
	LCD_init();
	UART_init(&uart_config_type);


	while(1)
    {
		do
		{
			/*entering pass for first time*/
			LCD_clearScreen();
			LCD_displayString("Plz enter pass:");
			LCD_moveCursor(1,0);
			enterPassword(pass1);
			sendPassword(pass1);

			LCD_clearScreen();

			LCD_displayString("Plz re-enter the same pass:");
			LCD_moveCursor(1,12);
			enterPassword(pass2);
			sendPassword(pass2);

			if(UART_recieveByte() == NOT_MATCHING)
			{
				LCD_clearScreen();
				LCD_displayString("NOT MATCHING");
				continue;
			}
		}
		while(UART_recieveByte() == NOT_MATCHING);
		_delay_ms(20);

		while(1)
		{
			/*STEP 2: Main Options*/
			LCD_clearScreen();
			LCD_displayString("+ : Open Door");
			LCD_moveCursor(1,0);
			LCD_displayString("- : Change Pass");

			key_hmi = KEYPAD_getPressedKey();
			_delay_ms(1000);
			while((key_hmi != '+') || (key_hmi != '-'));
			UART_sendByte(key_hmi);

			if(key_hmi == '+')
			{
				while(1)
				{
					LCD_clearScreen();
					LCD_displayString("plz enter pass:");
					enterPassword(pass1);
					sendPassword(pass1);

					if(UART_recieveByte() == NOT_MATCHING)
					{
						LCD_clearScreen();
						LCD_displayStringRowColumn(0,0,"Wrong Pass");
						_delay_ms(1000);
						false_attempts++;

						if(false_attempts == 3)
						{
							LCD_clearScreen();
							LCD_displayString("ERROR");
							false_attempts = 0;
							_delay_ms(60000);
							break;
						}
						else
						{
							continue;
						}
					}
					else
					{
						while(UART_recieveByte() != (DOOR_DONE))
						{
							if(UART_recieveByte() == (DOOR_OPENING))
							{
								LCD_clearScreen();
								LCD_displayString("Unlocking Door");
							}
							else if(UART_recieveByte() == (DOOR_OPENED))
							{
								LCD_clearScreen();
								LCD_displayString("Door Opened");
							}
							else if(UART_recieveByte() == (DOOR_CLOSING))
							{
								LCD_clearScreen();
								LCD_displayString("Locking Door");
							}
						}
					}
					break;
				}
			}
			else if(key_hmi == '-')
			{
				while(1)
				{
					LCD_clearScreen();
					LCD_displayString("plz enter pass:");
					enterPassword(pass1);
					sendPassword(pass1);

					if(UART_recieveByte() == NOT_MATCHING)
					{
						LCD_clearScreen();
						LCD_displayStringRowColumn(0,0,"Wrong Pass");
						_delay_ms(1000);
						false_attempts++;

						if(false_attempts == 3)
						{
							LCD_clearScreen();
							LCD_displayString("ERROR");
							false_attempts = 0;
							_delay_ms(60000);
							break;
						}
						else
						{
							continue;
						}
					}
					else
					{
						do
						{
							LCD_clearScreen();
							LCD_displayString("Plz enter pass:");
							LCD_moveCursor(1,0);
							enterPassword(pass1);
							sendPassword(pass1);

							LCD_clearScreen();

							/*re-entering pass*/
							LCD_displayString("Plz re-enter the same pass:");
							LCD_moveCursor(1,12);
							enterPassword(pass2);
							sendPassword(pass2);

							if(UART_recieveByte() == NOT_MATCHING)
							{
								LCD_clearScreen();
								LCD_displayString("NOT MATCHING");
								continue;
							}
						}
						while(UART_recieveByte() == NOT_MATCHING);
					}
					break;
				}
			}
		}
    }
}

