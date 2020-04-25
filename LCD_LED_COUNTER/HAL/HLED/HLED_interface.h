#ifndef HLED_INTERFACE_H
#define HLED_INTERFACE_H

#define HLED_ACTIVE_LOW 	0
#define HLED_ACTIVE_HIGH 	0x40000

#define LED_CONFIG(PIN,PORT,ACTIVE) (PIN | PORT | ACTIVE)

#define HLED_PORTA 0x10000
#define HLED_PORTB 0x20000
#define HLED_PORTC 0x30000

#define HLED_PIN0 	GPIO_PIN0
#define HLED_PIN1 	GPIO_PIN1
#define HLED_PIN2 	GPIO_PIN2
#define HLED_PIN3 	GPIO_PIN3
#define HLED_PIN4 	GPIO_PIN4
#define HLED_PIN5 	GPIO_PIN5
#define HLED_PIN6 	GPIO_PIN6
#define HLED_PIN7 	GPIO_PIN7
#define HLED_PIN8 	GPIO_PIN8
#define HLED_PIN9 	GPIO_PIN9
#define HLED_PIN10 	GPIO_PIN10
#define HLED_PIN11 	GPIO_PIN11
#define HLED_PIN12	GPIO_PIN12
#define HLED_PIN13	GPIO_PIN13
#define HLED_PIN14	GPIO_PIN14
#define HLED_PIN15	GPIO_PIN15

#define HLED_PIN_MASK 0xFFFF
#define HLED_PORT_OFFSET 16
#define HLED_VALUE_OFFSET 18

#define HLED_GET_PINS(VAR) (VAR & HLED_PIN_MASK)
#define HLED_GET_PORT(VAR) (((VAR >> HLED_PORT_OFFSET) -1) & 0b11)
#define HLED_GET_ON(VAR) (VAR >> HLED_VALUE_OFFSET)
#define HLED_GET_OFF(VAR) ((HLED_GET_ON(VAR) >> HLED_VALUE_OFFSET) ^ 1)

typedef struct LED_{
	u8 pin;
	u8 port;
	u8 active;
}LED_h;


STD_ERROR HLED_Init();
STD_ERROR HLED_LedOn(u32);
STD_ERROR HLED_LedOff(u32);

#endif