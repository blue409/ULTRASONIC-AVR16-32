/*
 * Ultrasonic.c
 * Ultrasonic driver using icu module and 8 MHZ clock cpu
 *  Created on: Oct 18, 2021
 *  Author: Menna Sayed
 ************************************************************************************/
#include "Ultrasonic.h"
#include "gpio.h"
#include "ICU.h"
#include "util\delay.h"
/****************************************definitions*******************************/
static Icu_Config config={rising,F_8};                           /*to configure the icu module as you like!!*/
volatile static uint16 timer_val =0;

/****************************************Prototypes*********************************/
void Ultrasonic_init(void)
{
	icu_init(&config);                                   /*initializing the icu dynamically by passing a structure to it*/
	icu_setCallBack(Ultrasonic_edgeProcessing);         /*when the isr is excuted it calls (Ultrasonic_edgeProcessing) function*/
	GPIO_setupPinDirection(trigger_Port,trigger_Pin,PIN_OUTPUT);
//	GPIO_writePin(trigger_Port,trigger_Pin,LOGIC_LOW);

}

void Ultrasonic_Trigger(void)                     /*function to send trigger pulse to ultrasonic*/
{
	GPIO_writePin(trigger_Port,trigger_Pin,LOGIC_HIGH);
	_delay_us(200);                                      /*this number made the ultrasonic work correctly*/
	GPIO_writePin(trigger_Port,trigger_Pin,LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	return((timer_val*0.017)+1);    /*calculating the distance = speed of sound in cm x time in seconds=(34000*(timerval*10^-6))/2*/
}                                  /*i added the +1 to correct the value displayed on lcd as it displays the no to its nearest floor*/

void Ultrasonic_edgeProcessing(void)        /*function to save the high time of the pulse on the echo pin to be used in calculating the distance*/
{
	static uint8 flag =0;	           /*local variable but keeps its value stored to indicate which edge is detected*/
	if(flag==0)                        /*rising edge is captured*/
	{
	    icu_clearTimer();
	    icu_edgeType(falling);
	    flag=1;
	}
	else if(flag == 1)                  /*falling edge is captured*/
	{
		timer_val = icu_get_Captured_value();             /*to store the high time elapsed between rising edge and falling edge */
		flag =0;
		icu_clearTimer();
	    icu_edgeType(rising);
	}

}








