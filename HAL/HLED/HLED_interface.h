#ifndef HLED_INTERFACE_H
#define HLED_INTERFACE_H

typedef struct LED_{
	u8 pin;
	u8 port;
	u8 active;
}LED_h;




STD_ERR HLED_Init();
STD_ERR HLED_LedOn(u32);
STD_ERR HLED_LedOff(u32);

#endif
