/*
 * App.c
 *
 *  Created on: Apr 26, 2020
 *      Author: Norhan Nassar
 */

#include "STD_TYPES.h"
#include "Sched_cfg.h"
#include "Sched.h"
#include "HSwitch_cfg.h"
#include "HSwitch.h"
#include "FRAMECONST_config.h"
#include "FRAMECONST_interface.h"
#include "USART_cfg.h"
#include "USART.h"
#include "App.h"

static void TransmitAppRunnable(void)
{
	u8 Sw_Status;
	FrameID_t FrameID = SwitchesStatus;
	u16 FrameLen = 1;								/* Frame will be one byte */
	u8 FrameData=0;
	u8 Frame;										/* Whole Frame after construct it */
	u8 CurrentSwStatus;
	for(CurrentSwStatus=0;CurrentSwStatus<NUMOFSWITCHES;CurrentSwStatus++)
	{
		HSwitch_getSwitchState(CurrentSwStatus,&Sw_Status);
		FrameData |= Sw_Status<<CurrentSwStatus;
	}
	FRAMECONST_FrameConstructor(&FrameData,FrameID,FrameLen,&Frame);				/* el mafrod hena ynady uart mosh hena 3shan hena may3rafsh hwa
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	3amal kam byte ya3ny el bytescount lesa may3rfhash */
	//USART_Send(u8* bufferData, u32 bytesCount);
}

const task_t TransmitAppTask = {TransmitAppRunnable,25};			/* HSwitch task runnable and periodicity */


