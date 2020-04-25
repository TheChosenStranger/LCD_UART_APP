/******************************/
/* Author  : Moustafa Ghareeb */
/* Version : V1.2             */
/* Date    : 30-03-2020       */
/******************************/
#ifndef HLCD_INTERFACE_H_
#define HLCD_INTERFACE_H_

/*Defining data bits*/
#define HLCD_D0_BIT		0
#define HLCD_D1_BIT 	1
#define HLCD_D2_BIT 	2
#define HLCD_D3_BIT 	3
#define HLCD_D4_BIT 	4
#define HLCD_D5_BIT 	5
#define HLCD_D6_BIT 	6
#define HLCD_D7_BIT 	7
/*Defining additional masks*/
#define CHANGE_CURSOR_POSITION	0b10000000
#define ONE_MASK				0b00000001
#define HLCD_ROW_SHIFT				 6

/*Defining display options for the LCD*/
#define	TWO_LINES  			   	0b00111100
#define CURSOR_OFF			    0b00001100
#define CURSOR_ON			    0b00001110
#define CLEAR_DISPLAY    		0b00000001
#define CURSOR_HOME	    		0b00000010

/*Functions prototypes*/
extern STD_ERROR HLCD_u8Init(void);
extern STD_ERROR HLCD_u8StartSequence(void);
extern STD_ERROR HLCD_u8WriteDataRequest(u8* Copy_u8Data,u8 Copy_u8Size);
extern STD_ERROR HLCD_u8WriteCmdRequest(u8 Copy_u8Cmd);
extern STD_ERROR HLCD_u8CursorPosition(u8 Copy_u8Row, u8 Copy_u8Column);
extern void HLCD_voidRunnable(void);

#endif
