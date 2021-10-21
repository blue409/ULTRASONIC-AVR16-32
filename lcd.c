/*
 * lcd.c
 *
 *  Created on: Oct 1, 2021
 *      Author: Menna Sayed
 */
/******************************************includes**********************************************/
#include "gpio.h"
#include "common_macros.h"
#include "lcd.h"
#include "util/delay.h"

/*******************************************prototypes*******************************************/
void LCD_init(void){
	GPIO_setupPinDirection( LCD_RS_PORT_ID,LCD_RS_PIN_ID,1);   /* to configure RS,E,RW as output pin */
	GPIO_setupPinDirection(LCD_RW_PORT_ID,LCD_RW_PIN_ID,1);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,1);

	GPIO_setupPortDirection(LCD_DATA_PORT_ID,255);           /*to configure data bus 8 pins as output */

	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_COMMAND);

}


void LCD_sendCommand(uint8 command){

	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,0);
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,0);
	_delay_ms(1);                                             /*delay for processing */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,1);
	_delay_ms(1);                                               /*delay for processing */
	GPIO_writePort(LCD_DATA_PORT_ID,command);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,0);             /*disable the lcd */
}

void LCD_displayCharacter(uint8 character){
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,1);  // to display data
	GPIO_writePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,0);  //writing data on lcd
	_delay_ms(1);                                             /*delay for processing */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,1);     //enable the lcd
	_delay_ms(1);
	GPIO_writePort(LCD_DATA_PORT_ID,character);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,0);             /*disable the lcd */
	_delay_ms(1);
}

void LCD_displayString(const char *str){
	uint8 i = 0;
	while(str[i] != '\0')
	{

		 LCD_displayCharacter(str[i]); /*to display the char*/
		 i++;
		                                 /*to display next char*/
	}

}

void LCD_moveCursor(uint8 row,uint8 col){

	uint8 lcd_memory_address;
	switch(row){

	case 0 :
		lcd_memory_address=col;
		break;
	case 1 :
		lcd_memory_address=col+0x40;
		break;
	case 2:
		lcd_memory_address=col+0x10;
		break;
	case 3:
		lcd_memory_address=col+0x50;
		break;

	}

	LCD_sendCommand(lcd_memory_address|LCD_SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *str){

	LCD_moveCursor(row,col);   /*to move the cursor to the required position*/
	LCD_displayString(str);

}

void LCD_clearString()
{
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

void LCD_integerTostring(uint16 num){
	char holdstr[16];
	itoa(num,holdstr,10);  //to convert num into string and store it in holdstr,,,10 =base of decimal no.
	LCD_displayString(holdstr);

}
