/**
  @page DFSDM_AudioRecord  Description of the DFSDM audio record example
  
  @verbatim
  ********************* COPYRIGHT(c) 2017 STMicroelectronics *******************
  * @file    DFSDM/DFSDM_AudioRecord/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the DFSDM audio record example.
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

This example shows how to use the DFSDM HAL API to perform stereo audio recording.
For this audio record we will use two MP34DT01 digital microphones mounted on the board. 

MP34DT01 runs with a clock frequency from 1MHz to 3,25MHz.
This clock frequency has to be delivered by DFSDM. So first channel of DFSDM will be
configurated to enable output clock generation, to choose audio clock as output clock source,
and output clock divider will be set to generate output clock on MP34DT01 frequency clock range.
Audio clock will be configurated to 11.294MHz, so DFSDM output clock divider will be set to 4.

The digital audio outputs from the microphones are coded in PDM (Pulse Density Modulation) and 
interlaced to use the same data wire connected to PC0. When CLK = 0, the left channel is sent
on PC0 and when CLK = 1, the right channel is sent on PC0.

PC0 can be configurated as DFSDM_DATIN4 (DFSDM channel 4 external data input).
We will use DFSDM channel 4 to get left channel. DFSDM channel 4 will be configurated to take
inputs from external serial inputs and from pins of channel 4. DFSDM channel 4 will also be 
configurated to operate in SPI mode with rising edge and with internal clock.
We will use also DFSDM channel 3 to get right channel. DFSDM channel 3 will be configurated to take
inputs from external serial inputs and from pins of channel 4. DFSDM channel 3 will also be 
configurated to operate in SPI mode with falling edge and with internal clock.

DFSDM filter 0 will be used to perform left channels conversions.
We will use a SINC3 filter with oversampling at 64 and integrator oversampling at 1.
Oversampling is set to 64 in order to have audio sample frequency at 44.1KHz (11.294MHz/(4*64)).
Regular conversions in fast mode will be performed in DMA mode on DFSDM filter 0 in order to fill
a buffer containing left audio samples at 44.1KHz.
DFSDM filter 1 will be used to perform right channels conversions.
We will use a SINC3 filter with oversampling at 64 and integrator oversampling at 1.
Oversampling is set to 64 in order to have audio sample frequency at 44.1KHz (11.294MHz/(4*64)).
Regular conversions in fast mode and synchronized with DFSDM filter 0 regular conversions will be 
performed in DMA mode on DFSDM filter 1 in order to fill a buffer containing right audio samples at 44.1KHz.

Playback of the recorded data will be performed on headset using HAL_SAI and WM8994 audio codec.
A circular playback buffer will be filled as soon as recorded data are available. 
When half left and right buffers will be filled, we put first parts of left and right channels data 
on first half of playback buffer. 
When left and right buffers will be full filled, we put second parts of left and right channels data 
on second half of playback buffer.

@note Care must be taken when using HAL_Delay(), this function provides accurate
      delay (in milliseconds) based on variable incremented in SysTick ISR. This
      implies that if HAL_Delay() is called from a peripheral ISR process, then 
      the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents  

  - DFSDM/DFSDM_AudioRecord/Src/main.c                  Main program
  - DFSDM/DFSDM_AudioRecord/Src/system_stm32l4xx.c      STM32L4xx system source file
  - DFSDM/DFSDM_AudioRecord/Src/stm32l4xx_it.c          Interrupt handlers
  - DFSDM/DFSDM_AudioRecord/Inc/main.h                  Main program header file
  - DFSDM/DFSDM_AudioRecord/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - DFSDM/DFSDM_AudioRecord/Inc/stm32l4xx_it.h          Interrupt handlers header file


@par Hardware and Software environment

  - This example runs on STM32L476xx devices.
    
  - This example has been tested with STMicroelectronics STM32L476G-EVAL
    board and can be easily tailored to any other supported device
    and development board.      

  - STM32L476G-EVAL Set-up :
    - Make sure that LCD Glass is in position IO.
    - Make sure that JP14 is in position 2-3 (MCU).
    - Make sure that JP16 is in position 2-3 (VDD).
    - Make sure that SB34 and SB42 are in default open state.
    - Plug headset on CN20 connector.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example 

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
