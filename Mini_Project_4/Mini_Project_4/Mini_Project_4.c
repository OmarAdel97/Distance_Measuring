/*
 ================================================================================================
 Name        : Mini_Project_4.c
 Author      : Omar Adel
 Description : ULTRASONIC SENSOR
 Date        : 04/06/2022
 ================================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h> /* To use the SREG register */

int main(void){


	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Initialize both the LCD and Ultrasonic driver */
	LCD_init();
	Ultrasonic_init();

	while(1)
	{
		/* display the the distance on LCD screen */
		LCD_displayStringRowColumn(0, 0, "Distance = ");
		LCD_intgerToString(Ultrasonic_readDistance());
		LCD_displayString(" cm");
	}
}
