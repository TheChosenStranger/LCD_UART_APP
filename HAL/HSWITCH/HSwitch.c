/*
 * Switch.c
 *
 *  Created on: Mar 26, 2020
 *      Author: Norhan Nassar
 */

#include "../../LIB/STD_TYPES.h"
#include "Switch.h"

static SwitchCbf_t sglobal;
void getSwitchState(u8* data)
{
	*data = 1;
}

void runnable(SwitchCbf_t s)
{
	sglobal = s;
}

void doit ()
{
	sglobal(&);
}




