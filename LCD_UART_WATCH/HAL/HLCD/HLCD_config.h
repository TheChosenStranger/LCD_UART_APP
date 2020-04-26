/******************************/
/* Author  : Moustafa Ghareeb */
/* Version : V1.3             */
/* Date    : 04-04-2020       */
/******************************/
#ifndef HLCD_CONFIG_H_
#define HLCD_CONFIG_H_

/*Configuring LCDs pins*/
/*From PIN0 to Pin15*/
#define HLCD_RS_PIN		PIN8
#define HLCD_RW_PIN		PIN9
#define HLCD_E_PIN		PIN10
#define HLCD_D0_PIN		PIN0
#define HLCD_D1_PIN		PIN1
#define HLCD_D2_PIN		PIN2
#define HLCD_D3_PIN		PIN3
#define HLCD_D4_PIN		PIN4
#define HLCD_D5_PIN		PIN5
#define HLCD_D6_PIN		PIN6
#define HLCD_D7_PIN		PIN7
/*Configuring LCDs ports*/
/* PORTA - PORTB - PORTC */
#define HLCD_RS_PORT	PORTA
#define HLCD_RW_PORT	PORTA
#define HLCD_E_PORT		PORTA
#define HLCD_D0_PORT	PORTA
#define HLCD_D1_PORT	PORTA
#define HLCD_D2_PORT	PORTA
#define HLCD_D3_PORT	PORTA
#define HLCD_D4_PORT	PORTA
#define HLCD_D5_PORT	PORTA
#define HLCD_D6_PORT	PORTA
#define HLCD_D7_PORT	PORTA
/*Configuring LCDs mode*/
#define HLCD_PIN_MODE		GPIO_CNF_GPO_PUSH_PULL
/*Configuring LCDs speed*/
#define HLCD_PIN_SPEED		GPIO_MODE_OUTPUT_2_MHZ
/*The default configurations for the LCD*/
#define LINES_FONT_INIT	 TWO_LINES	/* TWO_LINES*/
#define CURSOR_INIT		 CURSOR_OFF /* CURSOR_OFF	-	CURSOR_ON */

#endif
