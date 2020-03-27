/*
 * OS.c
 *
 *  Created on: Mar 24, 2020
 *      Author: Norhan Nassar
 */

#include "STD_TYPES.h"
#include "SYSTICK_cfg.h"
#include "SYSTICK_interface.h"
#include "OS_cfg.h"
#include "OS.h"

static u8 schedStartFlag = 0;

static taskInfo_t Systasks[MAXTASKNUM];

/* Call back function for systick handler, to increment the flag that a tick has arrived */
STD_ERROR Sched_SystickCbf(void)
{
	schedStartFlag++;				/* to handle alot of one if an interrupt cut one while running */
	return OK;
}

/* at cfg file
 * Tick time must be configured in micro sec	*/
STD_ERROR Sched_init(void)
{
	/* Init SYSTICK to make an interrupt every tick time in micro sec */
	/* NOT_OK -> 1 */
	if(SYSTICK_Init())
		return NOT_OK;
	if(SYSTICK_SetTime(TICKTIMEUS))
		return NOT_OK;
	if(SYSTICK_SetCallBack(&Sched_SystickCbf))
		return NOT_OK;

	return OK;
}

STD_ERROR Sched_Start(void)
{
	if(SYSTICK_Start())					/* Start Systick to start count */
		return NOT_OK;					/* if systick returns NOT_OK =1 so Sched_start returns NOT_OK */
	while(1)
	{
		while(!schedStartFlag);			/* when tick is arrived schedStartFlag will not be zero */
		if(schedStartFlag>0)
			schedStartFlag--;			/* here is a runnable for one flag is going to be executed */
		Sched_Runnable();				/* then Sched will be executed */
	}
	return OK;
}

/* task struct has:
 * task Periodicity -> it must be in micro sec
 * firstDelayTicks -> first delay then task start to count
 * Runnable -> task function to execute
 * taskPriority -> it will return error if it exceeds the array of tasks limit
 * and return error -> if TICKTIMEUS in cfg file is 0 */
STD_ERROR Sched_CreatTask(task_t* task,u32 taskPriority)
{
	if( (taskPriority >= MAXTASKNUM) || (TICKTIMEUS == 0) )
		return NOT_OK;
	Systasks[taskPriority].AppTask.Runnable = task->Runnable;
	Systasks[taskPriority].AppTask.Periodicity = task->Periodicity;
	Systasks[taskPriority].AppTask.firstDelayTicks = task->firstDelayTicks / task->Periodicity;
	Systasks[taskPriority].ticksToExecute = (task->Periodicity / TICKTIMEUS) - 1 ;
	Systasks[taskPriority].taskState = READY;
	Systasks[taskPriority].flagIfResume = 0;   				/* flag if a suspended task wants to be resumed again */
	return OK;													/* it is initial value is zero  	  */
}

/* taskRunnable -> address of the task call back function that you want to suspend it */
STD_ERROR Task_Suspend(taskRunnable_t taskRunnable)
{
	u8 i;
	for(i=0;i<MAXTASKNUM;i++)
	{
		if(Systasks[i].AppTask.Runnable == taskRunnable)
		{
			Systasks[i].taskState = SUSPENDED;
			return OK;
		}
	}
	return NOT_OK;
}

/* taskRunnable -> address of the task call back function that you want to resume it */
STD_ERROR Task_Resume(taskRunnable_t taskRunnable)
{
	u8 i;
	for(i=0;i<MAXTASKNUM;i++)
	{
		if(Systasks[i].AppTask.Runnable == taskRunnable)
		{
			Systasks[i].flagIfResume = 1;
			return OK;
		}
	}
	return NOT_OK;

}

/* Period -> must be in micro sec
 * and it must be larger than task periodicity time
 * taskRunnable -> address of the task call back function that you want to pause it */
STD_ERROR Task_Pause(taskRunnable_t taskRunnable, u32 Period)
{
	STD_ERROR loc_err = NOT_OK;
	/* task must be ready first to make it suspended */
	/* and Period must be larger than task Periodicity */
	u8 i;
	for(i=0;i<MAXTASKNUM;i++)
	{
		if((Systasks[i].AppTask.Runnable == taskRunnable)&&(Systasks[i].taskState == READY)&&(Period>Systasks[i].AppTask.Periodicity))
		{
			Systasks[i].taskState = PAUSED;
			Systasks[i].countIfPause = Period / Systasks[i].AppTask.Periodicity;
			loc_err = OK;
		}
	}

	return loc_err;
}

/* taskRunnable -> address of the task call back function that you want to delete it */
STD_ERROR Task_Delete(taskRunnable_t taskRunnable)
{
	u8 i;
	for(i=0;i<MAXTASKNUM;i++)
	{
		if(Systasks[i].AppTask.Runnable == taskRunnable)
		{
			Systasks[i].taskState = IDEAL;
			Systasks[i].AppTask.Runnable = NULL;
			return OK;
		}
	}
	return NOT_OK;
}

void Sched_Runnable(void)
{
	u8 i;
	for(i=0;i<MAXTASKNUM;i++)
	{
		if(Systasks[i].ticksToExecute == 0)
		{
			switch(Systasks[i].taskState)
			{
			case READY:
				if(Systasks[i].AppTask.Runnable == NULL)
					break;
				if(Systasks[i].AppTask.firstDelayTicks==0)
					Systasks[i].AppTask.Runnable();
				break;
			case PAUSED:
				Systasks[i].countIfPause--;
				if(Systasks[i].countIfPause == 0)
					Systasks[i].taskState = READY;
				break;
			case SUSPENDED:
				if(Systasks[i].flagIfResume)
				{
					Systasks[i].taskState = READY;
					Systasks[i].flagIfResume = 0;
				}
				break;
			}

			Systasks[i].ticksToExecute = (Systasks[i].AppTask.Periodicity / TICKTIMEUS) - 1 ;
		}
		else
			Systasks[i].ticksToExecute--;
	}
}




