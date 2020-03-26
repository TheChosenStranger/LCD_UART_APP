/*
 * OS.c
 *
 *  Created on: Mar 23, 2020
 *      Author: Norhan Nassar
 */

#include "../../LIB/STD_TYPES.h"
#include "../MCAL/SYSTIC/SYSTICK_interface.h"
#include "OS_cfg.h"
#include "OS.h"

typedef struct
{
	task_t* AppTask;
	u32 ticksToExecute;
	u8 countIfPause;
	u8 flagIfResume; //0
	taskState_t taskState;
} taskInfo_t ;

static u8 schedStartFlag = 0;

static taskInfo_t* Systasks[MAXTASKNUM];

/* Call back fuction for systick handler it is to increment the flag that a tick has arrived */
void Sched_SystickCbf(void)
{
	schedStartFlag++;				/* to handle alot of one, if an interrupt cut one while running */
}

STD_ERROR Sched_init(void)
{
	/* Init SYSTICK to make an interrupt every tick time in micro sec */
	if(!SYSTICK_Init())
		return NOT_OK;
	if(!SYSTICK_SetTime(TICKTIMEUS))
		return NOT_OK;
	if(!SYSTICK_SetCallBack(&Sched_SystickCbf))
		return NOT_OK;

	return OK;
}

STD_ERROR Sched_Start(void)
{
	if(SYSTICK_Start() == NOT_OK )		/* Start Systick to start count */
		return NOT_OK;
	while(1)
	{
		while(!schedStartFlag);			/* when tick is arrived schedStartFlag will be 1 */
		if(schedStartFlag>0)
			schedStartFlag--;			/* here is a runnable for one flag is going to be executed */
		Sched_Runnable();				/* then Sched will be executed */
	}
	return OK;
}

STD_ERROR Sched_CreatTask(task_t* task,u32 taskPriority)
{
	if( (taskPriority >= MAXTASKNUM) || (TICKTIMEUS == 0) )
		return NOT_OK;
	Systasks[taskPriority]->AppTask->Runnable = task->Runnable;
	Systasks[taskPriority]->AppTask->Periodicity = task->Periodicity;
	Systasks[taskPriority]->AppTask->firstDelayTicks = task->firstDelayTicks;
	Systasks[taskPriority]->ticksToExecute = (task->Periodicity / TICKTIMEUS) - 1 ;
	Systasks[taskPriority]->taskState = READY;
	Systasks[taskPriority]->flagIfResume = 0;   //initial value 0
	return OK;
}

STD_ERROR Task_Suspend(taskRunnable_t taskRunnable)
{
	u32 i;
	for(i=0;i<MAXTASKNUM;i++)
	{
		if(Systasks[i]->AppTask->Runnable == taskRunnable)
		{
			Systasks[i]->taskState = SUSPENDED;
			return OK;
		}
	}
	return NOT_OK;
}

STD_ERROR Task_Resume(taskRunnable_t taskRunnable)
{
	u32 i;
	for(i=0;i<MAXTASKNUM;i++)
	{
		if(Systasks[i]->AppTask->Runnable == taskRunnable)
		{
			Systasks[i]->flagIfResume = 1;
			return OK;
		}
	}
	return NOT_OK;

}

STD_ERROR Task_Pause(taskRunnable_t taskRunnable, u32 Period)
{
	STD_ERROR loc_err = NOT_OK;
	/* task must be ready first to make it suspended */
	/* and Period must be larger than task Periodicity */
	u32 i;
	for(i=0;i<MAXTASKNUM;i++)
	{
		if((Systasks[i]->AppTask->Runnable == taskRunnable)&&(Systasks[i]->taskState == READY)&&(Period>Systasks[i]->AppTask->Periodicity))
		{
			Systasks[i]->taskState = PAUSED;
			Systasks[i]->countIfPause = Period / Systasks[i]->AppTask->Periodicity;
			loc_err = OK;
		}
	}

	return loc_err;
}

STD_ERROR Task_Delete(taskRunnable_t taskRunnable)
{
	u32 i;
	for(i=0;i<MAXTASKNUM;i++)
	{
		if(Systasks[i]->AppTask->Runnable == taskRunnable)
		{
			Systasks[i]->taskState = IDEAL;
			Systasks[i]->AppTask->Runnable = NULL;
			return OK;
		}
	}
	return NOT_OK;
}

void Sched_Runnable(void)
{
	u32 i;
	for(i=0;i<MAXTASKNUM;i++)
	{
		if(Systasks[i]->ticksToExecute == 0)
		{
			switch(Systasks[i]->taskState)
			{
			case READY:
				if(Systasks[i]->AppTask->Runnable == NULL)
					break;
				Systasks[i]->AppTask->Runnable();
				break;
			case PAUSED:
				Systasks[i]->countIfPause--;
				if(Systasks[i]->countIfPause == 0)
					Systasks[i]->taskState = READY;
				break;
			case SUSPENDED:
				if(Systasks[i]->flagIfResume)
				{
					Systasks[i]->taskState = READY;
					Systasks[i]->flagIfResume = 0;
				}
				break;
			}

			Systasks[i]->ticksToExecute = (Systasks[i]->AppTask->Periodicity / TICKTIMEUS) - 1 ;
		}
		else
			Systasks[i]->ticksToExecute--;
	}
}




