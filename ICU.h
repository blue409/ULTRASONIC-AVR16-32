/*
 * ICU.h
 *
 *  Created on: Oct 18, 2021
 *  Author: Menna Sayed
 **********************************************************************************/

#ifndef ICU_H_
#define ICU_H_
#include "std_types.h"

/************************************Type Declarations****************************/
typedef enum
{
	falling,rising
}Edge_Type;

typedef	enum{   NO_Clock,F_1,F_8,F_64,F_256,F_1024   } Clock;

typedef	struct
{
	Edge_Type edge;
	Clock clock_presc;
}Icu_Config;

/************************************Prototypes***********************************/
void icu_init(const Icu_Config*);
void icu_edgeType(const Edge_Type);
void icu_clearTimer(void);                     /*to set initial value of timer to zero*/
void icu_setCallBack(void(*)(void));           /*takes pointer to a function*/
void icu_DEinit(void);                        /*to turn off the icu*/
uint16 icu_get_Captured_value(void);          /*to get value of timer stored in ICR1 reg when the edge is captured*/


#endif /* ICU_H_ */
