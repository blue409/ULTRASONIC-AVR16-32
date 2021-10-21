 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *  Created on: Oct 1, 2021
 *  Author: Menna Sayed
 ********************************************************************************/


#ifndef LCD_H_
#define LCD_H_
#include "std_types.h"


/*******************************pins connection definitions**********************/
#define LCD_RS_PORT_ID                 PORTB_ID
#define LCD_RS_PIN_ID                  PIN0_ID

#define LCD_RW_PORT_ID                 PORTB_ID
#define LCD_RW_PIN_ID                  PIN1_ID

#define LCD_E_PORT_ID                  PORTB_ID
#define LCD_E_PIN_ID                   PIN2_ID

#define LCD_DATA_PORT_ID               PORTA_ID

/* LCD Commands */
#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80


/********************************function protoypes******************************/
void LCD_init(void);
void LCD_sendCommand(uint8);
void LCD_displayCharacter(uint8);
void LCD_displayString(const char *str);
void LCD_moveCursor(uint8,uint8 );
void LCD_displayStringRowColumn(uint8,uint8,const char *);
void LCD_clearString();
void LCD_integerTostring(uint16);


#endif /* LCD_H_ */
