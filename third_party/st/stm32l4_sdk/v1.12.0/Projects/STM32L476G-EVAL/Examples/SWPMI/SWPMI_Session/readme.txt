/**
  @page SWPMI_Session SWP session Example
  
  @verbatim
  ********************* COPYRIGHT(c) 2017 STMicroelectronics *******************
  * @file    SWPMI_Session/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the SWPMI example.
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

This example shows how to use the SWPMI interface and open a communication session with 
a SWP compliant card in no software buffer mode.

ST sample card, provided with STM32L476G-EVAL board, contains a SWP profile. 
This project implements the following sequences taking place between STM32 MCU and the card :
- At power on, the card is powered on, and an interface activation sequence is verified:
  the STM32 MCU waits for ACT_SYNC_ID, then sends ACT_POWER_MODE (low power) and wait for ACT_READY 
  from the card (see. ETSI TS 102 613)
- Once the interface activation is done, the STM32 MCU opens a session with SWP SHDLC Layer by 
  transmitting an Information Frame OPEN-PIPE
- When the session is opened, LED1 is toggling.
- LED1 remains ON upon error detection.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - SWPMI_Session/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - SWPMI_Session/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - SWPMI_Session/Inc/main.h                  Header for main.c module
  - SWPMI_Session/Src/stm32l4xx_it.c          Interrupt handlers
  - SWPMI_Session/Src/main.c                  Main program
  - SWPMI_Session/Src/stm32l4xx_hal_msp.c     HAL MSP module
  - SWPMI_Session/Src/system_stm32l4xx.c      STM32L4xx system source file


@par Hardware and Software environment  
  - This example runs on STM32L4xx devices.    
  - This example has been tested with STMicroelectronics STM32L476G-EVAL 
    evaluation board (embedding a STM32L476xx device) and 
    can be easily tailored to any other supported device and development board. 
      
  - STM32L476G-EVAL Set-up :
  - Use ST sample Smartcard provided with STM32L476G-EVAL HW board
    - Make sure that LCD Glass is in position IO.
    - Make sure that board is configured for SWP as described in MB1144 User Manual:
        - Resistor R39 present
        - Resistor R109 removed
        - Solder bridge SB3 and SB6 opened

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
