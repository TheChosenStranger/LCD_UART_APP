/******************************/
/* Author  : Moustafa Ghareeb */
/* Version : V1.2             */
/* Date    : 30-03-2020       */
/******************************/
#ifndef HLCD_CONFIG_H_
#define HLCD_CONFIG_H_

/*LCD Configurations*/
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
/*Defining default configurations for the LCD*/
#define LINES_FONT_INIT	 TWO_LINES	/*TWO_LINES*/
#define CURSOR_INIT		 CURSOR_OFF	/*CURSOR_OFF - CURSOR_ON*/

#endif
