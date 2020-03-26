#include "STD_TYPES.h"
#include "UART_register.h"
#include "UART_config.h"
#include "UART_interface.h"
#include "GPIO_interface.h"

rxCbf_t txCallback=&UART_DefaultTxCallback;
rxCbf_t rxCallback=&UART_DefaultRxCallback;

static u8 TX_Buffer[32]; 
static u16 TX_Buffer_Len;
static u8 RX_Buffer[32]; 
static u16 RX_Buffer_Len;

STD_ERR UART_Init(void){
	STD_ERR Local_STD_ERR_Stat=OK;
	GPIO_t t = { USART1_TX_PIN, USART1_TX_PORT, USART1_TX_MODE ,
			 USART1_TX_SPEED };
	Local_STD_ERR_Stat=GPIO_Config(&t);
	if(Local_STD_ERR_Stat==OK){
		t.port=USART1_RX_PORT;
		t.pin=USART1_RX_PIN;
		t.mode=USART1_RX_MODE;
		t.speed=USART1_RX_MODE;
		Local_STD_ERR_Stat=GPIO_Config(&t);
	}
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

	return Local_STD_ERR_Stat;
}
void UART_Send(u8 * buffer, u16 len){
	u8 i;
	UARTx->USART_DR=buffer[0];
	for (i = 1; i < len; ++i)
	{
		TX_Buffer[i]=buffer[i];
	}
	TX_Buffer_Len=len;
	
}
void UART_Receive(u8* buffer, u16* len){
	u8 i;
	for (i = 0; i < RX_Buffer_Len; ++i) {
		buffer[i]=RX_Buffer[i];
	}
	*len=RX_Buffer_Len;
	RX_Buffer_Len=0;
}
STD_ERR UART_Configure(u32 baudrate, u8 stopBits, u32 parity){
	STD_ERR Local_STD_ERR_Stat=OK;
	if((USART_BRR_MASK && baudrate) == baudrate){
		UARTx->USART_BRR=baudrate;
	}
	else{
		Local_STD_ERR_Stat=NOT_OK;
	}
	if((Local_STD_ERR_Stat==OK)&&(USART_CR2_STOPBITS_MASK && stopBits)==stopBits){
		UARTx->USART_CR1&=~USART_CR2_STOPBITS_MASK;
		UARTx->USART_CR1|= stopBits;
	}
	else{
		Local_STD_ERR_Stat=NOT_OK;
	}
	if((USART_BRR_MASK && baudrate) == baudrate){
		UARTx->USART_BRR=baudrate;
	}
	else{
		Local_STD_ERR_Stat=NOT_OK;
	}
	if((Local_STD_ERR_Stat==OK)&&((USART_CR1_PE_MASK | USART_CR1_PS_MASK) && parity)==parity){
		if(parity==USART_CR1_PE_DISABLE){
			UARTx->USART_CR1&=~USART_CR1_PE_MASK;
			UARTx->USART_CR1&=~USART_CR1_PS_MASK;
		}
		else{
			UARTx->USART_CR1&=~USART_CR1_PE_MASK;
			UARTx->USART_CR1&=~USART_CR1_PS_MASK;
			UARTx->USART_CR1|=parity;
		}
	}else{
		Local_STD_ERR_Stat=NOT_OK;
	}
	return Local_STD_ERR_Stat;
}
STD_ERR UART_SetTxCallbackFnc(txCbf_t txcbf){
	STD_ERR Local_STD_ERR_Stat=OK;
	if(txcbf)
		txCallback=txcbf;
	else
		Local_STD_ERR_Stat=NOT_OK;
	return Local_STD_ERR_Stat;
}
STD_ERR UART_SetRxCallbackFnc(rxCbf_t rxcbf){
	STD_ERR Local_STD_ERR_Stat=OK;
	if(rxcbf)
		rxCallback=rxcbf;
	else
		Local_STD_ERR_Stat=NOT_OK;
	return Local_STD_ERR_Stat;
}
void UART_DefaultTxCallback(void){
	static u16 Local_u16NextChar=0;
	if(TX_Buffer_Len>Local_u16NextChar)
		UARTx->USART_DR=TX_Buffer[Local_u16NextChar++];
}
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
