/*
 * App.h
 *
 *  Created on: Apr 26, 2020
 *      Author: Norhan Nassar
 */

#ifndef APP_H_
#define APP_H_

typedef u8 FrameID_t;

#define SwitchesStatus				0xFF							/* Frame Id for Switches status frame */
#define SW_DATE						SWITCH_0						/* Second Switch is Date switch		  */
#define SW_EDIT						SWITCH_1						/* Third Switch is Edit switch		  */
#define SW_UP						SWITCH_2						/* 4th Switch is Up switch		  	  */
#define SW_DOWN						SWITCH_3						/* 5th Switch is Down switch		  */
#define SW_RIGHT					SWITCH_4						/* 6th Switch is Right switch		  */
#define SW_LEFT						SWITCH_5						/* 7th Switch is Left switch		  */

#define NUMOFSWITCHES				6

#endif /* APP_H_ */
