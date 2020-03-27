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
	RCC_u8EnableClock(HSI);
	RCC_u8SystemClockSelect(HSI);
	/*Enabling needed peripheral */
	RCC_u8EnablePeripheral(IOPA);
	RCC_u8EnablePeripheral(IOPB);
	RCC_u8EnablePeripheral(IOPC);
	RCC_u8EnablePeripheral(USART1);

	/*Initializing All modules*/
	LEDControl_u8Init();
	LCDControl_u8Init();
	/*Starting the scheduler*/
	Sched_init();
	Sched_CreatTask(&LCDControlTask,2);
	Sched_CreatTask(&LEDControlTask,3);
	Sched_Start();
	while(1)
	{}
}
