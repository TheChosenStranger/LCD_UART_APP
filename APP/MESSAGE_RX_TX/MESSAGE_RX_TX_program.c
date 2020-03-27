#include "STD_TYPES.h"
#include "UTIL_interface.h"
#include "HUART_interface.h"
#include "MESSAGE_RX_TX_interface.h"

extern u8 TogLED;

STD_ERROR Message_Send(u32 Num, u16 length){
	STD_ERROR Local_STD_ERROR_Stat=OK;
	u8 message[FRAME_LENGTH]=SPLIT_MESSAGE(Num);
	Local_STD_ERROR_Stat=HUART_Transmit(message,FRAME_LENGTH);
	return Local_STD_ERROR_Stat;
}

STD_ERROR Message_Receive(u8* buffer, u16* length){
	STD_ERROR Local_STD_ERROR_Stat=OK;
	u8 tempBuffer[FRAME_LENGTH];
	u16 tempLength;
	u32 tempMessage;
	TogLED = 1;
	Local_STD_ERROR_Stat=HUART_Recieve(tempBuffer,&tempLength);
	if(Local_STD_ERROR_Stat==OK){
		tempMessage=CONCAT_MESSAGE(tempBuffer[0],tempBuffer[1],tempBuffer[2],tempBuffer[3]);
		NumberToString(tempMessage,buffer,length);
	}	
	return Local_STD_ERROR_Stat;
}

