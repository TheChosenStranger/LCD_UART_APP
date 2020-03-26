/******************************/
/* Author  : Moustafa Ghareeb */
/* Version : V1.5             */
/* Date    : 6-3-2020         */
/******************************/

/*Defining standard error*/
#define NOK  0
#define	OK   1

/*Defining Clocls*/
#define HSI 0
#define	HSE 1
#define	PLL 2
#define	SYS 3

/*Defining buses*/
#define	APB2 0
#define	APB1 1
#define	AHB  2

/*Defining the CR register masks*/
#define HSION_MASK	(0x00000001)
#define HSIRDY_MASK	(0x00000002)
#define HSEON_MASK	(0x00010000)
#define HSERDY_MASK	(0x00020000)
#define PLLON_MASK	(0x01000000)
#define PLLRDY_MASK	(0x02000000)

/*Defining the CRFGR register masks*/
#define SW_CLEAR_MASK		(0x00000003)
#define SW_HSI_MASK			(0x00000000)
#define SW_HSE_MASK			(0x00000001)
#define SW_PLL_MASK			(0x00000002)
#define SWS_MASK			(0x0000000C)
#define SWS_HSI				(0x00000000)
#define SWS_HSE				(0x00000004)
#define SWS_PLL				(0x00000008)
#define HPRE_CLEAR_MASK		(0x000000f0)
#define HPRE_DIV01_MASK		(0x00000000)
#define HPRE_DIV02_MASK		(0x00000080)
#define HPRE_DIV04_MASK		(0x00000090)
#define HPRE_DIV08_MASK		(0x000000a0)
#define HPRE_DIV16_MASK		(0x000000b0)
#define HPRE_DIV64_MASK		(0x000000c0)
#define HPRE_DIV128_MASK	(0x000000d0)
#define HPRE_DIV256_MASK	(0x000000e0)
#define HPRE_DIV512_MASK	(0x000000f0)
#define PPRE1_CLEAR_MASK	(0x00000700)
#define PPRE1_DIV01_MASK	(0x00000000)
#define PPRE1_DIV02_MASK	(0x00000400)
#define PPRE1_DIV04_MASK	(0x00000500)
#define PPRE1_DIV08_MASK	(0x00000600)
#define PPRE1_DIV16_MASK	(0x00000700)
#define PPRE2_CLEAR_MASK	(0x00003800)
#define PPRE2_DIV01_MASK	(0x00000000)
#define PPRE2_DIV02_MASK	(0x00002000)
#define PPRE2_DIV04_MASK	(0x00002800)
#define PPRE2_DIV08_MASK	(0x00003000)
#define PPRE2_DIV16_MASK	(0x00003800)
#define PLLSRC_MASK			(0x00010000)
#define PLLXTPRE_MASK		(0x00020000)
#define PLLMUL_CLEAR_MASK	(0x003C0000)
#define MCO_CLEAR_MASK	    (0x07000000)
#define MCO_SYS_MASK	    (0x0C000000)
#define MCO_HSI_MASK	    (0x0D000000)
#define MCO_HSE_MASK	    (0x0E000000)
#define MCO_PLL_MASK	    (0x0F000000)

#define MCO_CHECK_MASK      (0x08000000)
/*Defining Peripherals for user use*/
#define MCO_SYS             MCO_SYS_MASK
#define MCO_HSI 			MCO_HSI_MASK
#define MCO_HSE 			MCO_HSE_MASK
#define MCO_PLL 			MCO_PLL_MASK

#define BUS_CHECK_MASK		(0xC0000000)
#define AHB_CHECK_MASK		(0x40000000)
#define APB2_CHECK_MASK		(0x80000000)
#define APB1_CHECK_MASK		(0xC0000000)
/*Defining the AHBENR register masks*/
#define AHB_SDIO_MASK		(0x40000400)
#define AHB_FSMC_MASK		(0x40000100)
#define AHB_CRC_MASK		(0x40000040)
#define AHB_FLITF_MASK		(0x40000010)
#define AHB_SRAM_MASK		(0x40000004)
#define AHB_DMA2_MASK		(0x40000002)
#define AHB_DMA1_MASK		(0x40000001)
#define AHB_SYSTICK_MASK	(0x40000000)

/*Defining the APB2EN register masks*/
#define APB2_TIM11_MASK		(0x80200000)
#define APB2_TIM10_MASK		(0x80100000)
#define APB2_TIM9_MASK		(0x80080000)
#define APB2_ADC3_MASK		(0x80008000)
#define APB2_USART1_MASK	(0x80004000)
#define APB2_TIM8_MASK		(0x80002000)
#define APB2_SPI1_MASK		(0x80001000)
#define APB2_TIM1_MASK		(0x80000800)
#define APB2_ADC2_MASK		(0x80000400)
#define APB2_ADC1_MASK		(0x80000200)
#define APB2_IOPG_MASK		(0x80000100)
#define APB2_IOPF_MASK		(0x80000080)
#define APB2_IOPE_MASK		(0x80000040)
#define APB2_IOPD_MASK		(0x80000020)
#define APB2_IOPC_MASK		(0x80000010)
#define APB2_IOPB_MASK		(0x80000008)
#define APB2_IOPA_MASK		(0x80000004)
#define APB2_AFIO_MASK		(0x80000001)

/*Defining Peripherals for user use*/
#define SDIO 	AHB_SDIO_MASK
#define FSMC 	AHB_FSMC_MASK
#define CRC 	AHB_CRC_MASK
#define FLIT 	AHB_FLITF_MASK
#define SRAM 	AHB_SRAM_MASK
#define DMA2 	AHB_DMA2_MASK
#define DMA1 	AHB_DMA1_MASK
#define SYSTK   AHB_SYSTICK_MASK
#define TIM11 	APB2_TIM11_MASK
#define TIM10 	APB2_TIM10_MASK
#define TIM9 	APB2_TIM9_MASK
#define ADC3 	APB2_ADC3_MASK
#define USART1 	APB2_USART1_MASK
#define TIM8 	APB2_TIM8_MASK
#define SPI1 	APB2_SPI1_MASK
#define TIM1 	APB2_TIM1_MASK
#define ADC2 	APB2_ADC2_MASK
#define ADC1 	APB2_ADC1_MASK
#define IOPG 	APB2_IOPG_MASK
#define IOPF 	APB2_IOPF_MASK
#define IOPE 	APB2_IOPE_MASK
#define IOPD 	APB2_IOPD_MASK
#define IOPC 	APB2_IOPC_MASK
#define IOPB 	APB2_IOPB_MASK
#define IOPA 	APB2_IOPA_MASK
#define AFIO 	APB2_AFIO_MASK

/*Defining clocks freqwuency*/
#define HSI_FREQ		8
#define HSI_FREQ_BY2	4
#define HSE_FREQ		8
#define HSE_FREQ_BY2	4
/*Will be continued*/

/*Defining the APB1EN register masks*/
/*Will be defined later*/


/*Defining helping parameters*/
#define PLLMUL_MULTIPLIER        ((u8)2)
#define PLLMUL_MULTIPLIER_SHIFT ((u8)18)

/*Defining functions*/
STD_ERROR RCC_u8SystemClockSelect(u8 source);
STD_ERROR RCC_u8EnableClock(u8 source);
STD_ERROR RCC_u8DisableClock(u8 source);
STD_ERROR RCC_u8BusPrescaler(u8 bus,u16 division);
STD_ERROR RCC_u8PLLConfigure(u8 source,u8 division,u8 multiplier);
STD_ERROR RCC_u8MCOConfigure(u32 source);
STD_ERROR RCC_u8EnablePeripheral(u32 periferal);
STD_ERROR RCC_u8DisablePeripheral(u32 periferal);
STD_ERROR RCC_u8GetPeripheralFreq(u32 periferal,u32 *local_sysclk);