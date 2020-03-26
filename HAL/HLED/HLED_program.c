#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "HLED_interface.h"
#include "HLED_config.h"

STD_ERROR HLED_Init() {
	STD_ERROR Local_STD_ERRORError = OK;
	GPIO_t t;
#if HLED_PORTA_LEDS
	t.port = GPIO_PORT_A;
	t.speed = GPIO_MODE_OUTPUT_10_MHZ;
	t.mode = GPIO_CNF_GPO_PUSH_PULL;
	t.pin = HLED_PORTA_LEDS;
	Local_STD_ERRORError = GPIO_Config(&t);
#endif
#if HLED_PORTB_LEDS
	t.port = GPIO_PORT_B;
	t.speed = GPIO_MODE_OUTPUT_10_MHZ;
	t.mode = GPIO_CNF_GPO_PUSH_PULL;
	t.pin = HLED_PORTB_LEDS;
	Local_STD_ERRORError = GPIO_Config(&t);
#endif
#if HLED_PORTC_LEDS
	t.port = GPIO_PORT_C;
	t.speed = GPIO_MODE_OUTPUT_10_MHZ;
	t.mode = GPIO_CNF_GPO_PUSH_PULL;
	t.pin = HLED_PORTC_LEDS;
	Local_STD_ERRORError = GPIO_Config(&t);
#endif
	return Local_STD_ERRORError;
}

STD_ERROR HLED_LedOn(u32 led) {
	STD_ERROR Local_STD_ERRORError = OK;
	GPIO_SetPinValue(led, (led >> 16) - 1, (led >> 18));
	return Local_STD_ERRORError;
}
STD_ERROR HLED_LedOff(u32 led) {
	STD_ERROR Local_STD_ERRORError = OK;
	GPIO_SetPinValue(led & HLED_PIN_MASK, (led >> 16) - 1, (led >> 18) ^ 1);
	return Local_STD_ERRORError;
}
