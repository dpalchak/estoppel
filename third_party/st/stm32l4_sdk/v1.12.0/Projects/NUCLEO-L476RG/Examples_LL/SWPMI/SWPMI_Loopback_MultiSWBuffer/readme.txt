/**
  @page SWPMI_Loopback_MultiSWBuffer SWPMI Multi buffer communication in loopback mode
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/SWPMI/SWPMI_Loopback_MultiSWBuffer/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the SWPMI Multi buffer communication in loopback mode example.
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

This example describes how to configure the SWPMI peripheral to start a communication
using DMA multibuffers in Loopback mode. The peripheral initialization is done using
LL unitary service functions for optimization purpose (performance and size).

In this example, after start-up, SYSCLK is configured to the max frequency using the PLL with
MSI as clock source.

Then, DMA configuration is done to enable TX/RX channels for SWPMI links and set the different buffers 
which will be used for the transfer. 
SWPMI is set in loopback mode with max bitrate of 2Mbit/s. 
Connection needed: 
 - None, because SWPMI is in loopback mode (mode for test purpose, connection is done internally).

LED2 blinks quickly to wait for user-button press. 
As soon as, user-button is pressed, SWPMI communication starts in DMA mode:
- DMA Circular mode enabled
- In SWPMI transfer buffer empty interrupt routine, when 3 1st frames have
  been transmitted, an update of the Multi buffer is done with 3 new frames
- In the same routine, when last frame has been sent, a frame payload size erase is done 
  to stop automatically SWPMI TX DMA.
- A the end of the transfer, a check is done between the reception buffer and the expected reception 
buffer:
   - LED2 ON: successful transmission
   - LED2 blinks with 1 sec period: an error occurred during transmission. 

@par Directory contents 

  - SWPMI/SWPMI_Loopback_MultiSWBuffer/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - SWPMI/SWPMI_Loopback_MultiSWBuffer/Inc/main.h                  Header for main.c module  
  - SWPMI/SWPMI_Loopback_MultiSWBuffer/Inc/stm32_assert.h          Template file to include assert_failed function
  - SWPMI/SWPMI_Loopback_MultiSWBuffer/Src/stm32l4xx_it.c          Interrupt handlers
  - SWPMI/SWPMI_Loopback_MultiSWBuffer/Src/main.c                  Main program
  - SWPMI/SWPMI_Loopback_MultiSWBuffer/Src/system_stm32l4xx.c      STM32L4xx system source file


@par Hardware and Software environment

  - This example runs on STM32L476xx devices.
    
  - This example has been tested with NUCLEO-L476RG Rev C board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
