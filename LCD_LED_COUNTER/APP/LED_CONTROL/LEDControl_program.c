/******************************/
/* Author  : Moustafa Ghareeb */
/* Version : V1.0             */
/* Date    : 27-03-2020       */
/******************************/
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../HAL/HLED/HLED_config.h"
#include "../../HAL/HLED/HLED_interface.h"
#include "LEDControl_interface.h"

u8 TogLED;

/*This function initializes the LED*/
STD_ERROR LEDControl_u8Init(void)
{
	STD_ERROR local_error;
	local_error  = HLED_Init();
	local_error |= HLED_LedOff(INDICATOR_LED);
	return local_error;
}

/*This function toggles the LCD with every data reception*/
void LEDControl_voidRunnable(void)
{
	static u8 led_state = 1;
	if(TogLED)
	{
		TogLED = 0;
		if(led_state)
		{
			HLED_LedOn(INDICATOR_LED);
			led_state = 0;
		}
		else
		{
			HLED_LedOff(INDICATOR_LED);
			led_state = 1;
		}
	}
}
