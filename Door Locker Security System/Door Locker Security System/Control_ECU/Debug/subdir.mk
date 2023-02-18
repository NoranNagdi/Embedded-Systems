################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Control_Ecu.c \
../buzzer.c \
../dc_motor.c \
../eeprom.c \
../gpio.c \
../i2c.c \
../timer.c \
../timer1.c \
../uart.c 

OBJS += \
./Control_Ecu.o \
./buzzer.o \
./dc_motor.o \
./eeprom.o \
./gpio.o \
./i2c.o \
./timer.o \
./timer1.o \
./uart.o 

C_DEPS += \
./Control_Ecu.d \
./buzzer.d \
./dc_motor.d \
./eeprom.d \
./gpio.d \
./i2c.d \
./timer.d \
./timer1.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


