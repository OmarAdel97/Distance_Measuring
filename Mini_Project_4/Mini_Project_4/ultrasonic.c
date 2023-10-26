 /******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the Ultrasonic driver
 *
  * Author: Omar Adel
 *
 *******************************************************************************/

#include "gpio.h"
#include "icu.h"
#include "ultrasonic.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <util/delay.h>


 uint8 g_edgeCount = 0;
 uint16 g_timeHigh = 0;
 /*******************************************************************************
  *                      Functions Definitions                                  *
  *******************************************************************************/
 /*
  * Description : Function to initialize the Ultrasonic driver
  * 	1. Initialize the ICU configuration
  * 	2. Initialize the ICU
  * 	3. Initialize the call back function
  * 	4. Setup the Trigger PIN 6 in PORT B to be OUTPUT
  */
void Ultrasonic_init(void){
	Icu_ConfigType config = {F_CPU_8,RISING};
	Icu_init(&config);
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);

}
/*
  * Description : Function to Trigger the Ultrasonic pulse
  * 	1. Give a trigger pulse to the the trigger pin in the sensor
  * 	2. wait for 10 us
  * 	3. remove the pulse.
  */
void Ultrasonic_Trigger(void){
	GPIO_writePin(PORTB_ID, PIN5_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(PORTB_ID, PIN5_ID,LOGIC_LOW);
}

/*
  * Description : Function to read the distance to the object.
  * 	1. Use the Trigger function to send a pulse
  * 	2. Polling till the time of the echo is calculated
  * 	3. Calculate the distance.
  */

uint16 Ultrasonic_readDistance(void){
	uint16 distance = 0;
	Ultrasonic_Trigger();
	while(g_edgeCount != 2);
	g_edgeCount = 0;
	distance = 0.0175*g_timeHigh;
	return distance;
}

/*
  * Description : Function to setup the call back function
  * 	Calculate the time taken for the edge to rise and then fall.
  */

void Ultrasonic_edgeProcessing(void){
		g_edgeCount++;
		if(g_edgeCount == 1)
		{
			/*
			 * Clear the timer counter register to start measurements from the
			 * first detected rising edge
			 */
			Icu_clearTimerValue();
			/* Detect falling edge */
			Icu_setEdgeDetectionType(FALLING);
		}
		else if(g_edgeCount == 2)
		{
			/* Store the High time value */
			g_timeHigh = Icu_getInputCaptureValue();
			/* Detect rising edge */
			Icu_setEdgeDetectionType(RISING);
		}


}
