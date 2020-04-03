#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "UART_register.h"
#include "UART_config.h"
#include "UART_interface.h"

/*callback functions set to default*/
rxCbf_t txCallback;
rxCbf_t rxCallback;

static UART_Message_Frame_t UART_TX;
static UART_Message_Frame_t UART_RX;
/*TX and RX buffer*/
/*static u8 TX_Buffer[UART_MAX_MESSAGE_LENGTH]; 
 static u16 TX_Buffer_Len;
 static u8 RX_Buffer[UART_MAX_MESSAGE_LENGTH];
 static u16 RX_Buffer_Len;*/
static u8 CurrentState = UART_STATE_NOT_BUSY;

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
STD_ERROR UART_Init(void) {
	STD_ERROR Local_STD_ERROR_Stat = OK;
	GPIO_t t = { USART1_TX_PIN, USART1_TX_PORT, USART1_TX_MODE,
	USART1_TX_SPEED };
	Local_STD_ERROR_Stat = GPIO_Config(&t);/*config transmitter*/
	if (Local_STD_ERROR_Stat == OK) {
		t.port = USART1_RX_PORT;
		t.pin = USART1_RX_PIN;
		t.mode = USART1_RX_MODE;
		t.speed = USART1_RX_MODE;
		Local_STD_ERROR_Stat = GPIO_Config(&t);/*config reciever*/
	}
	if (Local_STD_ERROR_Stat == OK) {
		UARTx->USART_CR1 |= USART_CR1_UE_ENABLE;
		UARTx->USART_CR1 |= USART_WORD_LENGTH_CONFIG;
		UARTx->USART_CR1 |= USART_PARITY_CONFIG;
		UARTx->USART_CR1 |= USART_PS_CONFIG;
		UARTx->USART_CR1 |= USART_PEIE_CONFIG;
		UARTx->USART_CR1 |= USART_TXEIE_CONFIG;
		UARTx->USART_CR1 |= USART_TCIE_CONFIG;
		UARTx->USART_CR1 |= USART_RXENE_CONFIG;

		UARTx->USART_BRR = USART_BAUDRATE;

		UARTx->USART_CR2 |= USART_STOPBITS_CONFIG;
		UARTx->USART_CR3 |= USART_HALFDUPLEX_CONFIG;

		UARTx->USART_CR1 |= USART_TE_CONFIG;
		UARTx->USART_CR1 |= USART_RE_CONFIG;
	}
	return Local_STD_ERROR_Stat;
}
/*	start trasmition process
 *	buffer=any string
 *	len=length of buffer
 */
STD_ERROR UART_Send(u8 * buffer, u16 len) {
	u8 i;
	STD_ERROR Local_STD_ERROR_Stat = OK;
	if (CurrentState == UART_STATE_NOT_BUSY) {
		CurrentState = UART_STATE_BUSY;
		UART_TX.Buffer = buffer;
		UART_TX.MessageLength = len;
		UART_TX.TransmitionComplete = UART_TRASMIT_NOT_COMPLETE;
		UART_TX.CurrentPosition = 1;
		UARTx->USART_DR = UART_TX.Buffer[0];
	} else {
		Local_STD_ERROR_Stat = NOT_OK;
	}
	return Local_STD_ERROR_Stat;

}
/*	start recieving process
 *	buffer=recieved string
 *	len=length of recieved string
 */
STD_ERROR UART_Receive(u8* buffer, u16 len) {
	u8 i;
	if (CurrentState == UART_STATE_NOT_BUSY
			&& UART_RX.TransmitionComplete == UART_TRASMIT_NOT_COMPLETE) {
		CurrentState = UART_STATE_BUSY;
		UART_RX.Buffer = buffer;
		UART_RX.MessageLength = len;
		UART_RX.TransmitionComplete = UART_TRASMIT_NOT_COMPLETE;
		UART_RX.CurrentPosition = 0;
	}

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
STD_ERROR UART_Configure(u32 baudrate, u8 stopBits, u32 parity) {
	STD_ERROR Local_STD_ERROR_Stat = OK;
	if ((USART_BRR_MASK && baudrate) == baudrate) {
		UARTx->USART_BRR = baudrate;
	} else {
		Local_STD_ERROR_Stat = NOT_OK;
	}
	if ((Local_STD_ERROR_Stat == OK)
			&& (USART_CR2_STOPBITS_MASK && stopBits) == stopBits) {
		UARTx->USART_CR1 &= ~USART_CR2_STOPBITS_MASK;
		UARTx->USART_CR1 |= stopBits;
	} else {
		Local_STD_ERROR_Stat = NOT_OK;
	}
	if (UART_VALIDATE_BAUDRATE(baudrate)) {
		UART_CalculateBaudrate(baudrate);
	} else {
		Local_STD_ERROR_Stat = NOT_OK;
	}
	if ((Local_STD_ERROR_Stat == OK)
			&& ((USART_CR1_PE_MASK | USART_CR1_PS_MASK) && parity) == parity) {
		UARTx->USART_CR1 &= ~USART_CR1_PE_MASK;
		UARTx->USART_CR1 &= ~USART_CR1_PS_MASK;
		UARTx->USART_CR1 |= parity;
	} else {
		Local_STD_ERROR_Stat = NOT_OK;
	}
	return Local_STD_ERROR_Stat;
}
/*	set callback function for trasmitter
 *	txcbf = pointer to callback fucntion
 */
STD_ERROR UART_SetTxCallbackFnc(txCbf_t txcbf) {
	STD_ERROR Local_STD_ERROR_Stat = OK;
	if (txcbf)
		txCallback = txcbf;
	else
		Local_STD_ERROR_Stat = NOT_OK;
	return Local_STD_ERROR_Stat;
}
/*	set callback function for reciever
 *	rxcbf = pointer to callback fucntion
 */
STD_ERROR UART_SetRxCallbackFnc(rxCbf_t rxcbf) {
	STD_ERROR Local_STD_ERROR_Stat = OK;
	if (rxcbf)
		rxCallback = rxcbf;
	else
		Local_STD_ERROR_Stat = NOT_OK;
	return Local_STD_ERROR_Stat;
}
/*default callback function for transmitter*/
void USART1_IRQHandler(void) {
	if ((UARTx->USART_SR && USART_SR_TXE_MASK) != 0) {
		if (UART_TX.TransmitionComplete == UART_TRASMIT_NOT_COMPLETE) {
			if (UART_TX.CurrentPosition < UART_TX.MessageLength) {
				UARTx->USART_DR = UART_TX.Buffer[UART_TX.CurrentPosition++];
			} else {
				UART_TX.TransmitionComplete = UART_TRASMIT_COMPLETE;
				CurrentState = UART_STATE_NOT_BUSY;
				UART_TX.MessageLength = 0;
				UART_TX.CurrentPosition = 0;
				txCallback();
			}
		}
	}
	if ((UARTx->USART_SR && USART_SR_RXNE_MASK) != 0) {
		if (UART_RX.TransmitionComplete == UART_TRASMIT_NOT_COMPLETE) {
			if (UART_RX.CurrentPosition < UART_RX.MessageLength) {
				UART_RX.Buffer[UART_RX.CurrentPosition++] = UARTx->USART_DR;
			} else {
				UART_RX.TransmitionComplete = UART_TRASMIT_COMPLETE;
				CurrentState = UART_STATE_NOT_BUSY;
				UART_RX.MessageLength = 0;
				UART_RX.CurrentPosition = 0;
				rxCallback();
			}
		}
	}
}
/*check if transmitter is sending*/
void UART_TransmitStatus(u8 * stat) {
	if ((UARTx->USART_SR && USART_SR_TC_MASK) != 0)
		*stat = 0;
	else
		*stat = 1;
}
/*check if reciver recieved new data*/
void UART_RecieveStatus(u8 * stat) {
	if ((UARTx->USART_SR && USART_SR_RXNE_MASK) != 0)
		*stat = 0;
	else
		*stat = 1;
}
void UART_CalculateBaudrate(u32 Baudrate) {
	u8 clock = 1;
	RCC_GetSytemFreq(&clock); //7ot el fnc bta3tak ya 8areeb
	u32 tempB = Baudrate * clock;
	u32 baudrateMentesa = ((tempB) / 1000);
	u32 baudrateExp = (tempB - baudrateMentesa) / 100;
	if (baudrateExp % 10 > 5)
		baudrateExp += 10;
	baudrateExp = (16 * baudrateExp) / 10;
	UARTx->USART_BRR = (baudrateMentesa << 4) | (baudrateExp);
}
