/*
 * Ultrasonic.h
 *
 *  Created on: Oct 18, 2021
 *  Author: Menna Sayed
 *************************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "std_types.h"
#include "ICU.h"

/***********************************Pin Deinitions***********************************/
#define trigger_Pin          PIN5_ID
#define trigger_Port         PORTB_ID
//echo pin is always on pin6 in portD
/***********************************Prototypes***************************************/


void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
