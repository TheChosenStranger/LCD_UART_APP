/*
 * ControlHSwitch.c
 *
 *  Created on: Mar 27, 2020
 *      Author: Norhan Nassar
 *      Version: V1.2
 */
#include "STD_TYPES.h"
#include "HSwitch_cfg.h"
#include "HSwitch.h"

/* this function initializes the switch*/
STD_ERROR ControlHSwitch_init(void)
{
	return Switch_init(void);
}

/* this function check if switch state is 1 increment counter and send it to the UART application
 * and return state again ti zero to read it again */
void ControlHSwitch_Runnable(void)
{
	static u32 counterToSend=0;
	u8 switchState = 0;
	Switch_getSwitchState(SYSTEM_SWITCH,&switchState);
	if(switchState)
	{
		counterToSend++;
		Message_Send(counterToSend, sizeof(counterToSend));
	}
	return OK;
}

/* this task will be
 * 5*2msec -> 10000
 * or more */
//task_t ControlSwitchTask = {&ControlSwitchTask,10000,0};




