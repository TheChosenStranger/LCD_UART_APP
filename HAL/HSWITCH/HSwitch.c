/*
 * HSwitch.c
 *
 *  Created on: Mar 27, 2020
 *      Author: Norhan Nassar
 */

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "HSwitch.h"
#include "HSwitch_cfg.h"

extern Switchs_Port_t Switchs_Port_Map[];
static STD_ERROR HSwitch_GPIO_u8ReadSwitchNum(u8 Copy_u8SwitchNum, u8* Copy_PtrData);

extern u8 switchState[SWITCHES_NUMBER];

STD_ERROR HSwitch_init()
{
	STD_ERROR loc_err = OK;
	u8 PortCounter,PinCounter;
	GPIO_t Switch_GPIO_Pin;				/* struct of type GPIO to configure it with this one */
	Switch_GPIO_Pin.pin=CLEAR;						/* Initialize Pin at GPIO struct to 0 */

	for(PortCounter=0;PortCounter<PORTS_NUM;PortCounter++)
	{
		Switch_GPIO_Pin.port = Switchs_Port_Map[PortCounter].Switchs_Port;
		for(PinCounter=0;PinCounter<Switchs_Port_Map[PortCounter].Switchs_Port_Num;PinCounter++)
		{
			Switch_GPIO_Pin.pin |= Switchs_Port_Map[PortCounter].Switchs_Port_Pins[PinCounter].Switch_Pin;
			if(Switchs_Port_Map[PortCounter].Switchs_Port_Pins->SWITCH_STATE==SWITCH_PULL_UP)
				GPIO_u8Write(Switchs_Port_Map[PortCounter].Switchs_Port,Switchs_Port_Map[PortCounter].Switchs_Port_Pins[PinCounter].Switch_Pin,1);
			else /* if user not configure its state it will be by default pull down */
				GPIO_u8Write(Switchs_Port_Map[PortCounter].Switchs_Port,Switchs_Port_Map[PortCounter].Switchs_Port_Pins[PinCounter].Switch_Pin,0);
		}
		Switch_GPIO_Pin.mode = GPIO_CNF_IP_PULL_UP_DOWN;
		Switch_GPIO_Pin.speed=GPIO_MODE_INPUT;
		GPIO_voidConfigure(&Switch_GPIO_Pin);
	}
	return loc_err;
}

void HSwitch_Runnable(void)
{
	static u8 currentState[SWITCHES_NUMBER];
	static u8 prevState[SWITCHES_NUMBER]={0};
	static u8 counter[SWITCHES_NUMBER]={0};
	u8 i;

	for(i=0;i<SWITCHES_NUMBER;i++)
	{
		HSwitch_GPIO_u8ReadSwitchNum(i,(currentState+i));
		if(currentState[i]==prevState[i])
			counter[i]++;
		else
			counter[i]=0;

		if(counter[i] == 5)
		{
			counter[i] =0;
			switchState[i] = currentState[i];

		}
		prevState[i]=currentState[i];
	}

}

STD_ERROR HSwitch_getSwitchState(u8 Copy_u8SwitchNum,u8* Copy_PtrSwitchState)
{
	*Copy_PtrSwitchState = switchState[Copy_u8SwitchNum];
	return OK;
}

/* static function to call GPIO write for this switch number  */
STD_ERROR HSwitch_GPIO_u8ReadSwitchNum(u8 Copy_u8SwitchNum, u8* Copy_PtrData)
{
	STD_ERROR loc_err;
	if(!Copy_PtrData)
		return NOT_OK;
	u8 PortCounter,PinCounter;
	for(PortCounter=0;PortCounter<PORTS_NUM;PortCounter++)
	{
		for(PinCounter=0;PinCounter<Switchs_Port_Map[PortCounter].Switchs_Port_Num;PinCounter++)
		{
			if(Switchs_Port_Map[PortCounter].Switchs_Port_Pins[PinCounter].Switch_Num==Copy_u8SwitchNum)
			{
				loc_err = GPIO_SetPinValue(Switchs_Port_Map[PortCounter].Switchs_Port_Pins[PinCounter].Switch_Pin,Switchs_Port_Map[PortCounter].Switchs_Port,Copy_PtrData);
				return loc_err;
			}
		}
	}
	return NOT_OK;
}
