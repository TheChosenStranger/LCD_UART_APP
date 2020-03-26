/*
 * GPIO_program.c
 *
 *  Created on: Jan 27, 2020
 *      Author: Moamen
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
static GPIO_x volatile * const GPIO_PORT[3] = PORTS_ARRAY;

STD_ERR GPIO_Config(GPIO_t* p) {
	STD_ERR res = OK;
	u8 pinNumber = 0;
	u16 tempPin = p->pin;
	while (tempPin != 0) {
		if (tempPin & 1) {
			if (pinNumber < GPIO_CRL_THRESHOLD && p->port <= GPIO_PORT_C) {
				GPIO_PORT[p->port]->CRL &= ~(GPIO_CLEAR_MASK
						<< (pinNumber * GPIO_PIN_OFFSET));
				GPIO_PORT[p->port]->CRL |= ((p->mode | p->speed)
						<< (pinNumber * GPIO_PIN_OFFSET));
			} else if (pinNumber < GPIO_CRH_THRESHOLD && p->port <= GPIO_PORT_C) {
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


STD_ERR GPIO_GetPinValue(u8 Pin, u8 Port, u8* Value) {
	STD_ERR res = 0;
	u8 tempValue = 0;
	if (Pin <= 15 && Port <= GPIO_PORT_C) {
		tempValue = GPIO_PORT[Port]->IDR | Pin;
		if (tempValue > 0)
		tempValue = 1;
	} else
	res = NOT_OK;
	*Value = tempValue;
	return res;
}
STD_ERR GPIO_SetPinValue(u16 Pin, u8 Port, u8 Value) {
	STD_ERR res = OK;
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
