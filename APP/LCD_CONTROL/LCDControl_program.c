/******************************/
/* Author  : Moustafa Ghareeb */
/* Version : V1.0             */
/* Date    : 27-03-2020       */
/******************************/
#include "../../LIB/STD_TYPES.h"

#include "../../HAL/HLCD/HLCD_interface.h"

#include "LCDControl_interface.h"

#define RETURN_CURSOR_STATE		0
#define	WRITE_DATA_STATE		1

/*This function initializes the LCD*/
STD_ERROR LCDControl_u8Init(void)
{
	STD_ERROR local_error;
	local_error = HLCD_u8Init();
	return local_error;
}

/*This function sends the data to be written on the LCD if there are any data*/
void LCDControl_voidRunnable(void)
{
	static u8 state = WRITE_DATA_STATE;
	if(!state)
	{
		HLCD_u8CursorPosition(0, 0);
		state = WRITE_DATA_STATE;
	}
	else	
	{
		u8 lcdData[10] = 0;
		u8 size;
		if(/*Get_UART_Rec(&lcdData,&size)==OK*/)
		{
			HLCD_u8WriteDataRequest(&lcdData, size);
			state = RETURN_CURSOR_STATE;
		}
	}
}