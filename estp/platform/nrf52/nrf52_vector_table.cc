
#include <cstdint>

#include "estp/base/macros.hh"

namespace estp {

extern "C" {
    void POWER_CLOCK_IRQHandler(void);
    void RADIO_IRQHandler(void);
    void UARTE0_UART0_IRQHandler(void);
    void SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler(void);
    void SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler(void);
    void NFCT_IRQHandler(void);
    void GPIOTE_IRQHandler(void);
    void SAADC_IRQHandler(void);
    void TIMER0_IRQHandler(void);
    void TIMER1_IRQHandler(void);
    void TIMER2_IRQHandler(void);
    void RTC0_IRQHandler(void);
    void TEMP_IRQHandler(void);
    void RNG_IRQHandler(void);
    void ECB_IRQHandler(void);
    void CCM_AAR_IRQHandler(void);
    void WDT_IRQHandler(void);
    void RTC1_IRQHandler(void);
    void QDEC_IRQHandler(void);
    void COMP_LPCOMP_IRQHandler(void);
    void SWI0_EGU0_IRQHandler(void);
    void SWI1_EGU1_IRQHandler(void);
    void SWI2_EGU2_IRQHandler(void);
    void SWI3_EGU3_IRQHandler(void);
    void SWI4_EGU4_IRQHandler(void);
    void SWI5_EGU5_IRQHandler(void);
    void TIMER3_IRQHandler(void);
    void TIMER4_IRQHandler(void);
    void PWM0_IRQHandler(void);
    void PDM_IRQHandler(void);
    void MWU_IRQHandler(void);
    void PWM1_IRQHandler(void);
    void PWM2_IRQHandler(void);
    void SPIM2_SPIS2_SPI2_IRQHandler(void);
    void RTC2_IRQHandler(void);
    void I2S_IRQHandler(void);
    void FPU_IRQHandler(void);
}

// NRF52 Exception Table
// Declare this extern "C" so the name does not get mangled
// This is so that we can reference this table directly in the linker script by name
using ExceptionHandler = void (*)(void);

extern "C" SECTION(".vector_table.nrf52") USED
ExceptionHandler const kNrf52VectorTable[] = {
    POWER_CLOCK_IRQHandler,
    RADIO_IRQHandler,
    UARTE0_UART0_IRQHandler,
    SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler,
    SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler,
    NFCT_IRQHandler,
    GPIOTE_IRQHandler,
    SAADC_IRQHandler,
    TIMER0_IRQHandler,
    TIMER1_IRQHandler,
    TIMER2_IRQHandler,
    RTC0_IRQHandler,
    TEMP_IRQHandler,
    RNG_IRQHandler,
    ECB_IRQHandler,
    CCM_AAR_IRQHandler,
    WDT_IRQHandler,
    RTC1_IRQHandler,
    QDEC_IRQHandler,
    COMP_LPCOMP_IRQHandler,
    SWI0_EGU0_IRQHandler,
    SWI1_EGU1_IRQHandler,
    SWI2_EGU2_IRQHandler,
    SWI3_EGU3_IRQHandler,
    SWI4_EGU4_IRQHandler,
    SWI5_EGU5_IRQHandler,
    TIMER3_IRQHandler,
    TIMER4_IRQHandler,
    PWM0_IRQHandler,
    PDM_IRQHandler,
    nullptr,
    nullptr,
    MWU_IRQHandler,
    PWM1_IRQHandler,
    PWM2_IRQHandler,
    SPIM2_SPIS2_SPI2_IRQHandler,
    RTC2_IRQHandler,
    I2S_IRQHandler,
    FPU_IRQHandler,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
};

}  // namespace estp
