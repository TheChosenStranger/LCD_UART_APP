/******************************/
/* Author  : Moustafa Ghareeb */
/* Version : V1.3             */
/* Date    : 04-04-2020       */
/******************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "HLCD_interface.h"
#include "HLCD_config.h"

/*Defining LCD STATES*/
#define	HLCD_INITIAL_STATE				0
#define	HLCD_SETUP_LCD_STATE 			1
#define	HLCD_SETUP_CURSOR_STATE 		2
#define	HLCD_EPIN_RESET1_STATE 			3
#define	HLCD_DISPLAY_CLEAR_STATE	 	4
#define	HLCD_EPIN_RESET2_STATE			5
#define	HLCD_INITIALIZATION_COMPLETE 	6
/*Defining max number for columns and rows*/
#define HLCD_COLS		16 
#define HLCD_ROWS		2 
/*Defining the counter before the init sequence*/
#define INIT_SEQ_COUNTER	20
/*Defining LCD Pins as PIN_ struct type*/
static  PIN_ HLCD_RS ={HLCD_RS_PORT,HLCD_RS_PIN,HLCD_PIN_MODE};
static  PIN_ HLCD_RW ={HLCD_RW_PORT,HLCD_RW_PIN,HLCD_PIN_MODE};
static  PIN_ HLCD_E  ={HLCD_E_PORT,HLCD_E_PIN,HLCD_PIN_MODE};
static  PIN_ HLCD_D0 ={HLCD_D0_PORT,HLCD_D0_PIN,HLCD_PIN_MODE};
static  PIN_ HLCD_D1 ={HLCD_D1_PORT,HLCD_D1_PIN,HLCD_PIN_MODE};
static  PIN_ HLCD_D2 ={HLCD_D2_PORT,HLCD_D2_PIN,HLCD_PIN_MODE};
static  PIN_ HLCD_D3 ={HLCD_D3_PORT,HLCD_D3_PIN,HLCD_PIN_MODE};
static  PIN_ HLCD_D4 ={HLCD_D4_PORT,HLCD_D4_PIN,HLCD_PIN_MODE};
static  PIN_ HLCD_D5 ={HLCD_D5_PORT,HLCD_D5_PIN,HLCD_PIN_MODE};
static  PIN_ HLCD_D6 ={HLCD_D6_PORT,HLCD_D6_PIN,HLCD_PIN_MODE};
static  PIN_ HLCD_D7 ={HLCD_D7_PORT,HLCD_D7_PIN,HLCD_PIN_MODE};
/*Defining private functions*/
static void HLCD_voidWriteData(u8 Copy_u8Data);
static void HLCD_voidWriteCmd(u8 Copy_u8Command);
static void HLCD_voidWriteDataCmd(u8 Copy_u8DataCmd);
static void HLCD_voidInitializationSequence(void);
/*This holds the current state of the LCD*/
static u8 HLCD_state = HLCD_INITIAL_STATE;
static u8 HLCD_busy = 0;
static u8 HLCD_data_cmd[HLCD_COLS];
static u8 dataCounter;
static u8 write_data_counter;

/*This function initializes the LCD pins*/
u8 HLCD_u8Init(void)
{
	u8 local_error;
	local_error  = GPIO_u8PinConfig(&HLCD_RS);
	local_error &= GPIO_u8PinConfig(&HLCD_RW);
	local_error &= GPIO_u8PinConfig(&HLCD_E);
	local_error &= GPIO_u8PinConfig(&HLCD_D0);
	local_error &= GPIO_u8PinConfig(&HLCD_D1);
	local_error &= GPIO_u8PinConfig(&HLCD_D2);
	local_error &= GPIO_u8PinConfig(&HLCD_D3);
	local_error &= GPIO_u8PinConfig(&HLCD_D4);
	local_error &= GPIO_u8PinConfig(&HLCD_D5);
	local_error &= GPIO_u8PinConfig(&HLCD_D6);
	local_error &= GPIO_u8PinConfig(&HLCD_D7);
	return local_error;
}

/*This function takes data to be written on the LCD*/
u8 HLCD_u8WriteDataRequest(u8* Copy_u8Data, u8 Copy_u8Size)
{
	u8 local_error = OK;
	if (!HLCD_busy) /*If the data/command reg is empty accept new data*/
	{
		u8 local_counter;
		for(local_counter = 0;local_counter<Copy_u8Size; local_counter++)
		{
			HLCD_data_cmd[local_counter] = *(Copy_u8Data+local_counter);
		}
		dataCounter = Copy_u8Size;
		write_data_counter = 0;
		HLCD_busy = 1;
	}
	else
	{
		local_error = NOK;
	}
	return local_error;
}

/*This function takes command to be applied on the LCD*/
u8 HLCD_u8WriteCmdRequest(u8 Copy_u8Cmd)
{
	u8 local_error = OK;
	if (!HLCD_busy) /*If the data/command reg is empty accept new data*/
	{
		HLCD_data_cmd[0] = Copy_u8Cmd;
		dataCounter = HLCD_COLS + 1;	/*dataCounter = 17 indicates command to be written*/
		HLCD_busy = 1;
	}
	else
	{
		local_error = NOK;
	}
	return local_error;
}

/*This function changes the cursor position: ROW[0-1] COL[0-1-2-3-4-5-6-7-8-9-10-11-12-13-14-15]*/
u8 HLCD_u8CursorPosition(u8 Copy_u8Row, u8 Copy_u8Column)
{
	u8 local_error;
	if((Copy_u8Row<HLCD_ROWS) & (Copy_u8Column<HLCD_COLS))
	{
		u8 cursor_position= (CHANGE_CURSOR_POSITION|(Copy_u8Row<<HLCD_ROW_SHIFT)|(Copy_u8Column));
		local_error = HLCD_u8WriteCmdRequest(cursor_position);
	}
	else
	{
		local_error = NOK;
	}
	
	return local_error;
}

/*This is the Runnable function that drives the LCD*/
void HLCD_voidRunnable(void)
{
	static u8 HLCD_E_state = 0;
	if (HLCD_state == HLCD_INITIALIZATION_COMPLETE)	/*Check if the initialization sequence is complete*/
	{
		if(HLCD_E_state)	/*Make the E pin low after writing data or command*/
		{
			GPIO_u8SetPinValue(&HLCD_E,OUTPUT_LOW);
			HLCD_E_state = 0;
		}
		else	/*Writing data or command per request*/
		{
			if(dataCounter>HLCD_COLS) /*Command is to be written*/
			{
				dataCounter = 0;
				HLCD_voidWriteCmd(HLCD_data_cmd[dataCounter]);
				HLCD_E_state = 1;
				
			}
			else if (dataCounter>write_data_counter) /*Data is to be written*/
			{
				HLCD_voidWriteData(HLCD_data_cmd[write_data_counter]);
				write_data_counter++;
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
		HLCD_voidInitializationSequence();
	}
}

/*This function writes data on the data pins for the LCD*/
static void HLCD_voidWriteData(u8 Copy_u8Data)
{
	/*RS is high and RW is low for writing data*/
	GPIO_u8SetPinValue(&HLCD_RS,OUTPUT_HIGH);
	GPIO_u8SetPinValue(&HLCD_RW,OUTPUT_LOW);
	/*Send the data to be written*/
	HLCD_voidWriteDataCmd(Copy_u8Data);
	/*E pulse*/
	GPIO_u8SetPinValue(&HLCD_E,OUTPUT_HIGH);
}

/*This function writes command on the data pins for the LCD*/
static void HLCD_voidWriteCmd(u8 Copy_u8Command)
{
	/*RS is low and RW is low for writing command*/
	GPIO_u8SetPinValue(&HLCD_RS,OUTPUT_LOW);
	GPIO_u8SetPinValue(&HLCD_RW,OUTPUT_LOW);
	/*Send the command to be written*/
	HLCD_voidWriteDataCmd(Copy_u8Command);
	/*E pulse*/
	GPIO_u8SetPinValue(&HLCD_E,OUTPUT_HIGH);
}

/*This function assigns the command/data bits to the corresponding data pins*/
static void HLCD_voidWriteDataCmd(u8 Copy_u8DataCmd)
{
	GPIO_u8SetPinValue(&HLCD_D0,( (Copy_u8DataCmd>>HLCD_D0_BIT) & ONE_MASK) );
	GPIO_u8SetPinValue(&HLCD_D1,( (Copy_u8DataCmd>>HLCD_D1_BIT) & ONE_MASK) );
	GPIO_u8SetPinValue(&HLCD_D2,( (Copy_u8DataCmd>>HLCD_D2_BIT) & ONE_MASK) );
	GPIO_u8SetPinValue(&HLCD_D3,( (Copy_u8DataCmd>>HLCD_D3_BIT) & ONE_MASK) );
	GPIO_u8SetPinValue(&HLCD_D4,( (Copy_u8DataCmd>>HLCD_D4_BIT) & ONE_MASK) );
	GPIO_u8SetPinValue(&HLCD_D5,( (Copy_u8DataCmd>>HLCD_D5_BIT) & ONE_MASK) );
	GPIO_u8SetPinValue(&HLCD_D6,( (Copy_u8DataCmd>>HLCD_D6_BIT) & ONE_MASK) );
	GPIO_u8SetPinValue(&HLCD_D7,( (Copy_u8DataCmd>>HLCD_D7_BIT) & ONE_MASK) );
}

static void HLCD_voidInitializationSequence(void)
{
	static u8 initializationCounter = INIT_SEQ_COUNTER;
	if(!initializationCounter)
	{
		switch(HLCD_state)	/*Start the initialization sequence*/
		{
			case HLCD_INITIAL_STATE:/*S0: Set up the LCD*/
			HLCD_voidWriteCmd(LINES_FONT_INIT);
			HLCD_state = HLCD_SETUP_LCD_STATE ;
			break;
			case HLCD_SETUP_LCD_STATE : /*S1: Make the E pin low*/
			GPIO_u8SetPinValue(&HLCD_E,OUTPUT_LOW);
			HLCD_state = HLCD_SETUP_CURSOR_STATE ;
			break;
			case HLCD_SETUP_CURSOR_STATE : /*S2: Set up the cursor*/
			HLCD_voidWriteCmd(CURSOR_INIT);
			HLCD_state = HLCD_EPIN_RESET1_STATE ;
			break;
			case HLCD_EPIN_RESET1_STATE : /*S3: Make the E pin low*/
			GPIO_u8SetPinValue(&HLCD_E,OUTPUT_LOW);
			HLCD_state = HLCD_DISPLAY_CLEAR_STATE ;
			break;
			case HLCD_DISPLAY_CLEAR_STATE : /*S4: Clear the display*/
			HLCD_voidWriteCmd(CLEAR_DISPLAY);
			HLCD_state = HLCD_EPIN_RESET2_STATE;
			break;
			case HLCD_EPIN_RESET2_STATE:  /*S5: Make the E pin low*/
			GPIO_u8SetPinValue(&HLCD_E,OUTPUT_LOW);
			HLCD_state = HLCD_INITIALIZATION_COMPLETE ;
			break;
		}
	}
	else
	{
		initializationCounter--;		/*Delay before init sequence*/
	}

}
