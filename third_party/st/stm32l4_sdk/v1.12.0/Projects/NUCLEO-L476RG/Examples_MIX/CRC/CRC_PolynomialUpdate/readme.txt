/**
  @page CRC_PolynomialUpdate CRC operation with Polynomial update (HAL/LL mixed usage example)
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    CRC/CRC_PolynomialUpdate/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of CRC operation including user updates on generating polynomial.
  ******************************************************************************
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  @endverbatim

@par Example Description 

This example provides a description of how to use the CRC peripheral
through the STM32L4xx CRC HAL and LL API. The LL API is used for performance
improvement.

The CRC calculation unit computes the 8-bit long CRC code
of a given buffer of 32-bit data words, based on a user-defined generating
polynomial. In this example, the polynomial is first set manually to 0x9B
that is X^8 + X^7 + X^4 + X^3 + X + 1; Then, in a second step, generating
polynomial value and length are updated and set to 0x1021, that is
X^16 + X^12 + X^5 + 1), for new CRC calculation. These updates are performed
using CRC LL API.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK).

The CRC peripheral configuration is ensured by HAL_CRC_Init() function.
The latter is calling HAL_CRC_MspInit() function which core is implementing
the configuration of the needed CRC resources according to the used hardware (CLOCK). 
You can update HAL_CRC_Init() input parameters to change the CRC configuration.

For each computation, calculated CRC code is stored in uwCRCValue variable.
Once calculated, the CRC value (uwCRCValue) is compared to the CRC expected value (uwExpectedCRCValue1 and uwExpectedCRCValue2).

STM32 board LED is used to monitor the example status:
  - LED2 is ON when correct CRC values are calculated
  - LED2 is slowly blinking (1 sec. period) when there is an error in initialization or if an incorrect CRC value is calculated.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents 
  
  - CRC/CRC_PolynomialUpdate/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - CRC/CRC_PolynomialUpdate/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - CRC/CRC_PolynomialUpdate/Inc/main.h                  Header for main.c module
  - CRC/CRC_PolynomialUpdate/Src/stm32l4xx_it.c          Interrupt handlers
  - CRC/CRC_PolynomialUpdate/Src/main.c                  Main program
  - CRC/CRC_PolynomialUpdate/Src/stm32l4xx_hal_msp.c     HAL MSP module 
  - CRC/CRC_PolynomialUpdate/Src/system_stm32l4xx.c      STM32L4xx system source file

     
@par Hardware and Software environment

  - This example runs on STM32L476xx devices.
  - This example has been tested with NUCLEO-L476RG Rev C board and can be
    easily tailored to any other supported device and development board.

@par How to use it ? 

In order to make the program work, you must do the following:
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 