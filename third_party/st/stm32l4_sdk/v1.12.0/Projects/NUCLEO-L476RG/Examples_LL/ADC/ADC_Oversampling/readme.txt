/**
  @page ADC_Oversampling ADC example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/ADC/ADC_Oversampling/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the ADC_Oversampling example.
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

This example describes how to use a ADC peripheral with ADC oversampling. This example 
is based on the STM32L4xx ADC LL API. The peripheral initialization done using LL
unitary service functions for optimization purpose (performance and size).

Description of ADC oversampling:
Multiple successive ADC conversions and average computation
are performed automatically, by ADC hardware, and therefore
off-load the CPU to do the equivalent task.
This feature can be used for the functions: averaging,
data rate reduction, SNR improvement, basic filtering.
This example uses 3 configurations of oversampling,
for comparison of final data to evaluate oversampling benefits.


Example configuration:
ADC is configured to convert a single channel, in single conversion mode,
from SW trigger.
ADC oversampling feature is used with 3 settings:
 - ADC oversampling enabled: ratio 16, bits right shift 4.
 - ADC oversampling enabled: ratio 16, no bits right shift.
 - ADC oversampling disabled.

Example execution:
At each press on push button, with the 3 oversampling setting:
the ADC converts the selected channel, software polls for conversion completion
and stores conversion data into a variable.
When all ADC conversions are completed, LED2 is turned on.
The 3 ADC conversion data corresponding to each of the oversampling setting
are evaluated (refer to loop "while (1)" of main program):
 - data validity check and SW calculation of equivalent data
   on 12 bits with floating point.
 - user can evaluate the expected results of oversampling:
   ADC conversion data with oversampling enabled has less variation
   than with oversampling disabled, calculation performed by ADC HW
   is equivalent to calculation performed by SW.

For debug: variables to monitor with debugger watch window:
 - "uhADCxConvertedData_OVS_ratio16_shift4": ADC group regular conversion data, oversampling ratio 16 and shift 4 (data scale: 12 bits)
 - "uhADCxConvertedData_OVS_ratio16_shift0": ADC group regular conversion data, oversampling ratio 16 and shift 4 (data scale: 16 bits)
 - "uhADCxConvertedData_OVS_disabled": ADC group regular conversion data, oversampling disabled (data scale corresponds to ADC resolution: 12 bits)
 - "fConvertedData_OVS_EquivalentValue12bits": Calculation of oversampling raw data (from variable "uhADCxConvertedData_OVS_ratio16_shift0") to the equivalent data on 12 bits with floating point.

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


@par Directory contents 

  - ADC/ADC_Oversampling/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - ADC/ADC_Oversampling/Inc/main.h                  Header for main.c module
  - ADC/ADC_Oversampling/Inc/stm32_assert.h          Template file to include assert_failed function
  - ADC/ADC_Oversampling/Src/stm32l4xx_it.c          Interrupt handlers
  - ADC/ADC_Oversampling/Src/main.c                  Main program
  - ADC/ADC_Oversampling/Src/system_stm32l4xx.c      STM32L4xx system source file


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
