/*
 * main.c
 * Read and display distance measured by ultrasonic sensor using icu module and 8 MHZ clock
 *  Created on: Oct 18, 2021
 *  Author: Menna Sayed
 ************************************************************************************/
#include "Ultrasonic.h"
#include "lcd.h"
#include "avr/io.h"
#include "util\delay.h"
int main(void){
	uint16 distance=0;
    SREG |= (1<<7);             /*to enable i-bit */
    LCD_init();
	Ultrasonic_init();
	LCD_moveCursor(0,1);
char str1[]="Distance = ";
char str2[]="cm ";
	while(1)
	{
		distance = Ultrasonic_readDistance();
		LCD_moveCursor(0,1);
		LCD_displayString(str1);
		LCD_integerTostring(distance);     /*to convert the number to string to be printed on the lcd*/
		LCD_displayString(str2);
		_delay_ms(200);             /*could be adjusted or removed depending on the lcd*/

	}

}

