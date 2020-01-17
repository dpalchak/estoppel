
#include "estp/base/macros.hh"
#include <cstdint>

namespace estp {


extern "C" {
	void NO_RETURN Default_IRQHandler() {
		for(;;) {}
	}

	void WWDG_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void PVD_PVM_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TAMP_STAMP_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void RTC_WKUP_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void FLASH_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void RCC_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void EXTI0_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void EXTI1_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void EXTI2_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void EXTI3_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void EXTI4_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DMA1_Channel1_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DMA1_Channel2_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DMA1_Channel3_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DMA1_Channel4_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DMA1_Channel5_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DMA1_Channel6_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DMA1_Channel7_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void ADC1_2_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void CAN1_TX_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void CAN1_RX0_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void CAN1_RX1_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void CAN1_SCE_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void EXTI9_5_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TIM1_BRK_TIM15_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TIM1_UP_TIM16_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TIM1_TRG_COM_TIM17_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TIM1_CC_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TIM2_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TIM3_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TIM4_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void I2C1_EV_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void I2C1_ER_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void I2C2_EV_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void I2C2_ER_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void SPI1_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void SPI2_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void USART1_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void USART2_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void USART3_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void EXTI15_10_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void RTC_Alarm_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DFSDM1_FLT3_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TIM8_BRK_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TIM8_UP_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TIM8_TRG_COM_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TIM8_CC_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void ADC3_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void FMC_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void SDMMC1_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TIM5_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void SPI3_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void UART4_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void UART5_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TIM6_DAC_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TIM7_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DMA2_Channel1_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DMA2_Channel2_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DMA2_Channel3_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DMA2_Channel4_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DMA2_Channel5_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DFSDM1_FLT0_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DFSDM1_FLT1_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DFSDM1_FLT2_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void COMP_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void LPTIM1_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void LPTIM2_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void OTG_FS_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DMA2_Channel6_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void DMA2_Channel7_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void LPUART1_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void QUADSPI_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void I2C3_EV_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void I2C3_ER_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void SAI1_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void SAI2_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void SWPMI1_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void TSC_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void LCD_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void AES_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void RNG_IRQHandler() WEAK ALIAS("Default_IRQHandler");
	void FPU_IRQHandler() WEAK ALIAS("Default_IRQHandler");
}

// STM32L4xx Interrupt Vector Table
// Declare this extern "C" so the name does not get mangled
// This is so that we can reference this table directly in the linker script by name
using Vector = void (*)(void);

extern "C"
SECTION(".stm32l4xx_vector_table")
USED
Vector const kStm32l4xxInterruptVectorTable[] = {
	WWDG_IRQHandler,
	PVD_PVM_IRQHandler,
	TAMP_STAMP_IRQHandler,
	RTC_WKUP_IRQHandler,
	FLASH_IRQHandler,
	RCC_IRQHandler,
	EXTI0_IRQHandler,
	EXTI1_IRQHandler,
	EXTI2_IRQHandler,
	EXTI3_IRQHandler,
	EXTI4_IRQHandler,
	DMA1_Channel1_IRQHandler,
	DMA1_Channel2_IRQHandler,
	DMA1_Channel3_IRQHandler,
	DMA1_Channel4_IRQHandler,
	DMA1_Channel5_IRQHandler,
	DMA1_Channel6_IRQHandler,
	DMA1_Channel7_IRQHandler,
	ADC1_2_IRQHandler,
	CAN1_TX_IRQHandler,
	CAN1_RX0_IRQHandler,
	CAN1_RX1_IRQHandler,
	CAN1_SCE_IRQHandler,
	EXTI9_5_IRQHandler,
	TIM1_BRK_TIM15_IRQHandler,
	TIM1_UP_TIM16_IRQHandler,
	TIM1_TRG_COM_TIM17_IRQHandler,
	TIM1_CC_IRQHandler,
	TIM2_IRQHandler,
	TIM3_IRQHandler,
	TIM4_IRQHandler,
	I2C1_EV_IRQHandler,
	I2C1_ER_IRQHandler,
	I2C2_EV_IRQHandler,
	I2C2_ER_IRQHandler,
	SPI1_IRQHandler,
	SPI2_IRQHandler,
	USART1_IRQHandler,
	USART2_IRQHandler,
	USART3_IRQHandler,
	EXTI15_10_IRQHandler,
	RTC_Alarm_IRQHandler,
	DFSDM1_FLT3_IRQHandler,
	TIM8_BRK_IRQHandler,
	TIM8_UP_IRQHandler,
	TIM8_TRG_COM_IRQHandler,
	TIM8_CC_IRQHandler,
	ADC3_IRQHandler,
	FMC_IRQHandler,
	SDMMC1_IRQHandler,
	TIM5_IRQHandler,
	SPI3_IRQHandler,
	UART4_IRQHandler,
	UART5_IRQHandler,
	TIM6_DAC_IRQHandler,
	TIM7_IRQHandler,
	DMA2_Channel1_IRQHandler,
	DMA2_Channel2_IRQHandler,
	DMA2_Channel3_IRQHandler,
	DMA2_Channel4_IRQHandler,
	DMA2_Channel5_IRQHandler,
	DFSDM1_FLT0_IRQHandler,
	DFSDM1_FLT1_IRQHandler,
	DFSDM1_FLT2_IRQHandler,
	COMP_IRQHandler,
	LPTIM1_IRQHandler,
	LPTIM2_IRQHandler,
	OTG_FS_IRQHandler,
	DMA2_Channel6_IRQHandler,
	DMA2_Channel7_IRQHandler,
	LPUART1_IRQHandler,
	QUADSPI_IRQHandler,
	I2C3_EV_IRQHandler,
	I2C3_ER_IRQHandler,
	SAI1_IRQHandler,
	SAI2_IRQHandler,
	SWPMI1_IRQHandler,
	TSC_IRQHandler,
	LCD_IRQHandler,
	AES_IRQHandler,
	RNG_IRQHandler,
	FPU_IRQHandler
};

} // namespace estp


