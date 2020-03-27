/*
 * GPIO_program.c
 *
 *  Created on: Jan 27, 2020
 *      Author: Moamen
 */
#include "../../LIB/STD_TYPES.h"

#include "GPIO_interface.h"

/*works with ports A B C*/
static GPIO_x volatile * const GPIO_PORT[3] = PORTS_ARRAY;

/*	configure multiple pins with the same port and configurations
 *	parameters are
 *	Pin=(GPIO_PIN0->GPIO_PIN15) ORed together ex:(GPIO_PIN0|GPIO_PIN3|GPIO_PIN15)
 *	Port=(GPIO_PORT_A GPIO_PORT_B GPIO_PORT_C)
 *	Mode= input options
 *			GPIO_CNF_IP_ANALOG,GPIO_CNF_IP_FLOATING,GPIO_CNF_IP_PULL_UP_DOWN 
 *		  output options
 *			GPIO_CNF_GPO_PUSH_PULL,GPIO_CNF_GPO_OPEN_DRAIN,GPIO_CNF_AF_PUSH_PULL,GPIO_CNF_AF_OPEN_DRAIN
 *	Speed = GPIO_MODE_INPUT,GPIO_MODE_OUTPUT_10_MHZ,GPIO_MODE_OUTPUT_2_MHZ,GPIO_MODE_OUTPUT_50_MHZ
 */
STD_ERROR GPIO_Config(GPIO_t* p) {
	STD_ERROR res = OK;
	u8 pinNumber = 0; 	/*pin counter*/
	u16 tempPin = p->pin;
	while (tempPin != 0) {
		if (tempPin & 1) { /*find next pin to configure*/
			if (pinNumber < GPIO_CRL_THRESHOLD && p->port <= GPIO_PORT_C) {	/*pin in CRL*/
				GPIO_PORT[p->port]->CRL &= ~(GPIO_CLEAR_MASK
						<< (pinNumber * GPIO_PIN_OFFSET));					/*clear old config*/
				GPIO_PORT[p->port]->CRL |= ((p->mode | p->speed)
						<< (pinNumber * GPIO_PIN_OFFSET));					/*set new config*/
			} else if (pinNumber < GPIO_CRH_THRESHOLD && p->port <= GPIO_PORT_C) {/*pin in CRH*/
				GPIO_PORT[p->port]->CRH &=
						~(GPIO_CLEAR_MASK
								<< ((pinNumber - GPIO_CRL_THRESHOLD)
										* GPIO_PIN_OFFSET));
				GPIO_PORT[p->port]->CRH |=
						((p->mode | p->speed)
								<< ((pinNumber - GPIO_CRL_THRESHOLD)
										* GPIO_PIN_OFFSET));
			} else {
				res = NOT_OK;
			}
		}
		pinNumber++;
		tempPin = tempPin >> 1;
	}

	return res;
}

/*	Reads the value of 1 pin
*	Pin=(GPIO_PIN0->GPIO_PIN15) only 1 pin at a time
*	Port=(GPIO_PORT_A GPIO_PORT_B GPIO_PORT_C)
*	Pointer to u8 store value
*	value is 0 or 1
*/
STD_ERROR GPIO_GetPinValue(u16 Pin, u8 Port, u8* Value) {
	STD_ERROR res = OK;
	u8 tempValue = 0;
	if (((Pin & (Pin - 1)) == 0) && Port <= GPIO_PORT_C) {/*check if Pin is valid by testing if its a power of 2*/
		tempValue = GPIO_PORT[Port]->IDR | Pin;
		if (tempValue != 0)
			tempValue = 1;
	} else
		res = NOT_OK;
	*Value = tempValue;
	return res;
}
/*	Sets or clears pins, all pins are either set or cleared
*	Pin=(GPIO_PIN0->GPIO_PIN15) ORed together ex:(GPIO_PIN0|GPIO_PIN3|GPIO_PIN15)
*	Port=(GPIO_PORT_A, GPIO_PORT_B, GPIO_PORT_C)
*	Value=GPIO_HIGH,GPIO_LOW
*	
*/
STD_ERROR GPIO_SetPinValue(u16 Pin, u8 Port, u8 Value) {
	STD_ERROR res = OK;
	if (Value == GPIO_HIGH || Value == GPIO_LOW) {
		//testvar=Pin&mask;
		if (Value == GPIO_HIGH)
			GPIO_PORT[Port]->ODR |= Pin;
		else if (Value == GPIO_LOW)
			GPIO_PORT[Port]->ODR &= ~(Pin);
	} else
		res = NOT_OK;

	return res;
}
