#include "STD_TYPES.h"
#include "UTIL_interface.h"

void NumberToString(u32 Copy_u32_Number,u8* String,u16* Length){
	u16 i, count;
    u32 temp,n;
    u8GetNumberLength(Copy_u32_Number,&count);
    *Length=count;
    i = count;
    temp = Copy_u32_Number;
    if(!Copy_u32_Number)
    	String[0]='0';
    while (i > 0) {
        n = getPower(10, i - 1);
        Copy_u32_Number = temp;
        Copy_u32_Number = Copy_u32_Number / n;
        String[count-i]=(Copy_u32_Number + '0');
        temp = temp - Copy_u32_Number * n;
        i--;
    }
}
void StringToNumber(u32* Number,u8* String,u16 Length){
	u8 i;
	u32 power;
	u32 temp=0;
	for ( i = 0; i < Length; ++i)
	{
		power=getPower(10, Length-i-1);
		temp+=(String[i]-'0')*power;
		/* code */
	}
	*Number=temp;
}
void u8GetNumberLength(u32 Copy_u32_Number,u16* length) {
    u16 count = 0;
    while (Copy_u32_Number != 0) {
        Copy_u32_Number = Copy_u32_Number / 10;
        count++;
    }
    *length= count;
}
u32 getPower(u32 num, u8 pow) {
    u8 i;
    u32 res = 1;
    for (i = 0; i < pow; i++) {
        res = res * num;
    }
    return res;
}