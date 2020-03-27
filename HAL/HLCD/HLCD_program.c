/******************************/
/* Author  : Moustafa Ghareeb */
/* Version : V1.1             */
/* Date    : 17-03-2020       */
/******************************/
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/GPIO/GPIO_interface.h"

#include "HLCD_interface.h"

PIN_ HLCD_E  ={HLCD_E_PORT,HLCD_E_PIN,HLCD_PIN_MODE}
PIN_ HLCD_RS ={HLCD_RS_PORT,HLCD_RS_PIN,HLCD_PIN_MODE}
PIN_ HLCD_RW ={HLCD_RW_PORT,HLCD_RW_PIN,HLCD_PIN_MODE}
PIN_ HLCD_D0 ={HLCD_D0_PORT,HLCD_D0_PIN,HLCD_PIN_MODE}
PIN_ HLCD_D1 ={HLCD_D1_PORT,HLCD_D1_PIN,HLCD_PIN_MODE}
PIN_ HLCD_D2 ={HLCD_D2_PORT,HLCD_D2_PIN,HLCD_PIN_MODE}
PIN_ HLCD_D3 ={HLCD_D3_PORT,HLCD_D3_PIN,HLCD_PIN_MODE}
PIN_ HLCD_D4 ={HLCD_D4_PORT,HLCD_D4_PIN,HLCD_PIN_MODE}
PIN_ HLCD_D5 ={HLCD_D5_PORT,HLCD_D5_PIN,HLCD_PIN_MODE}
PIN_ HLCD_D6 ={HLCD_D6_PORT,HLCD_D6_PIN,HLCD_PIN_MODE}
PIN_ HLCD_D7 ={HLCD_D7_PORT,HLCD_D7_PIN,HLCD_PIN_MODE}
/*Defining private functions*/
static void HLCD_voidWriteData(u8 Copy_u8Data);
static void CLCD_voidWriteCmd(u8 Copy_u8Command);
static void HLCD_voidWriteDataCmd(u8 Copy_u8DataCmd);
/*Defining LCD STATES*/
#define	HLCD_INITIAL_STATE	0
#define	HLCD_STATE1 	1
#define	HLCD_STATE2 	2
#define	HLCD_STATE3 	3
#define	HLCD_STATE4 	4
#define	HLCD_STATE5 	5
#define	HLCD_STATE6 	6

#define HLCD_COLS		16 
#define HLCD_ROWS		2 
/*This holds the current state of the LCD*/
static u8 HLCD_state = HLCD_INITIAL_STATE;
static u8 HLCD_busy = 0;
static u8 HLCD_data_cmd[HLCD_COLS];
static u8 dataCounter;


/*This function initializes the LCD pins*/
STD_ERROR HLCD_u8Init(void)
{
	STD_ERROR local_error;
	local_error  = GPIO_u8PinConfig(HLCD_E);
	local_error |= GPIO_u8PinConfig(HLCD_RW);
	local_error |= GPIO_u8PinConfig(HLCD_RE);
	local_error |= GPIO_u8PinConfig(HLCD_D0);
	local_error |= GPIO_u8PinConfig(HLCD_D1);
	local_error |= GPIO_u8PinConfig(HLCD_D2);
	local_error |= GPIO_u8PinConfig(HLCD_D3);
	local_error |= GPIO_u8PinConfig(HLCD_D4);
	local_error |= GPIO_u8PinConfig(HLCD_D5);
	local_error |= GPIO_u8PinConfig(HLCD_D6);
	local_error |= GPIO_u8PinConfig(HLCD_D7);
	return local_error;
}

/*This function takes data to be written on the LCD*/
STD_ERROR HLCD_u8WriteDataRequest(u8* Copy_u8Data, u8 Copy_u8Size)
{
	STD_ERROR local_error = OK;
	if (!HLCD_busy) /*If the data/command reg is empty accept new data*/
	{
		u8 local_counter;
		for(local_counter = 0;local_counter<Copy_u8Size; local_counter++)
		{
			HLCD_data_cmd[local_counter] = *(Copy_u8Data+local_counter);
		}
		dataCounter = Copy_u8Size;
		HLCD_busy = 1;
	}
	else
	{
		local_error = NOT_OK;
	}
	return local_error;
}

/*This function takes command to be applied on the LCD*/
STD_ERROR HLCD_u8WriteCmdRequest(u8 Copy_u8Cmd)
{
	STD_ERROR local_error = OK;
	if (!HLCD_busy) /*If the data/command reg is empty accept new data*/
	{
		HLCD_data_cmd[0] = Copy_u8Cmd;
		dataCounter = HLCD_COLS + 1;	/*dataCounter = 17 indicates command to be written*/
		HLCD_busy = 1;
	}
	else
	{
		local_error = NOT_OK;
	}
	return local_error;
}

/*This function changes the cursor position: ROW[0-1] COL[0-1-2-3-4-5-6-7-8-9-10-11-12-13-14-15]*/
STD_ERROR HLCD_u8CursorPosition(u8 Copy_u8Row, u8 Copy_u8Column)
{
	STD_ERROR local_error;
	if(Copy_u8Row<HLCD_ROWS & Copy_u8Column<HLCD_COLS)
	{
		u8 cursor_position= (0b10000000|(Copy_u8Row<<HLCD_ROW_SHIFT)|(Copy_u8Column));
		local_error = HLCD_u8WriteCmdRequest(cursor_position);
	}
	else
	{
		local_error = NOT_OK;
	}
	
	return local_error;
}

/*This function writes data on the data pins for the LCD*/
static void HLCD_voidWriteData(u8 Copy_u8Data)
{
	/*RS is high and RW is low for writing data*/
	GPIO_u8SetPinValue(HLCD_RS,OUTPUT_HIGH);
	GPIO_u8SetPinValue(HLCD_RW,OUTPUT_LOW);
	/*Send the data to be written*/
	HLCD_voidWriteDataCmd(u8 Copy_u8Data);
	/*E pulse*/
	GPIO_u8SetPinValue(HLCD_E,OUTPUT_HIGH);
}

/*This function writes command on the data pins for the LCD*/
static void CLCD_voidWriteCmd(u8 Copy_u8Command)
{
	/*RS is low and RW is low for writing command*/
	GPIO_u8SetPinValue(HLCD_RS,OUTPUT_LOW);
	GPIO_u8SetPinValue(HLCD_RW,OUTPUT_LOW);
	/*Send the command to be written*/
	HLCD_voidWriteDataCmd(u8 Copy_u8Command);
	/*E pulse*/
	GPIO_u8SetPinValue(HLCD_E,OUTPUT_HIGH);
}

/*This function assignes the command/data bits to the corresponding data pins*/
static void HLCD_voidWriteDataCmd(u8 Copy_u8DataCmd)
{
	GPIO_u8SetPinValue(HLCD_D0,( (Copy_u8DataCmd>>HLCD_D0_BIT) & ONE_MASK) );
	GPIO_u8SetPinValue(HLCD_D1,( (Copy_u8DataCmd>>HLCD_D1_BIT) & ONE_MASK) );
	GPIO_u8SetPinValue(HLCD_D2,( (Copy_u8DataCmd>>HLCD_D2_BIT) & ONE_MASK) );
	GPIO_u8SetPinValue(HLCD_D3,( (Copy_u8DataCmd>>HLCD_D3_BIT) & ONE_MASK) );
	GPIO_u8SetPinValue(HLCD_D4,( (Copy_u8DataCmd>>HLCD_D4_BIT) & ONE_MASK) );
	GPIO_u8SetPinValue(HLCD_D5,( (Copy_u8DataCmd>>HLCD_D5_BIT) & ONE_MASK) );
	GPIO_u8SetPinValue(HLCD_D6,( (Copy_u8DataCmd>>HLCD_D6_BIT) & ONE_MASK) );
	GPIO_u8SetPinValue(HLCD_D7,( (Copy_u8DataCmd>>HLCD_D7_BIT) & ONE_MASK) );
}

void HLCD_voidRunnable(void)
{
	static u8 HLCD_E_state = 0;
	
	if (HLCD_state == HLCD_STATE6)	/*Check if the initialization sequence is complete*/
	{
		if(HLCD_E_state)	/*Make the E pin low after writing data or command*/
		{
			GPIO_u8SetPinValue(HLCD_E,OUTPUT_LOW);
			HLCD_E_state = 0;
		}
		else	/*Writing data or command per request*/
		{
			if(dataCounter>HLCD_COLS) /*Command is to be written*/
			{
				dataCounter = 0;
				CLCD_u8WriteCmd(HLCD_data_cmd[dataCounter]);
				HLCD_E_state = 1;
				
			}
			else if (dataCounter>0) /*Data is to be written*/
			{
				dataCounter--;
				CLCD_u8WriteCmd(HLCD_data_cmd[dataCounter]);
				HLCD_E_state = 1;
			
			}
			else if (!dataCounter)
			{
				HLCD_busy = 0;
			}
		}
	}
	else
	{
		switch(HLCD_state)	/*Start the initialization sequence*/
		{
			case HLCD_INITIAL_STATE:/*S0: Set up the LCD*/
			CLCD_u8WriteCmd(LINES_FONT_INIT);
			HLCD_state = HLCD_STATE1 ;
			break;

			case HLCD_STATE1 : /*S1: Make the E pin low*/	
			GPIO_u8SetPinValue(HLCD_E,OUTPUT_LOW);
			HLCD_state = HLCD_STATE2 ;
			break;
			
			case HLCD_STATE2 : /*S2: Set up the cursor*/
			CLCD_u8WriteCmd(CURSOR_INIT);
			HLCD_state = HLCD_STATE3 ;
			break;

			case HLCD_STATE3 : /*S3: Make the E pin low*/	
			GPIO_u8SetPinValue(HLCD_E,OUTPUT_LOW);
			HLCD_state = HLCD_STATE4 ;
			break;

			case HLCD_STATE4 : /*S4: Clear the display*/
			CLCD_u8WriteCmd(CLEAR_DISPLAY);
			HLCD_state = HLCD_STATE5 ;
			break;
			
			case HLCD_STATE5 :  /*S5: Make the E pin low*/
			GPIO_u8SetPinValue(HLCD_E,OUTPUT_LOW);
			HLCD_state = HLCD_STATE6 ;
			break;
		}
	}
}