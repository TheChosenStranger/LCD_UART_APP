#ifndef MESSAGE_TX_RX_INTERFACE
#define MESSAGE_TX_RX_INTERFACE 

#define BYTE_0_MASK 0xFF000000
#define BYTE_0_OFFSET 24
#define BYTE_1_MASK 0x00FF0000
#define BYTE_1_OFFSET 16
#define BYTE_2_MASK 0x0000FF00
#define BYTE_2_OFFSET 8
#define BYTE_3_MASK 0x000000FF
#define BYTE_3_OFFSET 00

#define FRAME_LENGTH 4

#define GET_BYTE(NUM,MASK,OFFSET) ( ( NUM & MASK) >> OFFSET )
#define SPLIT_MESSAGE(NUM) { GET_BYTE(NUM,BYTE_0_MASK,BYTE_0_OFFSET) , GET_BYTE(NUM,BYTE_1_MASK,BYTE_1_OFFSET) , GET_BYTE(NUM,BYTE_2_MASK,BYTE_2_OFFSET) , GET_BYTE(NUM,BYTE_3_MASK,BYTE_3_OFFSET) }
#define CONCAT_MESSAGE(NUM0,NUM1,NUM2,NUM3) ((NUM0 << BYTE_0_OFFSET )|(NUM1 << BYTE_1_OFFSET )|(NUM2 << BYTE_2_OFFSET )|(NUM3 << BYTE_3_OFFSET ))

void NumberToString(u32,u8*,u16*);
void StringToNumber(u32*,u8*,u16);
void u8GetNumberLength(u32 Copy_u32_Number,u16* length);
u32 getPower(u32 num, u8 pow);

#endif