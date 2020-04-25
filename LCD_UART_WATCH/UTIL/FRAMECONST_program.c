/*
 * FRAMECONST_program.c
 *
 *  Created on: Apr 6, 2020
 *      Author: Moamen
 */

#include "STD_TYPES.h"
#include "FRAMECONST_config.h"
#include "FRAMECONST_interface.h"


STD_ERROR FRAMECONST_FrameConstructor(frameData_t* Data,u8 FrameID,u16 Length,u8* Frame){
	u8 i;
	STD_ERROR Local_STD_ERROR_Stat=OK;
	tProtocol_t * prot=(tProtocol_t *)Frame;
	prot->header.id=FrameID;
	prot->header.sf=FRAMECONST_START_OF_FRAME;
	prot->header.id=FrameID;
	prot->header.len=Length;
	frameData_t *ff= (frameData_t*)prot->frameData;
	ff->data=Data->data;
	ff->EOF=FRAMECONST_END_OF_FRAME;
	//prot->frameData[i]=FRAMECONST_END_OF_FRAME;
	return Local_STD_ERROR_Stat;
}
