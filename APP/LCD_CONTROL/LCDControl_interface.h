/******************************/
/* Author  : Moustafa Ghareeb */
/* Version : V1.0             */
/* Date    : 27-03-2020       */
/******************************/
#ifndef LCD_CONTROL_INTERFACE_H_
#define LCD_CONTROL_INTERFACE_H_

STD_ERROR LCDControl_u8Init(void);
void LCDControl_voidRunnable(void);

/*The task for the module to be run by the scheduler*/
task_t LCDControlTask =
{
	LCDControl_voidRunnable,
	500,
	0
};

#endif
