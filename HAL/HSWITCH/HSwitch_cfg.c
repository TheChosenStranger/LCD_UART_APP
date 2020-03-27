/*
 * HSwitch_cfg.c
 *
 *  Created on: Mar 27, 2020
 *      Author: Norhan Nassar
 *      Version: V1.2
 */

#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "HSwitch.h"
#include "HSwitch_cfg.h"

/* Configure each Switch on your system to a certain Pin at a certain Port
 * and configure its state -> SWITCH_PULL_UP or SWITCH_PULL_DOWN */
#define SWITCHES_PORTB { {SWITCH_0,GPIO_PIN0,SWITCH_PULL_UP}};

Switch_Pin_t Switchs_PORTB[SWITCHES_PORTB_NUM]=SWITCHES_PORTB
Switchs_Port_t Switchs_Port_Map[PORTS_NUM] = { {PORTB,SWITCHES_PORTB_NUM,(Switch_Pin_t*)&Switchs_PORTB} };
