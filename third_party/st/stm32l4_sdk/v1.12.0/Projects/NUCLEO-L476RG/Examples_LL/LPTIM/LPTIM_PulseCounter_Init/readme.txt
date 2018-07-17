/**
  @page LPTIM_PulseCounter_Init LPTIM example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/LPTIM/LPTIM_PulseCounter_Init/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the LPTIM_PulseCounter_Init example.
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

This example describes how to use the LPTIM in counter mode to generate a PWM
output signal and update PWM duty cycle. This example is based on the STM32L4xx
LPTIM LL API. The peripheral initialization is done using LL initialization function
to demonstrate LL init usage.

To reduce power consumption, MCU enters stop mode after starting counting. Each
time the counter reaches the maximum value (Period/Autoreload), an interruption
is generated, the MCU is woke up from stop mode and LED2 toggles the last state.
  
In this example Period value is set to 1000, so each time the counter counts
(1000 + 1) rising edges on LPTIM1_IN1 pin, an interrupt is generated and LED2
toggles. If the external function generator is set to provide a square waveform at 1Khz,
the led will toggle each second.

In this example the internal clock provided to the LPTIM1 is LSI (32 kHz),
so the external input is sampled with LSI clock. In order not to miss any event,
the frequency of the changes on the external Input1 signal should never exceed the
frequency of the internal clock provided to the LPTIM1 (LSI for the
present example).

@par Directory contents 

  - LPTIM/LPTIM_PulseCounter_Init/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - LPTIM/LPTIM_PulseCounter_Init/Inc/main.h                  Header for main.c module
  - LPTIM/LPTIM_PulseCounter_Init/Inc/stm32_assert.h          Template file to include assert_failed function
  - LPTIM/LPTIM_PulseCounter_Init/Src/stm32l4xx_it.c          Interrupt handlers
  - LPTIM/LPTIM_PulseCounter_Init/Src/main.c                  Main program
  - LPTIM/LPTIM_PulseCounter_Init/Src/system_stm32l4xx.c      STM32L4xx system source file


@par Hardware and Software environment

  - This example runs on STM32L476xx devices.
    
  - This example has been tested with NUCLEO-L476RG Rev C board and can be
    easily tailored to any other supported device and development board.
    
  - Connect a square waveform generator to PB.05 (pin 29 in CN10 connector).
    If the frequency of the signal is 1 kHz, LED2 toggles every second.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
