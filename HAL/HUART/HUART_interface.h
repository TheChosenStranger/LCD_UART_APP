#ifndef HUART_INTERFACE
#define HUART_INTERFACE 

STD_ERROR HUART_Transmit(u8* buffer,u16 length);
STD_ERROR HUART_Recieve(u8* buffer,u16* length);

#endif