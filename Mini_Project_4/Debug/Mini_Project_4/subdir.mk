################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Mini_Project_4/Mini_Project_4.c \
../Mini_Project_4/gpio.c \
../Mini_Project_4/icu.c \
../Mini_Project_4/lcd.c \
../Mini_Project_4/ultrasonic.c 

OBJS += \
./Mini_Project_4/Mini_Project_4.o \
./Mini_Project_4/gpio.o \
./Mini_Project_4/icu.o \
./Mini_Project_4/lcd.o \
./Mini_Project_4/ultrasonic.o 

C_DEPS += \
./Mini_Project_4/Mini_Project_4.d \
./Mini_Project_4/gpio.d \
./Mini_Project_4/icu.d \
./Mini_Project_4/lcd.d \
./Mini_Project_4/ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
Mini_Project_4/%.o: ../Mini_Project_4/%.c Mini_Project_4/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


