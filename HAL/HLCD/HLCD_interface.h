/******************************/
/* Author  : Moustafa Ghareeb */
/* Version : V1.1             */
/* Date    : 17-03-2020       */
/******************************/
#ifndef HLCD_INTERFACE_H_
#define HLCD_INTERFACE_H_

/*Defining LCDs pins*/
#define HLCD_E_PIN		GPIO_PIN0	
#define HLCD_RS_PIN		GPIO_PIN1
#define HLCD_RW_PIN		GPIO_PIN2
#define HLCD_D0_PIN		GPIO_PIN0
#define HLCD_D1_PIN		GPIO_PIN1
#define HLCD_D2_PIN		GPIO_PIN2
#define HLCD_D3_PIN		GPIO_PIN3
#define HLCD_D4_PIN		GPIO_PIN4
#define HLCD_D5_PIN		GPIO_PIN5
#define HLCD_D6_PIN		GPIO_PIN6
#define HLCD_D7_PIN		GPIO_PIN7
/*Defining LCDs ports*/
#define HLCD_E_PORT		GPIO_PORT_B
#define HLCD_RS_PORT	GPIO_PORT_B
#define HLCD_RW_PORT	GPIO_PORT_B
#define HLCD_D0_PORT	GPIO_PORT_A
#define HLCD_D1_PORT	GPIO_PORT_A
#define HLCD_D2_PORT	GPIO_PORT_A
#define HLCD_D3_PORT	GPIO_PORT_A
#define HLCD_D4_PORT	GPIO_PORT_A
#define HLCD_D5_PORT	GPIO_PORT_A
#define HLCD_D6_PORT	GPIO_PORT_A
#define HLCD_D7_PORT	GPIO_PORT_A
/*Defining LCDs mode*/
#define HLCD_PIN_MODE		GPIO_CNF_GPO_PUSH_PULL
#define HLCD_PIN_SPEED		GPIO_MODE_OUTPUT_10_MHZ
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
#define ONE_MASK	0b00000001
#define HLCD_ROW_SHIFT 6

/*Defining display options for the LCD*/
#define	TWO_LINES  			   	0b00111100
#define CURSOR_OFF			    0b00001100
#define CURSOR_ON			    0b00001110
#define CLEAR_DISPLAY    		0b00000001
#define CURSOR_HOME	    		0b00000010

/*Defining default configurations for the LCD*/

#define LINES_FONT_INIT	 TWO_LINES
#define CURSOR_INIT		 CURSOR_OFF

STD_ERROR HLCD_u8Init(void);
STD_ERROR HLCD_u8StartSequence(void);
STD_ERROR HLCD_u8WriteDataRequest(u8* Copy_u8Data,u8 Copy_u8Size);
STD_ERROR HLCD_u8WriteCmdRequest(u8 Copy_u8Cmd);
STD_ERROR HLCD_u8CursorPosition(u8 Copy_u8Row, u8 Copy_u8Column);
void HLCD_voidRunnable(void);

#endif
