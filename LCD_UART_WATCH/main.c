/*********************************************************/
/* Author  : Moamen Ahmed Moustafa Ghareeb Norhan Nassar */
/* Version : V1.0            							 */
/* Date    : 27-03-2020    							     */
/*********************************************************/
#include "./LIB/STD_TYPES.h"
/*Including OS layer*/
#include "./OS/OS.h"
/*Including MCAL layers modules*/
#include "./MCAL/RCC/RCC_interface.h"
#include "./MCAL/NVIC/NVIC_interface.h"
/*Including HAL layers modules*/
#include "./HAL/HLCD/HLCD_interface.h"
#include "./HAL/HLED/HLED_interface.h"
#include "./HAL/HSWITCH/HSwitch.h"
#include "./HAL/HUART/HUART_interface.h"
/*Including APP layers modules*/
#include "./APP/MESSAGE_RX_TX/MESSAGE_RX_TX_interface.h"
#include "./APP/LED_Control/LEDControl_interface.h"
#include "./APP/LCD_Control/LCDControl_interface.h"
#include "./APP/SWITCH_CONTROL/ControlHSwitch.h"

/*These are the tasks for the module to be run by the scheduler*/
task_t SwitchTask 	     = {HSwitch_Runnable        ,3000  ,0};
task_t ControlSwitchTask = {ControlHSwitch_Runnable ,15000 ,0};
task_t LCDControlTask    = {LCDControl_voidRunnable ,50000 ,0};
task_t LCDUpdateTask     = {HLCD_voidRunnable       ,2000  ,0};
task_t LEDControlTask    = {LEDControl_voidRunnable ,2500  ,0};

void main(void)
{
	/*Selecting systems Clk*/
	RCC_u8EnableClock(HSI);
	RCC_u8SystemClockSelect(HSI);
	/*Enabling needed peripheral*/
	RCC_u8EnablePeripheral(IOPA);
	RCC_u8EnablePeripheral(IOPB);
	RCC_u8EnablePeripheral(IOPC);
	RCC_u8EnablePeripheral(USART1);
	/*Enabling needed interrupts*/
	NVIC_EnableInterrupt(USART1);
	/*Initializing All modules*/
	Message_Init();
	ControlHSwitch_init();
	LEDControl_u8Init();
	LCDControl_u8Init();
	/*Starting the scheduler*/
	Sched_init();
	Sched_CreatTask(&SwitchTask,0);
	Sched_CreatTask(&ControlSwitchTask,1);
	Sched_CreatTask(&LCDUpdateTask,2);
	Sched_CreatTask(&LCDControlTask,3);
	Sched_CreatTask(&LEDControlTask,4);
	Sched_Start();
	while(1)
	{}
}
