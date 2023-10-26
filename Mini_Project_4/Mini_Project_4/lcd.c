 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
  * Author: Omar Adel
 *
 *******************************************************************************/

#include "gpio.h"
#include "lcd.h"
#include "common_macros.h" /* To use the macros like SET_BIT */



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */

void LCD_init(void){
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID, PIN_OUTPUT);  /*SET Directions of PINS 0,1,2 in PORTD*/
	GPIO_setupPinDirection(LCD_RW_PORT_ID,LCD_RW_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID, PIN_OUTPUT);

#if (LCD_DATA_BITS_MODE == 4)
	/* Configure 4 pins in the data port as output pins */
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID+1,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID+2,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID+3,PIN_OUTPUT);

	LCD_sendCommand(LCD_GO_TO_HOME);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);/*2 lines + 4 - bit Mode*/

#elif (LCD_DATA_BITS_MODE == 8)
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT); /* Set PORTC Direction*/
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);/*2 lines + 8 - bit Mode*/

#endif
	LCD_sendCommand(LCD_CURSOR_OFF); /*Curser Off*/
	LCD_sendCommand(LCD_CLEAR_COMMAND); /*Clear Screen*/
}
/*
 * Description :
 * Setup the Send command function for the LCD driver
 * Following the Datasheet's AC characteristics steps to complete the function send command
 */
void LCD_sendCommand(uint8 command){

	uint8 lcd_port_value = 0;
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW); 		/*Set RS = 0*/
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW); 		/*Set R/W = 0*/
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); 	/*Set Enable = 1*/
	_delay_ms(1);

#if(LCD_DATA_BITS_MODE == 4)
	/* out the last 4 bits of the required command to the data bus D4 --> D7 */
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | (command & 0xF0);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | ((command & 0xF0) >> 4);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the first 4 bits of the required command to the data bus D4 --> D7 */
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | ((command & 0x0F) << 4);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | (command & 0x0F);
#endif

	GPIO_writePort(LCD_DATA_PORT_ID, command);				/*write the command in PORTB*/
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);		/*Set Enable = 0*/
	_delay_ms(1);

#elif (LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID,command); /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}
/*
 * Description :
 * Setup the Send Data function for the LCD driver
 * Following the Datasheet's AC characteristics steps to complete the function send data
 */
void LCD_displayCharacter(uint8 data){
	uint8 lcd_port_value = 0;
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH); 		/*Set RS = 1*/
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW); 		/*Set R/W = 0*/
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); 	/*Set Enable = 1*/
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
	/* out the last 4 bits of the required data to the data bus D4 --> D7 */
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | (data & 0xF0);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | ((data & 0xF0) >> 4);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the first 4 bits of the required data to the data bus D4 --> D7 */
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | ((data & 0x0F) << 4);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | (data & 0x0F);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif (LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID,data); /* out the required data to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}
void LCD_displayString(const char*Str){
	uint8 i = 0;

	while(Str[i] != '\0'){
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_displayString(buff); /* Display the string */
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}

