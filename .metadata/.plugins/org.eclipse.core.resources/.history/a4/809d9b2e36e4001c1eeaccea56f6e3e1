 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Omar Adel
 *
 *******************************************************************************/
#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include <util/delay.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define LCD_DATA_BITS_MODE 8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

#if (LCD_DATA_BITS_MODE == 4)

/* if LCD_LAST_PORT_PINS is defined in the code, the LCD driver will use the last 4 pins in the gpio port for for data.
 * To use the first four pins in the gpio port for data just remove LCD_LAST_PORT_PINS */
#define LCD_LAST_PORT_PINS

#ifdef LCD_LAST_PORT_PINS
#define LCD_FIRST_DATA_PIN_ID         PIN4_ID
#else
#define LCD_FIRST_DATA_PIN_ID         PIN0_ID
#endif

#endif


/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT_ID                 PORTD_ID
#define LCD_RS_PIN_ID                  PIN0_ID

#define LCD_RW_PORT_ID                 PORTD_ID
#define LCD_RW_PIN_ID                  PIN1_ID

#define LCD_E_PORT_ID                  PORTD_ID
#define LCD_E_PIN_ID                   PIN2_ID

#define LCD_DATA_PORT_ID               PORTC_ID

/* LCD Commands */
#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void LCD_init(void);

/*
 * Description :
 * Setup the Send command function for the LCD driver
 * Following the Datasheet's AC characteristics steps to complete the function send command
 */
void LCD_sendCommand(uint8 command);

/*
 * Description :
 * Setup the Send Data function for the LCD driver
 * Following the Datasheet's AC characteristics steps to complete the function send data
 */
void LCD_displayCharacter(uint8 data);

void LCD_displayString(const char*Str);

void LCD_moveCursor(uint8 row,uint8 col);

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);

void LCD_intgerToString(int data);


void LCD_clearScreen(void);


#endif /* LCD_H_ */
