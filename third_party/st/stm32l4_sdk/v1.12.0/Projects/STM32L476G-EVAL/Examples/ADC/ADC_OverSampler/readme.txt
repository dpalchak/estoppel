/**
  @page ADC_OverSampler ADC OverSampler example

  @verbatim
  ********************* COPYRIGHT(c) 2017 STMicroelectronics *******************
  * @file    ADC/ADC_OverSampler/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the ADC Oversampler example.
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

This example describes how to configure and use the ADC to convert an external
analog input combined with oversampling feature to increase resolution through the HAL API.
  
The ADC is configured to convert continuously ADC_CHANNEL_5 connected to PA.00
while the oversampler is enabled. 
Oversampling ratio is set to ADC_OVERSAMPLING_RATIO_128 so the maximum output result 
is 0xFFF * 128 = 0x7FF80 (19 bits).
Since the ADC_DR is a 16-bit long register, a 3-bit right shift is performed to 
keep only the 16 most significant bits.

User can vary the ADC_CHANNEL_5 voltage using the Eval Board potentiometer (RV3) connected to PA.00.

uwConvertedValue variable contains the 16-bit conversion result and 
uwInputVoltage yields the input voltage in mV. 

  
@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - ADC/ADC_OverSampler/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - ADC/ADC_OverSampler/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - ADC/ADC_OverSampler/Inc/main.h                  Header for main.c module  
  - ADC/ADC_OverSampler/Src/stm32l4xx_it.c          Interrupt handlers
  - ADC/ADC_OverSampler/Src/main.c                  Main program
  - ADC/ADC_OverSampler/Src/stm32l4xx_hal_msp.c     HAL MSP file 
  - ADC/ADC_OverSampler/Src/system_stm32l4xx.c      STM32L4xx system source file


@par Hardware and Software environment 

  - This example runs on STM32L476xx devices.

  - This example has been tested with STM32L476G-EVAL board and can be
    easily tailored to any other supported device and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
