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
#include "OS_cfg.h"
#include "OS.h"

/* Create Switch task to read Switch status every 2msec and first delay is eqqual to 0 */
task_t SwitchTask = {&HSwitch_Runnable,2000,0};

extern u8 switchState[SWITCHES_NUMBER];

/* this function check if switch state is 1 increment counter and send it to the UART application
 * and return state again ti zero to read it again */
STD_ERROR ControlHSwitch()
{
	static u32 counterToSend=0;
	if(switchState[SWITCH_0])
	{
		counterToSend++;
		/* call uart send to send to it this number */
	}
	return OK;
}

/* this task will be
 * 5*2msec -> 10000
 * or more */
//task_t ControlSwitchTask = {&ControlSwitchTask,10000,0};




