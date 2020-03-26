#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "HLED_interface.h"
#include "HLED_config.h"

//static u32 LEDS[MAX_LEDS];
//static u8 LedIndex = 0;
//static u8 PORTA_ACTIVE=0;
STD_ERR HLED_Init() {
	STD_ERR Local_STD_ERRError = OK;
	GPIO_t t;
#if HLED_PORTA_LEDS
	t.port = GPIO_PORT_A;
	t.speed = GPIO_MODE_OUTPUT_10_MHZ;
	t.mode = GPIO_CNF_GPO_PUSH_PULL;
	t.pin = HLED_PORTA_LEDS;
	Local_STD_ERRError = GPIO_Config(&t);
#endif
#if HLED_PORTB_LEDS
	t.port = GPIO_PORT_B;
	t.speed = GPIO_MODE_OUTPUT_10_MHZ;
	t.mode = GPIO_CNF_GPO_PUSH_PULL;
	t.pin = HLED_PORTB_LEDS;
	Local_STD_ERRError = GPIO_Config(&t);
#endif
#if HLED_PORTC_LEDS
	t.port = GPIO_PORT_C;
	t.speed = GPIO_MODE_OUTPUT_10_MHZ;
	t.mode = GPIO_CNF_GPO_PUSH_PULL;
	t.pin = HLED_PORTC_LEDS;
	Local_STD_ERRError = GPIO_Config(&t);
#endif
	/*LEDS[0]=HLED_PORTA_LEDS;
	 LEDS[1]=HLED_PORTB_LEDS;
	 LEDS[2]=HLED_PORTC_LEDS;*/
	return Local_STD_ERRError;
}

STD_ERR HLED_LedOn(u32 led) {
	STD_ERR Local_STD_ERRError = OK;
	GPIO_SetPinValue(led, (led >> 16) - 1, (led >> 18));
	return Local_STD_ERRError;
}
STD_ERR HLED_LedOff(u32 led) {
	STD_ERR Local_STD_ERRError = OK;
	GPIO_SetPinValue(led & HLED_PIN_MASK, (led >> 16) - 1, (led >> 18) ^ 1);
	return Local_STD_ERRError;
}
