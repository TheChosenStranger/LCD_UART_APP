#ifndef HLED_INTERFACE_H
#define HLED_INTERFACE_H

#define INDICATOR_LED	LED_0

STD_ERROR LEDControl_u8Init(void);
void LEDControl_voidRunnable(void);

/*The task for the module to be run by the scheduler*/
task_t LCDControlTask
{
	LEDControl_voidRunnable;
	500;
	100;
} ;


#endif
