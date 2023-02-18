/******************************************************************************
 *
 * Module: I2C
 *
 * File Name: i2c.h
 *
 * Description: header file for the I2C AVR driver
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/
#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

#define FCPU              8000000UL

/*******************************************************************************
 *                         Types Declarations                                  *
 *******************************************************************************/

typedef uint8 TWI_Address;
typedef uint32 TWI_BaudRate;


typedef enum{
	PRESCALER_1,PRESCALER_4,PRESCALER_16,PRESCALER_64
}TWI_Prescaler;


typedef struct{
	TWI_BaudRate bit_rate;
	TWI_Address address;
}TWI_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * function to initialize I2C driver.
 */

void TWI_init(const TWI_ConfigType * Config_Ptr);

/*
 * Description :
 * function to send start bit.
 */
void TWI_start(void);

/*
 * Description :
 * function to send stop bit.
 */
void TWI_stop(void);

/*
 * Description :
 * function to write byte.
 */
void TWI_writeByte(uint8 data);

/*
 * Description :
 * function to read byte with acknowledge.
 */
uint8 TWI_readByteWithACK(void);

/*
 * Description :
 * function to read byte with negative acknowledge.
 */
uint8 TWI_readByteWithNACK(void);

/*
 * Description :
 * function to get the status of I2C.
 */
uint8 TWI_getStatus(void);


#endif /* I2C_H_ */
