/*
 * ICU.c
 * ICU Driver can be dynamically configured
 *  Created on: Oct 18, 2021
 *  Author: Menna Sayed
 **********************************************************************************/
#include "ICU.h"
#include "common_macros.h"
#include "avr/io.h"
#include "avr/interrupt.h"
/********************************Global variables***********************************/
static volatile void(*g_callBackptr)(void) = NULL_PTR;

/**********************************Function Definitions*****************************/

void icu_init(const Icu_Config*config_ptr)
{

    CLEAR_BIT(DDRD,PD6);             //input pin to MCU

	TCCR1A =0;
	SET_BIT(TCCR1A,FOC1A);
	SET_BIT(TCCR1A,FOC1B);
	TCCR1B=0;
	switch(config_ptr->edge)        /*configure the edge to be detected as in the input structure */
	{
	case 0:                 //already cleared/
		break;
	case 1:                  //setting the bit/
		SET_BIT(TCCR1B,ICES1);
		break;
	}
	switch(config_ptr->clock_presc)      /*configure the clock and prescaler as in the input structure*/
	{
	    case 0:
			break;
		case 1:
			SET_BIT(TCCR1B,CS10);
			break;
		case 2:
			SET_BIT(TCCR1B,CS11);
			break;
		case 3:
			SET_BIT(TCCR1B,CS10);
			SET_BIT(TCCR1B,CS11);
			break;
		case 4:
			SET_BIT(TCCR1B,CS12);
			break;
		case 5:
			SET_BIT(TCCR1B,CS10);
			SET_BIT(TCCR1B,CS12);
			break;
	}
	                      /*set initial value for timer and ICR1 regs.*/
  TCNT1 = 0;
  ICR1 = 0;

  TIMSK=0;
  SET_BIT(TIMSK,TICIE1);      /*module int enabled*/

}

void icu_edgeType(const Edge_Type edge)
{
   TCCR1B = (TCCR1B & 0xBF) | (edge<<6);   /*first section for masking the reg with 1 except the bit 6 with zero*/
}

void icu_clearTimer(void)
{
	TCNT1 = 0;
}

void icu_setCallBack(void(*ptr_func)(void))   /*we save the address of the call back function which is passed to this func*/
{
    g_callBackptr = ptr_func;
}

void icu_DEinit(void)          /*to disable the icu driver*/
{
	TCCR1A =0;
	TCCR1B =0;
	TCNT1 = 0;
	ICR1 = 0;
	TIMSK &= ~(1<<TICIE1);
}

uint16 icu_get_Captured_value(void)
{
	return ICR1;              /*return the value stored in timer reg when edge is captured*/
}

ISR (TIMER1_CAPT_vect)
{
	if(g_callBackptr != NULL_PTR)  /*if the pointer points to a function enter the cond*/
	{
		g_callBackptr();        /*we call the call back function we point at using the pointer*/
	}
}

