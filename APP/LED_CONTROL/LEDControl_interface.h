/******************************/
/* Author  : Moustafa Ghareeb */
/* Version : V1.0             */
/* Date    : 27-03-2020       */
/******************************/
#ifndef LEDCONTROL_INTERFACE_H_
#define LEDCONTROL_INTERFACE_H_

#define INDICATOR_LED	LED_0

STD_ERROR LEDControl_u8Init(void);
void LEDControl_voidRunnable(void);

#endif
