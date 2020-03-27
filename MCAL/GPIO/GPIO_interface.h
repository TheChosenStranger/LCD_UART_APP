/*
 * GPIO_interface.h
 *
 *  Created on: Jan 27, 2020
 *      Author: Moamen
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

typedef struct {
	u32 CRL;
	u32 CRH;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 BRR;
	u32 LCKR;
} GPIO_x;

//(*(GPIO_x*)GPIO_A_BASE_ADDRESS)
#define GPIO_A_BASE_ADDRESS 0x40010800
#define GPIO_B_BASE_ADDRESS 0x40010C00
#define GPIO_C_BASE_ADDRESS 0x40011000

#define GPIO_A ((GPIO_x volatile * const)GPIO_A_BASE_ADDRESS)
#define GPIO_B ((GPIO_x volatile * const)GPIO_B_BASE_ADDRESS)
#define GPIO_C ((GPIO_x volatile * const)GPIO_C_BASE_ADDRESS)

#define GPIO_CNF_IP_ANALOG 					0b0000
#define GPIO_CNF_IP_FLOATING 				0b0100
#define GPIO_CNF_IP_PULL_UP_DOWN 			0b1000

#define GPIO_CNF_GPO_PUSH_PULL 				0b0000
#define GPIO_CNF_GPO_OPEN_DRAIN 			0b0100
#define GPIO_CNF_AF_PUSH_PULL 				0b1000
#define GPIO_CNF_AF_OPEN_DRAIN 				0b1100

#define GPIO_MODE_INPUT        				0b0000
#define GPIO_MODE_OUTPUT_10_MHZ 			0b0001
#define GPIO_MODE_OUTPUT_2_MHZ				0b0010
#define GPIO_MODE_OUTPUT_50_MHZ				0b0011

#define GPIO_PIN0 	0x01
#define GPIO_PIN1 	0x02
#define GPIO_PIN2 	0x04
#define GPIO_PIN3 	0x08
#define GPIO_PIN4 	0x10
#define GPIO_PIN5 	0x20
#define GPIO_PIN6 	0x40
#define GPIO_PIN7 	0x80
#define GPIO_PIN8 	0x100
#define GPIO_PIN9 	0x200
#define GPIO_PIN10 	0x400
#define GPIO_PIN11 	0x800
#define GPIO_PIN12 	0x1000
#define GPIO_PIN13 	0x2000
#define GPIO_PIN14 	0x4000
#define GPIO_PIN15 	0x8000

#define GPIO_PORT_A 0
#define GPIO_PORT_B 1
#define GPIO_PORT_C 2


#define PORTS_ARRAY { GPIO_A, GPIO_B, GPIO_C }

#define GPIO_CRL_THRESHOLD 8
#define GPIO_CRH_THRESHOLD 16

#define GPIO_CLEAR_MASK 0b1111

#define GPIO_PIN_OFFSET 4

#define GPIO_HIGH 1
#define GPIO_LOW 0

#define GPIO_END_OF_STRUCT 0xFF

typedef struct GPIO_t {
	u16 pin;
	u8 port;
	u8 mode;
	u8 speed;
} GPIO_t;

STD_ERROR GPIO_Config(GPIO_t*);
STD_ERROR GPIO_GetPinValue(u16 Pin, u8 Port, u8* Value);
STD_ERROR GPIO_SetPinValue(u16 Pin, u8 Port, u8 Value);

#endif /* GPIO_INTERFACE_H_ */
