/*
 * HSwitch.h
 *
 *  Created on: Mar 27, 2020
 *      Author: Norhan Nassar
 *      version: V1.2
 */

#ifndef HSWITCH_H_
#define HSWITCH_H_

typedef 	u8 	SWITCH_STATE;
#define		SWITCH_PULL_UP					1
#define		SWITCH_PULL_DOWN				0

#define 	CLEAR							0x00000000

/* Max number of Switches on a certain port 							*/
#define 	SWITCH_PORT_MAX_NUM					16


/* Struct to each switch 																		*/
/* It contains: switch Number, and which pin connected to and it is pull up or pull down	*/
typedef struct
{
	u16 Switch_Num;
	u16 Switch_Pin;									/* GPIO_PIN0 to GPIO_PIN15 			  */
	u8 SWITCH_STATE;								/* SWITCH_PULL_UP or SWITCH_PULL_DOWN */
}Switch_Pin_t;

/* Struct to each Port which connect to it some Switches										*/
typedef struct
{
	u32 Switchs_Port;					/* Port which Switches connected to -> PORTA or PORTB.. */
	u8  Switchs_Port_Num;				/* Number of Switchs at each port 						*/
	Switch_Pin_t* Switchs_Port_Pins;	/* Pointer to struct of pins connected to this port 	*/
}Switchs_Port_t;

/******************************************************************************************/
/* Description: This API shall initialize all Switchs at configuration file to be Input   */
/* Pull up or pull down for each port 										 			  */
/******************************************************************************************/
extern STD_ERROR Switch_init(void);

/*****************************************************************************************/
/* Description: This API shall check if a certain switch is pressed or not				 */
/* Copy_PtrState -> pointer to switch state												 */
/*****************************************************************************************/
extern STD_ERROR Switch_getSwitchState(u8 Copy_u8SwitchNum,u8* Copy_PtrSwitchState);

/*****************************************************************************************/
/* Task Runnable every given periodicity												 */
/* to check if Switches are pressed or not 												 */
/*****************************************************************************************/
extern void HSwitch_Runnable(void);


#endif /* HSWITCH_H_ */
