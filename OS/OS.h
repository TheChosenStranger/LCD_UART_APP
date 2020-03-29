#ifndef OS_H
#define OS_H

typedef u8 taskState_t;
typedef void (*taskRunnable_t)(void);
#define NULL ((void *)0)

#define SUSPENDED			0
#define READY				1
#define PAUSED				2
#define IDEAL				3

/* struct for user */
typedef struct
{
	taskRunnable_t Runnable;			/* Pointer to Task Function */
	u32 Periodicity;					/* time in micro sec 		*/
	u32 firstDelayTicks;				/* first delay to start count from in micro sec */
} task_t;

typedef struct
{
	task_t AppTask;
	u32 ticksToExecute;
	u8 countIfPause;
	u8 flagIfResume;
	taskState_t taskState;
} taskInfo_t ;

/* at cfg file
 * Tick time must be configured in micro sec	*/
extern STD_ERROR Sched_init(void);

/* task struct has:
 * task Periodicity -> it must be in micro sec
 * firstDelayTicks -> number of ticks that scheduler stars count from
 * Runnable -> task function to execute
 * taskPriority -> it will return error if it exceeds the array of tasks limit
 * and return error -> if TICKTIMEUS in cfg file is 0 */
extern STD_ERROR Sched_CreatTask(task_t* task,u8 taskPriority);

extern STD_ERROR Sched_Start(void);

extern void Sched_Runnable(void);

/* Call back function for systick handler, to increment the flag that a tick has arrived */
extern void Sched_SystickCbf(void);

/* taskRunnable -> address of the task call back function that you want to suspend it */
extern STD_ERROR Task_Suspend(taskRunnable_t tasktosus);

/* Period -> must be in micro sec
 * and it must be larger than task periodicity time
 * taskRunnable -> address of the task call back function that you want to pause it */
extern STD_ERROR Task_Pause(taskRunnable_t taskRunnable, u8 Period);

/* taskRunnable -> address of the task call back function that you want to delete it */
extern STD_ERROR Task_Delete(taskRunnable_t taskRunnable);

/* taskRunnable -> address of the task call back function that you want to resume it */
extern STD_ERROR Task_Resume(taskRunnable_t taskRunnable);

#endif
