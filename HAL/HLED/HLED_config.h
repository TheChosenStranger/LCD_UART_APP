#ifndef HLED_CONFIG_H
#define HLED_CONFIG_H 

/*	to add a new LED:				
*	define LED and use LED_CONFIG(HLED_PIN0 -> HLED_PIN15 , HLED_PORTA or HLED_PORTB or HLED_PORTC , HLED_ACTIVE_HIGH or HLED_ACTIVE_LOW)
*	then add LED to corresponding port
*
*
*
*
*/
#define LED_0 LED_CONFIG(HLED_PIN13	,HLED_PORTC,HLED_ACTIVE_LOW)

/*PortA leds*/
#define HLED_PORTA_LEDS (0 & HLED_PIN_MASK)
/*PortB leds*/
#define HLED_PORTB_LEDS (0 & HLED_PIN_MASK)
/*PortC leds*/
#define HLED_PORTC_LEDS ((LED_0) & HLED_PIN_MASK)

#endif
