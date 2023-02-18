/******************************************************************************
 *
 * Module: I2C
 *
 * File Name: i2c.h
 *
 * Description: Source file for the I2C AVR driver
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/
#include <avr/io.h>
#include "i2c.h"
#include "common_macros.h"

/*
 * Description :
 * function to initialize I2C driver.
 */
void TWI_init(const TWI_ConfigType * Config_Ptr)
{
	uint8 baud_rate = 0;
	baud_rate = (uint8)(((FCPU/(Config_Ptr->bit_rate))-16)/2);
	TWBR = baud_rate;
	TWSR = PRESCALER_1;
	TWAR = (Config_Ptr->address)<<1; //write address
	TWCR |= (1<<TWEN); // enable i2c
}

/*
 * Description :
 * function to send start bit.
 */
void TWI_start(void)
{
    /*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /*wait until the start bit is send*/
	while(BIT_IS_CLEAR(TWCR,TWINT));

}

/*
 * Description :
 * function to send stop bit.
 */
void TWI_stop(void)
{
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

}

/*
 * Description :
 * function to write byte.
 */
void TWI_writeByte(uint8 data)
{
	TWDR = data; //write data

	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*
 * Description :
 * function to read byte with acknowledge.
 */
uint8 TWI_readByteWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}

/*
 * Description :
 * function to read byte with negative acknowledge.
 */
uint8 TWI_readByteWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

/*
 * Description :
 * function to get the status of I2C.
 */
uint8 TWI_getStatus(void)
{
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & 0xF8;
	return status;
}

