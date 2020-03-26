#ifndef OS_H
#define OS_H

typedef u8 taskState_t;
#define NULL ((void *)0)

#define SUSPENDED			0
#define READY				1
#define PAUSED				2
#define IDEAL				3

typedef struct
{
	taskRunnable_t Runnable;			/* Pointer to Task Function */
	u32 Periodicity;
	u32 firstDelayTicks;				/* Number of ticks to start task at it */
} task_t;

extern STD_ERROR Sched_init(void);
/* taskPriority -> it will return error if it exceeds the array of tasks limit 
 * task struct has:
 * task Periodicity -> it must be in micro sec
 * firstDelayTicks -> number of ticks that scheduler stars count from
 * Runnable -> task function to execute */
extern STD_ERROR Sched_CreatTask(task_t* task,u32 taskPriority);
extern STD_ERROR Sched_Start(void);
extern void Sched_Runnable(void);
extern void Sched_SystickCbf(void);
extern STD_ERROR Task_Suspend(taskRunnable_t tasktosus);
/* Period -> must be in micro sec
 * and it must be smaller than task periodicity time
 * Copy_taskID -> must be one of the application tasks id */
extern STD_ERROR Task_Pause(taskRunnable_t taskRunnable, u32 Period);
extern STD_ERROR Task_Delete(taskRunnable_t taskRunnable);
extern STD_ERROR Task_Resume(taskRunnable_t taskRunnable);
#endif
