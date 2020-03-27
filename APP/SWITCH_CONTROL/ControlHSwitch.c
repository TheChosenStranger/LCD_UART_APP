/*
 * ControlHSwitch.c
 *
 *  Created on: Mar 27, 2020
 *      Author: Norhan Nassar
 *      Version: V1.2
 */
#include "../../LIB/STD_TYPES.h"
#include "../MESSAGE_RX_TX/MESSAGE_RX_TX_interface.h"
#include "../../HAL/HSwitch/HSwitch_cfg.h"
#include "../../HAL/HSwitch/HSwitch.h"
#include "ControlHSwitch.h"

/* this function initializes the switch*/
STD_ERROR ControlHSwitch_init(void)
{
	return HSwitch_init();
}

/* this function check if switch state is 1 increment counter and send it to the UART application
 * and return state again ti zero to read it again */
void ControlHSwitch_Runnable(void)
{
	static u32 counterToSend=0;
	u8 switchState = 0;
	HSwitch_getSwitchState(SYSTEM_SWITCH,&switchState);
	if(switchState)
	{
		counterToSend++;
		Message_Send(counterToSend, sizeof(counterToSend));
	}
}
