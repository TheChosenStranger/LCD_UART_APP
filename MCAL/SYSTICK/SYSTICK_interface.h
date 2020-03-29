/******************************/
/* Author  : Moustafa Ghareeb */
/* Version : V1.0             */
/* Date    : 10-03-2020       */
/******************************/
#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

/*Defining peripheral masks*/
#define SYSTIC_EXCEPTION_EN			(0x00000002)
#define SYSTIC_EXCEPTION_DIS		(0x00000000)
#define SYSTIC_ENABLE_MASK			(0x00000001)
#define SYSTIC_PRESCALER_CHECK_MASK	(0xCFFFFFFF)
#define SYSTIC_PRESCALER_NONE		(0xC0000004)
#define SYSTIC_PRESCALER_BY8		(0xC0000000)
#define SYSTIC_START_MASK			(0xA0000001)
#define SYSTIC_STOP_MASK			(0xAFFFFFFE)

#define SYSTIC_PRESCALER_DIV			8
#define SYSTK						(0x40000000)

/*Initial configurations*/
#define SYSTIC_PRESCALER_INIT		SYSTIC_PRESCALER_BY8
#define SYSTIC_EXCEPTION_INIT		SYSTIC_EXCEPTION_EN

STD_ERROR SYSTICK_u8Init(void);
STD_ERROR SYSTICK_u8SetTime(u32 Copy_Time_us);
STD_ERROR SYSTICK_u8Start(void);
STD_ERROR SYSTICK_u8Stop(void);
STD_ERROR SYSTICK_u8SetCallback(void(*Copy_ptr)(void));
STD_ERROR SYSTICK_u8SetPrescaler(u32 Copy_Prescaler);
void SysTick_Handler(void);

#endif
