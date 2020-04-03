#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

typedef  void(*txCbf_t)(void) ;
typedef  void(*rxCbf_t)(void) ;


typedef struct {
	u8 *Buffer;
	u16 MessageLength;
	u8 TransmitionComplete;
	u16 CurrentPosition;
}UART_Message_Frame_t;

#define UART_TRASMIT_COMPLETE		1
#define UART_TRASMIT_NOT_COMPLETE	0

#define USART1_TX_PORT 				GPIO_PORT_A
#define USART1_TX_PIN  				GPIO_PIN9 

#define USART1_RX_PORT 				GPIO_PORT_A
#define USART1_RX_PIN  				GPIO_PIN10

#define USART1_TX_MODE 				GPIO_CNF_GPO_PUSH_PULL
#define USART1_TX_SPEED 			GPIO_MODE_OUTPUT_50_MHZ


#define USART1_RX_CNF				GPIO_CNF_IP_PULL_UP_DOWN
#define USART1_RX_MODE 				GPIO_MODE_INPUT

#define USART_SR_TXE_MASK 				0x00000080
#define USART_SR_TC_MASK 				0x00000040
#define USART_SR_RXNE_MASK 				0x00000020

#define USART_DR_MASK 					0x000001FF

#define USART_BRR_MASK					0x0000FFFF

#define USART_BAUDRATE_1200   52083
#define USART_BAUDRATE_2400   26041
#define USART_BAUDRATE_4800   13020
#define USART_BAUDRATE_9600   6510
#define USART_BAUDRATE_14400  4340
#define USART_BAUDRATE_19200  3255
#define USART_BAUDRATE_38400  1627
#define USART_BAUDRATE_57600  1085
#define USART_BAUDRATE_115200 542


#define USART_CR1_UE_MASK	 			0x00002000
#define USART_CR1_MWORD_LENGTH_MASK 	0x00001000
#define USART_CR1_PE_MASK 				0x00010400
#define USART_CR1_PS_MASK 				0x00020200
#define USART_CR1_PEIE_MASK 			0x00000100
#define USART_CR1_TXEIE_MASK			0x00000080
#define USART_CR1_TCIE_MASK				0x00000040
#define USART_CR1_RXENE_MASK			0x00000020
#define USART_CR1_TE_MASK				0x00000010
#define USART_CR1_RE_MASK				0x00000008

#define USART_CR2_STOPBITS_MASK			0x00003000

#define USART_CR3_HDSEL_MASK			0x00000008

#define USART_CR1_UE_ENABLE	 			0x00002000
#define USART_CR1_UE_DISABLE 			0x00000000
#define USART_CR1_MWORD_LENGTH_9BITS 	0x00001000
#define USART_CR1_MWORD_LENGTH_8BITS 	0x00000000
#define USART_CR1_PE_ENABLE				0x00010400
#define USART_CR1_PE_DISABLE			0x00010000
#define USART_CR1_PS_ODD				0x00020200
#define USART_CR1_PS_EVEN				0x00020000
#define USART_CR1_PEIE_ENABLE 			0x00000100
#define USART_CR1_PEIE_DISBALE 			0x00000000
#define USART_CR1_TXEIE_ENABLE			0x00000080
#define USART_CR1_TXEIE_DISABLE			0x00000000
#define USART_CR1_TCIE_ENABLE			0x00000040
#define USART_CR1_TCIE_DISABLE			0x00000000
#define USART_CR1_RXNEIE_ENABLE			0x00000020
#define USART_CR1_RXNEIE_DISABLE		0x00000000
#define USART_CR1_TE_ENABLE				0x00000010
#define USART_CR1_TE_DISABLE			0x00000000
#define USART_CR1_RE_ENABLE				0x00000008
#define USART_CR1_RE_DISABLE			0x00000000

#define USART_CR2_STOPBITS_1			0x00000000
#define USART_CR2_STOPBITS_0_5			0x00001000
#define USART_CR2_STOPBITS_2			0x00002000
#define USART_CR2_STOPBITS_1_5			0x00003000

#define USART_CR3_HDSEL_HALF_DUPLEX_ON	0x00000008
#define USART_CR3_HDSEL_HALF_DUPLEX_OFF	0x00000000

#define UART_STATE_NOT_BUSY 			0
#define UART_STATE_BUSY 				1

#define USART_PARITY_OFF 				USART_CR1_PE_DISABLE
#define USART_PARITY_EVEN 				(USART_CR1_PE_ENABLE | USART_CR1_PS_EVEN)
#define USART_PARITY_ODD 				(USART_CR1_PE_ENABLE | USART_CR1_PS_ODD)

#define UART_MAX_MESSAGE_LENGTH 		1000


#define UART_VALIDATE_BAUDRATE(BR) (BR==USART_BAUDRATE_1200)||(BR==USART_BAUDRATE_2400)||(BR==USART_BAUDRATE_4800)||(BR==USART_BAUDRATE_9600)||(BR==USART_BAUDRATE_14400)||(BR==USART_BAUDRATE_19200)||(BR==USART_BAUDRATE_38400)||(BR==USART_BAUDRATE_57600)||(BR==USART_BAUDRATE_115200)

STD_ERROR UART_Init(void);
STD_ERROR UART_Send(u8 * buffer, u16 len);
STD_ERROR UART_Receive(u8 * buffer, u16 len);
STD_ERROR UART_Configure(u32 baudrate, u8 stopBits, u32 parity);
STD_ERROR UART_SetTxCallbackFnc(txCbf_t txcbf);
STD_ERROR UART_SetRxCallbackFnc(rxCbf_t rxcbf);
void UART_DefaultTxCallback(void);
void UART_DefaultRxCallback(void);
void UART_TransmitStatus(u8 * stat);
void UART_RecieveStatus(u8 * stat);
void UART_CalculateBaudrate(u32 Baudrate);
#endif
