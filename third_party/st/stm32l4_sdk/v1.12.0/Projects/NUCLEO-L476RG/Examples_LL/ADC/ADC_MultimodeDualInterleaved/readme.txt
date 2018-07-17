/**
  @page ADC_MultimodeDualInterleaved ADC example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/ADC/ADC_MultimodeDualInterleaved/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the ADC_MultimodeDualInterleaved example.
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

This example describes how to use several ADC peripherals in multimode,
mode interleaved. This example is based on the STM32L4xx ADC LL
API. The peripheral initialization is done using LL unitary service functions
for optimization purpose (performance and size).

Description of multimode interleaved:
ADC master instance synchronizes and manages ADC slave instance.
Multimode interleaved combines ADC instances to convert
the same channel and increase the overall ADC conversion rate.
This example configures the ADC to perform conversions at the 
maximum ADC conversion rate possible (with a sampling time  
corresponding to ADC resolution 12 bits).


Example configuration:
ADC1 and ADC2 instances (master and slave) are configured in continuous conversion mode,
from SW trigger (in order to reach more simply the maximum conversion rate possible,
but trigger from timer is also possible).
Both ADC instances are configured to convert a single channel (1 channel from a GPIO),
this channel is common to ADC1 and ADC2.
DMA is configured to transfer conversion data in an array, in circular mode.
Note: One DMA channel is used (the one of ADC master) to transfer data from
      both ADC instances (master and slave).
      Usage of two DMA channels (one for ADC master, one for ADC slave) is also
      possible: this is the recommended configuration in case of high ADC
      conversions rates and applications using other DMA channels intensively.

Example execution:
From the first press on push button, the ADC converts the selected channel
continuously.
DMA transfers conversion data to the array, transfer complete interruption occurs.
Results array is updated indefinitely (DMA in circular mode).
LED2 is turned on when the DMA transfer is completed (results array full)
and turned off at next DMA half-transfer (result array first half updated).

Note: ADC is converting at high frequency, therefore LED2 is toggling at high frequency
      and will appear as dimming.
      Use an oscilloscope probe on LED2 to watch DMA transfers frequency.

Note: A file is provide with this example to detail the ADC conversions timings.
      Refer to file "ADC MultimodeDualInterleaved timing simulation STM32L4.xls".

For debug: variables to monitor with debugger watch window:
 - "aADCxADCyMultimodeDualConvertedData[ADC_CONVERTED_DATA_BUFFER_SIZE]": ADC multimode dual conversion data: ADC master and ADC slave conversion data are concatenated in a registers of 32 bits.
 - "aADCxMultimodeDualMasterConvertedData[ADC_CONVERTED_DATA_BUFFER_SIZE]": For the purpose of this example, dispatch multimode dual conversion data into array corresponding to ADC master conversion data.
 - "aADCyMultimodeDualSlaveConvertedData[ADC_CONVERTED_DATA_BUFFER_SIZE]": For the purpose of this example, dispatch multimode dual conversion data into array corresponding to ADC slave conversion data.
 - "ubDmaTransferStatus": status of DMA transfer of ADC group regular conversions

Connection needed:
None.
Note: Optionally, a voltage can be supplied to the analog input pin (cf pin below),
      between 0V and Vdda=3.3V, to perform a ADC conversion on a determined
      voltage level.
      Otherwise, this pin can be let floating (in this case ADC conversion data
      will be undetermined).

Other peripherals used:
  1 GPIO for push button
  1 GPIO for LED2
  1 GPIO for analog input: PA.04 (Arduino connector CN8 pin A2, Morpho connector CN7 pin 32)
  DMA


@par Directory contents 

  - ADC/ADC_MultimodeDualInterleaved/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - ADC/ADC_MultimodeDualInterleaved/Inc/main.h                  Header for main.c module
  - ADC/ADC_MultimodeDualInterleaved/Inc/stm32_assert.h          Template file to include assert_failed function
  - ADC/ADC_MultimodeDualInterleaved/Src/stm32l4xx_it.c          Interrupt handlers
  - ADC/ADC_MultimodeDualInterleaved/Src/main.c                  Main program
  - ADC/ADC_MultimodeDualInterleaved/Src/system_stm32l4xx.c      STM32L4xx system source file


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
