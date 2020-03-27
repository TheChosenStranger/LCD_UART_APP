#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "HLED_config.h"
#include "HLED_interface.h"


/*sets initial configrations for LEDs on ports a,b,c*/
STD_ERROR HLED_Init() {
	STD_ERROR Local_STD_ERRORError = OK;
	GPIO_t t;
#ifdef HLED_PORTA_LEDS
	t.port = GPIO_PORT_A;
	t.speed = GPIO_MODE_OUTPUT_10_MHZ;
	t.mode = GPIO_CNF_GPO_PUSH_PULL;
	t.pin = HLED_PORTA_LEDS;
	Local_STD_ERRORError = GPIO_Config(&t);
#endif
#ifdef HLED_PORTB_LEDS
	t.port = GPIO_PORT_B;
	t.speed = GPIO_MODE_OUTPUT_10_MHZ;
	t.mode = GPIO_CNF_GPO_PUSH_PULL;
	t.pin = HLED_PORTB_LEDS;
	Local_STD_ERRORError = GPIO_Config(&t);
#endif
#ifdef HLED_PORTC_LEDS
	t.port = GPIO_PORT_C;
	t.speed = GPIO_MODE_OUTPUT_10_MHZ;
	t.mode = GPIO_CNF_GPO_PUSH_PULL;
	t.pin = HLED_PORTC_LEDS;
	Local_STD_ERRORError = GPIO_Config(&t);
#endif
	return Local_STD_ERRORError;
}
/*turn led on pass argument
*	led= LED_0,LED_1,LED_2,...
*/
STD_ERROR HLED_LedOn(u32 led) {
	STD_ERROR Local_STD_ERRORError = OK;
	Local_STD_ERRORError=GPIO_SetPinValue(HLED_GET_PINS(led), HLED_GET_PORT(led), HLED_GET_ON(led));
	return Local_STD_ERRORError;
}
STD_ERROR HLED_LedOff(u32 led) {
	STD_ERROR Local_STD_ERRORError = OK;
	Local_STD_ERRORError=GPIO_SetPinValue(HLED_GET_PINS(led), HLED_GET_PORT(led), HLED_GET_OFF(led));
	return Local_STD_ERRORError;
}
