/********************************************************/
/* Author  : Moamen Ahmed Moustafa Ghareeb Norhan Nassar*/
/* Version : V1.0            							*/
/* Date    : 21-03-2020    							    */
/********************************************************/
#include "./LIB/STD_TYPES.h"
/*Including MCAL layers modules*/
#include "./MCAL/GPIO/GPIO_interface.h"
#include "./MCAL/RCC/RCC_interface.h"
#include "./MCAL/NVIC/NVIC_interface.h"
#include "./MCAL/SYSTIC/SYSTIC_interface.h"
#include "./MCAL/UART/UART_interface.h"
/*Including HAL layers modules*/
#include "./HAL/HLCD/HLCD_interface.h"
#include "./HAL/HLED/HLED_interface.h"
#include "./HAL/HSWITCH/HSWITCH_interface.h"
#include "./HUART/HUART/HUART_interface.h"
/*Including APP layers modules*/
#include "./APP/LEDControl/LEDControl_interface.h"
#include "./APP/LCDControl/LCDControl_interface.h"

void main(void)
{
	/*Selecting systems Clk*/
	/*Enable GPIOs Clocks*/

	/*Initializing All modules*/
	SYSTICK_u8Init();

	LEDControl_u8Init();
	LCDControl_u8Init();
	/*Starting the scheduler*/
	Sched_init();
	Sched_CreatTask(&LCDControlTask,2);
	Sched_CreatTask(&LEDControlTask,3);
	SYSTICK_u8SetTime(1000);	/*1000 us*/
	SYSTICK_u8SetCallback(Sched_SystickCbf);
	Sched_Start();
}
