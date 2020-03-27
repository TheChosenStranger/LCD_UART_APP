/*
 * ControlHSwitch.c
 *
 *  Created on: Mar 27, 2020
 *      Author: Norhan Nassar
 *      Version: V1.2
 */
#ifndef CONTROLHSWITCH_H_
#define CONTROLHSWITCH_H_

#define SYSTEM_SWITCH	SWITCH_0

/* this function initializes the switch*/
STD_ERROR ControlHSwitch_init(void);
/* this function check if switch state is 1 increment counter and send it to the UART application
 * and return state again ti zero to read it again */
void ControlHSwitch_Runnable(void);

#endif
