#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/UART/UART_interface.h"
#include "HUART_interface.h"

STD_ERROR HUART_Init(void)
{
	return UART_Init();
}

STD_ERROR HUART_Transmit(u8* buffer,u16 length){
	STD_ERROR Local_STD_ERROR_stat=OK;
	u8 temp;
	UART_TransmitStatus(&temp);
	if(temp==0)
		Local_STD_ERROR_stat=NOT_OK;
	else
		UART_Send(buffer,length);
	return Local_STD_ERROR_stat;
}

STD_ERROR HUART_Recieve(u8* buffer,u16 length){
	STD_ERROR Local_STD_ERROR_stat=OK;
	u8 temp;
	UART_RecieveStatus(&temp);
	if(temp==0)
		Local_STD_ERROR_stat=NOT_OK;
	else
		UART_Receive(buffer,length);
	return Local_STD_ERROR_stat;
}
