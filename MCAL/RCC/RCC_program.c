/******************************/
/* Author  : Moustafa Ghareeb */
/* Version : V1.5             */
/* Date    : 6-3-2020         */
/******************************/

#include "../../LIB/STD_TYPES.h"

#include "RCC_interface.h"
/*Defining a structure that holds all the RCC registers*/
typedef struct RCC_
{
	u32 CR;
	u32 CFGR;
	u32 CIR;
	u32 APB2RSTR;
	u32 APB1RSTR;
	u32 AHBENR;
	u32 APB2ENR;
	u32 APB1ENR;
	u32 BDCR;
	u32 CS;
}RCC_;
/*Defining the base address for the RCC and creating a structure at this base*/
#define  RCC_BASE_ADDRESS  0x40021000					
#define  RCC ((RCC_ volatile * const)RCC_BASE_ADDRESS)

/*This function switches the SYSCLK to the desired input clock [HSI-HSE-PLL]*/
STD_ERROR RCC_u8SystemClockSelect(u8 source)
{
	STD_ERROR local_error = OK;
	switch(source)
	{
	case HSI:
		if(RCC->CR & HSIRDY_MASK) /*Checks if the HSI is ready*/
		{
			RCC->CFGR = (RCC->CFGR & ~SW_CLEAR_MASK) |  SW_HSI_MASK;	/*Switch to HSI by setting SW=00*/
		}
		else
		{local_error = NOT_OK;}
		break;
	case HSE:
		if(RCC->CR & HSERDY_MASK) /*Checks if the HSE is ready*/
		{
			RCC->CFGR = (RCC->CFGR & ~SW_CLEAR_MASK) |  SW_HSE_MASK;	/*Switch to HSE by setting SW=01*/
		}
		else
		{local_error = NOT_OK;}
		break;
	case PLL:
		if(RCC->CR & PLLRDY_MASK) /*Checks if the PLL is ready*/
		{
			RCC->CFGR = (RCC->CFGR & ~SW_CLEAR_MASK) |  SW_PLL_MASK;	/*Switch to PLL by setting SW=10*/
		}
		else
		{local_error = NOT_OK;}
		break;
	default:
		local_error = NOT_OK;
		break;
	}
	return local_error;
}

/*This function takes the name of the clock as input and enables it [HSI-HSE-PLL]*/
STD_ERROR RCC_u8EnableClock(u8 source)
{
	STD_ERROR local_error = OK;
	switch(source)
	{
	case HSI:
		if(!(RCC->CR & HSIRDY_MASK)) /*Checks if the HSI is not ready*/
		{
			RCC->CR |= HSION_MASK;	/*Enable HSI*/
			while(!(RCC->CR & HSIRDY_MASK)){;} /*Wait until ready*/
		}
		break;
	case HSE:
		if(!(RCC->CR & HSERDY_MASK)) /*Checks if the HSE is not ready*/
		{
			RCC->CR |= HSEON_MASK;	/*Enable HSE*/
			while(!(RCC->CR & HSERDY_MASK)){;} /*Wait until ready*/
		}
		break;
	case PLL:
		if(!(RCC->CR & PLLRDY_MASK)) /*Checks if the PLL is not ready*/
		{
			RCC->CR |= PLLON_MASK;	/*Enable PLL*/
			while(!(RCC->CR & PLLRDY_MASK)){;} /*Wait until ready*/
		}
		break;
	default:
		local_error = NOT_OK;
		break;
	}
	return local_error;
}

/*This function takes the name of the clock as input and Disables it unless it is the SYSCLK [HSI-HSE-PLL]*/
STD_ERROR RCC_u8DisableClock(u8 source)
{
	STD_ERROR local_error = OK;
	switch(source)
	{
	case HSI:
		if(!GET_BIT(RCC->CFGR,2) && !GET_BIT(RCC->CFGR,3)) /*Checks if the HSI is SYSCLK*/
		{
			local_error = NOT_OK;
		}
		else if(RCC->CR & HSIRDY_MASK) /*Checks if the HSI is ready*/
		{
			RCC->CR &= ~HSION_MASK;	/*Disable HSI*/
		}
		break;
	case HSE:
		if(GET_BIT(RCC->CFGR,2) && !GET_BIT(RCC->CFGR,3)) /*Checks if the HSE is SYSCLK*/
		{
			local_error = NOT_OK;
		}
		else if(RCC->CR & HSERDY_MASK) /*Checks if the HSE is ready*/
		{
			RCC->CR &= ~HSEON_MASK;	/*Disable HSE*/
		}
		break;
	case PLL:
		if(!GET_BIT(RCC->CFGR,2) && GET_BIT(RCC->CFGR,3)) /*Checks if the PLL is SYSCLK*/
		{
			local_error = NOT_OK;
		}
		else if(RCC->CR & PLLRDY_MASK) /*Checks if the PLL is ready*/
		{
			RCC->CR &= ~PLLON_MASK;	/*Disable PLL*/
		}
		break;
	default:
		local_error = NOT_OK;
		break;
	}
	return local_error;
}

/*This function configures the prescaler of any desired bus by the desired value [APB2-APB1-AHB] 
	[1-2-4-8-16] + [64-128-256-512] "for th AHB" note that the default value is '1'
 */
STD_ERROR RCC_u8BusPrescaler(u8 bus,u16 division)
{
	STD_ERROR local_error = OK;
	switch(bus)
	{
	case APB2:
		switch(division) /*Checks division value*/
		{
		case 2:
			RCC->CFGR = (RCC->CFGR & ~PPRE2_CLEAR_MASK)|(PPRE2_DIV02_MASK);	/*Divide by 2 by setting PPRE2=100*/
			break;
		case 4:
			RCC->CFGR = (RCC->CFGR & ~PPRE2_CLEAR_MASK)|(PPRE2_DIV04_MASK);	/*Divide by 4 by setting PPRE2=101*/
			break;
		case 8:
			RCC->CFGR = (RCC->CFGR & ~PPRE2_CLEAR_MASK)|(PPRE2_DIV08_MASK);	/*Divide by 8 by setting PPRE2=110*/
			break;
		case 16:
			RCC->CFGR = (RCC->CFGR & ~PPRE2_CLEAR_MASK)|(PPRE2_DIV16_MASK);	/*Divide by 16 by setting PPRE2=111*/
			break;
		default:
			RCC->CFGR = (RCC->CFGR & ~PPRE2_CLEAR_MASK)|(PPRE2_DIV01_MASK);	/*Divide by 1 by setting PPRE2=000*/
			break;
		}
		break;

	case APB1:
		switch(division) /*Checks division value*/
		{
		case 2:
			RCC->CFGR = (RCC->CFGR & ~PPRE1_CLEAR_MASK)|(PPRE1_DIV02_MASK);	/*Divide by 2 by setting PPRE1=100*/
			break;
		case 4:
			RCC->CFGR = (RCC->CFGR & ~PPRE1_CLEAR_MASK)|(PPRE1_DIV04_MASK);		/*Divide by 4 by setting PPRE1=101*/
			break;
		case 8:
			RCC->CFGR = (RCC->CFGR & ~PPRE1_CLEAR_MASK)|(PPRE1_DIV08_MASK);		/*Divide by 8 by setting PPRE1=110*/
			break;
		case 16:
			RCC->CFGR = (RCC->CFGR & ~PPRE1_CLEAR_MASK)|(PPRE1_DIV16_MASK);		/*Divide by 16 by setting PPRE1=111*/
			break;
		default:
			RCC->CFGR = (RCC->CFGR & ~PPRE1_CLEAR_MASK)|(PPRE1_DIV01_MASK);   	/*Divide by 1 by setting PPRE1=000*/
		}
		break;
	case AHB:
		switch(division) /*Checks division value*/
		{
		case 2:
			RCC->CFGR = (RCC->CFGR & ~HPRE_CLEAR_MASK)|(HPRE_DIV02_MASK);	/*Divide by 2 by setting HPRE=1000*/
			break;
		case 4:
			RCC->CFGR = (RCC->CFGR & ~HPRE_CLEAR_MASK)|(HPRE_DIV04_MASK);	/*Divide by 4 by setting HPRE=1001*/
			break;
		case 8:
			RCC->CFGR = (RCC->CFGR & ~HPRE_CLEAR_MASK)|(HPRE_DIV08_MASK);	/*Divide by 8 by setting HPRE=1010*/
			break;
		case 16:
			RCC->CFGR = (RCC->CFGR & ~HPRE_CLEAR_MASK)|(HPRE_DIV16_MASK);	/*Divide by 16 by setting HPRE=1011*/
			break;
		case 64:
			RCC->CFGR = (RCC->CFGR & ~HPRE_CLEAR_MASK)|(HPRE_DIV64_MASK);;	/*Divide by 64 by setting HPRE=1100*/
			break;
		case 128:
			RCC->CFGR = (RCC->CFGR & ~HPRE_CLEAR_MASK)|(HPRE_DIV128_MASK);	/*Divide by 128 by setting HPRE=1101*/
			break;
		case 256:
			RCC->CFGR = (RCC->CFGR & ~HPRE_CLEAR_MASK)|(HPRE_DIV256_MASK);	/*Divide by 256 by setting HPRE=1110*/
			break;
		case 512:
			RCC->CFGR = (RCC->CFGR & ~HPRE_CLEAR_MASK)|(HPRE_DIV512_MASK);	/*Divide by 512 by setting HPRE=1111*/
			break;
		default:
			RCC->CFGR = (RCC->CFGR & ~HPRE_CLEAR_MASK)|(HPRE_DIV01_MASK);	/*Divide by 1 by setting HPRE=000*/
			break;
		}
		break;
	default:
		local_error = NOT_OK;
		break;
	}
	return local_error;
}

/*This function configures the prescaler of the PLL clock and its source as input [HSI-HSE] 
	[1-2] for division
	[2-3-4-5-6-7-8-9-10-11-12-13-14-15-16] for multiplier
 */
STD_ERROR RCC_u8PLLConfigure(u8 source,u8 division,u8 multiplier)
{
	STD_ERROR local_error = OK;
	switch(source)
	{
	case HSI:
		if(RCC->CR & HSIRDY_MASK) /*Checks if the HSI is ready*/
		{
			RCC->CFGR &= ~PLLSRC_MASK; /*Select HSI/2 as PLL source*/
		}
		else
		{local_error = NOT_OK;}
		break;
	case HSE:
		RCC->CFGR |= PLLSRC_MASK;	/*Select HSE as PLL source*/
		if(division == 1)		/*Selects either division by 1 or 2*/
		{RCC->CFGR &= ~PLLXTPRE_MASK;}
		else if (division == 2)
		{RCC->CFGR |= PLLXTPRE_MASK;}
		else
		{local_error = NOT_OK;}
		break;
	default:
		local_error = NOT_OK;
		break;
	}
	if(multiplier>1 && multiplier <17)
	{
		/*"multiplier-PLLMUL_MULTIPLIER" is the value that is needed to be assigned to the PLLMUL bits*/
		/*shifting this value left by PLLMUL_MULTIPLIER_SHIFT creates the final value which could directly be put in the PLLMUL*/
		RCC->CFGR = (RCC->CFGR & ~PLLMUL_CLEAR_MASK)|((multiplier-PLLMUL_MULTIPLIER)<<PLLMUL_MULTIPLIER_SHIFT);	/*Sets PLL multiplier by setting PLLMUL*/
	}
	else
	{local_error = NOT_OK;}
	return local_error;
}

/*This function configures the clock for the MCO PIN [MCO_SYS-MCO_HSI-MCO_HSE-MCO_PLL] 
	note: when choosing PLL it is not actually the PLL it is PLL/2   */
STD_ERROR RCC_u8MCOConfigure(u32 source)
{
	STD_ERROR local_error = OK;
	u32 local_check = source & MCO_CHECK_MASK;
	if (local_check == MCO_CHECK_MASK)
	{
		RCC->CFGR = (RCC->CFGR & ~MCO_CLEAR_MASK) |  source;	/*Choose the MCO clock*/
	}
	else
	{
		RCC->CFGR &= ~MCO_CLEAR_MASK;			/*Choose no MCO clock*/
		local_error = NOT_OK;
	}
	return local_error;
}

/*This function enables the clock for any peripheral
[SDIO-FSMC-CRC-FLIT-SRAM-DMA2-DMA1-TIM11-TIM10-TIM9-ADC3-USART1-TIM8-SPI1-TIM1-ADC2-ADC1-IOPG-IOPF-IOPE-IOPD-IOPC-IOPB-IOPA-AFIO]*/

STD_ERROR RCC_u8EnablePeripheral(u32 peripheral)
{
	STD_ERROR local_error = OK;
	u32 local_check = peripheral  & BUS_CHECK_MASK;
	switch(local_check)
	{
	/*AHB bus peripheral*/
	case AHB_CHECK_MASK:
		RCC->AHBENR |= peripheral;	/*Enable selected AHB peripheral Clock*/
		break;
		/*APB2 bus peripheral*/
	case APB2_CHECK_MASK:
		RCC->APB2ENR = peripheral;	/*Enable selected APB2 peripheral Clock*/
		break;
		/*To be continued*/
	default:
		local_error = NOT_OK;
		break;
	}
	return local_error;
}

/*This function disables the clock for any peripheral
[SDIO-FSMC-CRC-FLIT-SRAM-DMA2-DMA1-TIM11-TIM10-TIM9-ADC3-USART1-TIM8-SPI1-TIM1-ADC2-ADC1-IOPG-IOPF-IOPE-IOPD-IOPC-IOPB-IOPA-AFIO]*/
STD_ERROR RCC_u8DisablePeripheral(u32 peripheral)
{
	STD_ERROR local_error = OK;
	u32 local_check = peripheral & BUS_CHECK_MASK;
	switch(local_check)
	{
	/*AHB bus peripheral*/
	case AHB_CHECK_MASK:
		RCC->AHBENR &= ~peripheral;	/*Disable selected AHB peripheral Clock*/
		break;
		/*APB2 bus peripheral*/
	case APB2_CHECK_MASK:
		RCC->APB2ENR &= ~peripheral;	/*Disable selected APB2 peripheral Clock*/
		break;
		/*To be continued*/
	default:
		local_error = NOT_OK;
		break;
	}
	return local_error;
}

/*This function gets the clock of any peripheral
[SDIO-FSMC-CRC-FLIT-SRAM-DMA2-DMA1-SYSTK-TIM11-TIM10-TIM9-ADC3-USART1-TIM8-SPI1-TIM1-ADC2-ADC1-IOPG-IOPF-IOPE-IOPD-IOPC-IOPB-IOPA-AFIO]*/
STD_ERROR RCC_u8GetPeripheralFreq(u32 peripheral ,u32 *local_sysclk)
{
	STD_ERROR local_error = OK;
	u32 local_check = peripheral & BUS_CHECK_MASK;
	u32 pll_mult;
	/*Get SYSCLK*/
	*local_sysclk = (RCC->CFGR & SWS_MASK);
	switch(*local_sysclk)
	{
	/*HSI is the SYSCLK*/
	case SWS_HSI:
		*local_sysclk = 	HSI_FREQ;	/*Gets HSI frequency*/
		break;
	/*HSE is the SYSCLK*/
	case SWS_HSE:
		*local_sysclk = 	HSE_FREQ;	/*Gets HSE frequency*/
		break;
	/*PLL is the SYSCLK*/
	case SWS_PLL:
		/*Gets PLL frequency*/
		/*Get the PLL source*/
		*local_sysclk = (RCC->CFGR & PLLSRC_MASK);
		if(!*local_sysclk)
			{*local_sysclk = HSI_FREQ_BY2;}
		else
			{	/*Get the HSE divider for PLL*/
				*local_sysclk = (RCC->CFGR & PLLXTPRE_MASK);
				if(!*local_sysclk)
					{*local_sysclk = HSE_FREQ;}
				else
					{*local_sysclk = HSE_FREQ_BY2;}
			}
			/*Get the PLL divider*/
			pll_mult = ((RCC->CFGR & PLLMUL_CLEAR_MASK) >> PLLMUL_MULTIPLIER_SHIFT) + PLLMUL_MULTIPLIER;
			*local_sysclk *= pll_mult;
		break;
	default:
		local_error = NOT_OK;
		break;
	}

	switch(local_check)
	{
	/*AHB bus peripheral*/
	case AHB_CHECK_MASK:
	local_check = RCC->CFGR & HPRE_CLEAR_MASK;
	switch(local_check) /*Gets AHB bus Clock*/
		{
		case HPRE_DIV02_MASK:
			*local_sysclk /= 2;	/*Divided by 2*/
			break;
		case HPRE_DIV04_MASK:
			*local_sysclk /= 4;	/*Divided by 4*/
			break;
		case HPRE_DIV08_MASK:
			*local_sysclk /= 6;	/*Divided by 8*/
			break;
		case HPRE_DIV16_MASK:
			*local_sysclk /= 8;	/*Divided by 16*/
			break;
		case HPRE_DIV64_MASK:
			*local_sysclk /= 10;	/*Divided by 64*/
			break;
		case HPRE_DIV128_MASK:
			*local_sysclk /= 128;/*Divided by 128*/
			break;
		case HPRE_DIV256_MASK:
			*local_sysclk /= 256;/*Divided by 256*/
			break;
		case HPRE_DIV512_MASK:
			*local_sysclk /= 512;/*Divided by 512*/
			break;
		default:
			*local_sysclk /= 1;	/*Divided by 1*/
			break;
		}
		break;
		/*APB2 bus peripheral*/
	case APB2_CHECK_MASK:
		local_check = RCC->CFGR & PPRE2_CLEAR_MASK;
		switch(local_check) /*Gets APB2 bus Clock*/
		{
		case PPRE2_DIV02_MASK:
			*local_sysclk /= 2;	/*Divided by 2*/
			break;
		case PPRE2_DIV04_MASK:
			*local_sysclk /= 4;	/*Divided by 4*/
			break;
		case PPRE2_DIV08_MASK:
			*local_sysclk /= 6;	/*Divided by 8*/
			break;
		case PPRE2_DIV16_MASK:
			*local_sysclk /= 8;	/*Divided by 16*/
			break;
		default:
			*local_sysclk /= 1;	/*Divided by 1*/
			break;
		}							
		break;
		/*To be continued*/
	default:
		local_error = NOT_OK;
		break;
	}
	return local_error;
}