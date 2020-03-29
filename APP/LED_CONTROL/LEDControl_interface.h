/******************************/
/* Author  : Moustafa Ghareeb */
/* Version : V1.0             */
/* Date    : 27-03-2020       */
/******************************/
#ifndef LEDCONTROL_INTERFACE_H_
#define LEDCONTROL_INTERFACE_H_

/*Defining the name used for the LED(s) used in the app*/
#define INDICATOR_LED	LED_0

/*Functions prototypes*/
STD_ERROR LEDControl_u8Init(void);
void LEDControl_voidRunnable(void);

#endif
