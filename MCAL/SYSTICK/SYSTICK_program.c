/******************************/
/* Author  : Moustafa Ghareeb */
/* Version : V1.0             */
/* Date    : 10-03-2020       */
/******************************/
#include "../../LIB/STD_TYPES.h"

#include "../SYSTICK/SYSTICK_interface.h"

/*Defining the SYSTIC registers*/
typedef struct SYSTIC_
{
	u32 CTRL;
  	u32 LOAD;
  	u32 VAL;
  	u32 CALIB;
}SYSTIC_;
/*Defining the base address for the SYSTIC and creating a struct at this base*/
#define SYSTIC_BASE_ADDRESS 0xE000E010
#define SYSTIC ((SYSTIC_ volatile * const)SYSTIC_BASE_ADDRESS)

/*This is the local pointer to funtion which will hold the address for the call back function*/
static void(*SysTick_Callbackfun)(void);

/*This function enables SYSTIC exception and sets the prescaler to none*/
STD_ERROR SYSTICK_u8Init(void)
{
	STD_ERROR local_error = OK;
	SYSTIC->CTRL = SYSTIC_PRESCALER_INIT | SYSTIC_EXCEPTION_INIT;
	return local_error;
}

/*This function sets the time for the SysTick timer in microseconds*/
STD_ERROR SYSTICK_u8SetTime(u32 Copy_Time_us)
{
	STD_ERROR local_error = OK;
	u32 bus_freq;
	u8 get_prescaler = SYSTIC->CTRL & SYSTIC_PRESCALER_INIT;
	RCC_u8GetPeripheralFreq(SYSTK,&bus_freq);
	if (get_prescaler)
	{
		SYSTIC->LOAD = (Copy_Time_us*bus_freq);
	}
	else
	{
		SYSTIC->LOAD = (Copy_Time_us*bus_freq)/SYSTIC_PRESCALER_DIV;
	}

	return local_error;
}

/*This function changes the prescaler [SYSTIC_PRESCALER_NONE - SYSTIC_PRESCALER_BY8] */
STD_ERROR SYSTICK_u8SetPrescaler(u32 Copy_Prescaler)
{
	STD_ERROR local_error = OK;
	u32 local_check = Copy_Prescaler & SYSTIC_PRESCALER_CHECK_MASK;
	if(local_check == Copy_Prescaler)
	{
		SYSTIC->CTRL &= SYSTIC_PRESCALER_CHECK_MASK;
		SYSTIC->CTRL |= Copy_Prescaler;
	}
	else
	{local_error = NOT_OK;}
	return local_error;
}

/*This function starts the SYSTIC timer*/
STD_ERROR SYSTICK_u8Start(void)
{
	STD_ERROR local_error = OK;
	SYSTIC->CTRL |= SYSTIC_START_MASK;
	return local_error;
}

/*This function stops the SYSTIC timer*/
STD_ERROR SYSTICK_u8Stop(void)
{
	STD_ERROR local_error = OK;
	SYSTIC->CTRL &= SYSTIC_STOP_MASK;
	return local_error;
}

/*This function sets the Callback function for the Systic timer*/
STD_ERROR SYSTICK_u8SetCallback(void(*Copy_ptr)(void))
{
	STD_ERROR local_error = OK;
	if(Copy_ptr)
		{SysTick_Callbackfun = Copy_ptr;}
	else
		{local_error = NOT_OK;}
	return local_error;
}

/*This is the Interrupt for the SysTick timer which calls the call back function*/
void SysTick_Handler(void)
{
	SysTick_Callbackfun();
}
