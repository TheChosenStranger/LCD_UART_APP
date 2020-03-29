#include "../../LIB/STD_TYPES.h"
#include "../GPIO/GPIO_interface.h"
#include "UART_register.h"
#include "UART_config.h"
#include "UART_interface.h"


/*callback functions set to default*/
rxCbf_t txCallback=&UART_DefaultTxCallback;
rxCbf_t rxCallback=&UART_DefaultRxCallback;

/*TX and RX buffer*/
static u8 TX_Buffer[32]; 
static u16 TX_Buffer_Len;
static u8 RX_Buffer[32]; 
static u16 RX_Buffer_Len;

/*	Initialize UART to default configurations
*	can be modified from config file
*	default configs set to:
*	Baudrate: 				9600
*	Word Length:		 	8 bits
*	Parity:  				Disabled
*	Parity Interrupt:		Disabled
*	Tx Interrupt:			Enabled
*	TC Interrupt:			Disabled
*	Rx Interrupt:			Enabled
*	Transmit:	 			Enabled
*	Recieve: 				Enabled
*	Stopbits:				1
*	Halfduplex Mode:		Disabled
*/
STD_ERROR UART_Init(void){
	STD_ERROR Local_STD_ERROR_Stat=OK;
	GPIO_t t = { USART1_TX_PIN, USART1_TX_PORT, USART1_TX_MODE ,
			 USART1_TX_SPEED };
	Local_STD_ERROR_Stat=GPIO_Config(&t);/*config transmitter*/
	if(Local_STD_ERROR_Stat==OK){
		t.port=USART1_RX_PORT;
		t.pin=USART1_RX_PIN;
		t.mode=USART1_RX_MODE;
		t.speed=USART1_RX_MODE;
		Local_STD_ERROR_Stat=GPIO_Config(&t);/*config reciever*/
	}
	if(Local_STD_ERROR_Stat==OK){
		UARTx->USART_CR1|=USART_CR1_UE_ENABLE;
		UARTx->USART_CR1|=USART_WORD_LENGTH_CONFIG;
		UARTx->USART_CR1|=USART_PARITY_CONFIG; 
		UARTx->USART_CR1|=USART_PS_CONFIG;	 	
		UARTx->USART_CR1|=USART_PEIE_CONFIG;
		UARTx->USART_CR1|=USART_TXEIE_CONFIG;
		UARTx->USART_CR1|=USART_TCIE_CONFIG;
		UARTx->USART_CR1|=USART_RXENE_CONFIG;
		
		UARTx->USART_BRR=USART_BAUDRATE;

		UARTx->USART_CR2|=USART_STOPBITS;
		UARTx->USART_CR3|=USART_HALFDUPLEX;

		UARTx->USART_CR1|=USART_TE_CONFIG;
		UARTx->USART_CR1|=USART_RE_CONFIG;
	}
	return Local_STD_ERROR_Stat;
}
/*	start trasmition process
*	buffer=any string
*	len=length of buffer
*/	
void UART_Send(u8 * buffer, u16 len){
	u8 i;
	UARTx->USART_DR=buffer[0];
	for (i = 1; i < len; ++i)
	{
		TX_Buffer[i]=buffer[i];
	}
	TX_Buffer_Len=len;
	
}
/*	start recieving process
*	buffer=recieved string
*	len=length of recieved string
*/	
void UART_Receive(u8* buffer, u16* len){
	u8 i;
	for (i = 0; i < RX_Buffer_Len; ++i) {
		buffer[i]=RX_Buffer[i];
	}
	*len=RX_Buffer_Len;
	RX_Buffer_Len=0;
}
/*
*	Configure UART post init function
*	baudrate= USART_BAUDRATE_9600_8MHZ,USART_BAUDRATE_115200_8MHZ 
*				(or any value calculate using the equation desiered_baudrate=freq/(16*USARTDIV) )
*				baudrate=((mantisa of USARTDIV)|(exponent of USARTDIV * 16))
*	stopBits = USART_CR2_STOPBITS_1, USART_CR2_STOPBITS_0_5, USART_CR2_STOPBITS_2, USART_CR2_STOPBITS_1_5
*	parity = USART_PARITY_OFF, USART_PARITY_EVEN, USART_PARITY_ODD
*
*
*/
STD_ERROR UART_Configure(u32 baudrate, u8 stopBits, u32 parity){
	STD_ERROR Local_STD_ERROR_Stat=OK;
	if((USART_BRR_MASK && baudrate) == baudrate){
		UARTx->USART_BRR=baudrate;
	}
	else{
		Local_STD_ERROR_Stat=NOT_OK;
	}
	if((Local_STD_ERROR_Stat==OK)&&(USART_CR2_STOPBITS_MASK && stopBits)==stopBits){
		UARTx->USART_CR1&=~USART_CR2_STOPBITS_MASK;
		UARTx->USART_CR1|= stopBits;
	}
	else{
		Local_STD_ERROR_Stat=NOT_OK;
	}
	if((USART_BRR_MASK && baudrate) == baudrate){
		UARTx->USART_BRR=baudrate;
	}
	else{
		Local_STD_ERROR_Stat=NOT_OK;
	}
	if((Local_STD_ERROR_Stat==OK)&&((USART_CR1_PE_MASK | USART_CR1_PS_MASK) && parity)==parity){
		UARTx->USART_CR1&=~USART_CR1_PE_MASK;
		UARTx->USART_CR1&=~USART_CR1_PS_MASK;
		UARTx->USART_CR1|=parity;
	}else{
		Local_STD_ERROR_Stat=NOT_OK;
	}
	return Local_STD_ERROR_Stat;
}
/*	set callback function for trasmitter
*	txcbf = pointer to callback fucntion
*/
STD_ERROR UART_SetTxCallbackFnc(txCbf_t txcbf){
	STD_ERROR Local_STD_ERROR_Stat=OK;
	if(txcbf)
		txCallback=txcbf;
	else
		Local_STD_ERROR_Stat=NOT_OK;
	return Local_STD_ERROR_Stat;
}
/*	set callback function for reciever
*	rxcbf = pointer to callback fucntion
*/
STD_ERROR UART_SetRxCallbackFnc(rxCbf_t rxcbf){
	STD_ERROR Local_STD_ERROR_Stat=OK;
	if(rxcbf)
		rxCallback=rxcbf;
	else
		Local_STD_ERROR_Stat=NOT_OK;
	return Local_STD_ERROR_Stat;
}
/*default callback function for transmitter*/
void UART_DefaultTxCallback(void){
	static u16 Local_u16NextChar=0;
	if(TX_Buffer_Len>Local_u16NextChar)
		UARTx->USART_DR=TX_Buffer[Local_u16NextChar++];
}
/*default callback function for reciver*/
void UART_DefaultRxCallback(void){
	static u16 Local_u16NextChar=0;
	RX_Buffer_Len=Local_u16NextChar;
	RX_Buffer[Local_u16NextChar++]=UARTx->USART_DR;
}
void USART1_IRQHandler(void){
	if((UARTx->USART_SR && USART_SR_TXE_MASK) != 0)
		txCallback();
	if((UARTx->USART_SR && USART_SR_RXNE_MASK) != 0)
		rxCallback();
}
/*check if transmitter is sending*/
void UART_TransmitStatus(u8 * stat){
	if((UARTx->USART_SR && USART_SR_TC_MASK) != 0)
		*stat=0;
	else
		*stat=1;
}
/*check if reciver recieved new data*/
void UART_RecieveStatus(u8 * stat){
	if((UARTx->USART_SR && USART_SR_RXNE_MASK) != 0)
			*stat=0;
		else
			*stat=1;
}
