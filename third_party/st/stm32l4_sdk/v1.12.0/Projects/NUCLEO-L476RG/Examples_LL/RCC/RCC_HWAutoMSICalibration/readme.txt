/**
  @page RCC_HWAutoMSICalibration RCC example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/RCC/RCC_HWAutoMSICalibration/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the RCC example.
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

This example demonstrates and explains how to use the MSI clock source hardware
auto-calibration to get an accurate MSI clock using LSE (PLL mode). 

In the associated software, after start-up, SYSCLK is configured to the max 
frequency using the PLL with MSI as clock source.

When a 32.768 kHz external oscillator is present in the application,it is possible to configure 
the MSI in a PLL-mode by setting the MSIPLLEN bit. 
When configured in PLL-mode, the MSI automatically calibrates itself thanks to the LSE. 
This mode is available for all MSI frequency ranges. At 48 MHz, the MSI in PLL-mode can 
be used for the USB OTG FS device, saving the need of an external high-speed crystal.

The program waits until User push-button is pressed to begin the auto calibration 
procedure (fast blink of the LED2):
 - Enable and wait for LSE is ready.
 - Enable PLL-Mode feature
 - LED2 is turn on to indicate end of the HW calibration procedure.

@note User can connect on oscilloscope to MCO pin (PA.08) to check MSI frequency before and after
calibration procedure.

@note User can enable USE_TIMEOUT switch to detect a problem with LSE activation (LED2 is blinking 
every 1 sec in case of issue)

@par Directory contents 

  - RCC/RCC_HWAutoMSICalibration/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - RCC/RCC_HWAutoMSICalibration/Inc/main.h                  Header for main.c module
  - RCC/RCC_HWAutoMSICalibration/Inc/stm32_assert.h          Template file to include assert_failed function
  - RCC/RCC_HWAutoMSICalibration/Src/stm32l4xx_it.c          Interrupt handlers
  - RCC/RCC_HWAutoMSICalibration/Src/main.c                  Main program
  - RCC/RCC_HWAutoMSICalibration/Src/system_stm32l4xx.c      STM32L4xx system source file


@par Hardware and Software environment

  - This example runs on STM32L476xx devices.
    
  - This example has been tested with NUCLEO-L476RG Rev C board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-L476RG Rev C Set-up
    - External LSE Oscillator is mandatory to be able to run this example.
    - Connect the MCO pin to an oscilloscope to monitor the different waveforms:
      - PA.08: connected to pin 23 of CN10 connector  


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
