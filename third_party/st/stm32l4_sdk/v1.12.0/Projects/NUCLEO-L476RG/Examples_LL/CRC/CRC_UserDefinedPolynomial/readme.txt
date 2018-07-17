/**
  @page CRC_UserDefinedPolynomial CRC : 8-bit CRC calculation using user-defined polynomial value
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/CRC/CRC_UserDefinedPolynomial/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the CRC_UserDefinedPolynomial example.
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

This example shows how to configure and use CRC calculation unit to get a 8-bit long CRC of a given data buffer,
based on a user-defined generating polynomial. The peripheral initialization is done using LL unitary service functions
for optimization purpose (performance and size).

CRC Peripheral is configured to work with a user defined polynomial value (8-bit long value).
In this example, the polynomial is set manually to 0x9B that is X^8 + X^7 + X^4 + X^3 + X + 1.
Generated CRC value is then 8-bit long.

Example execution:
After startup from reset and system configuration, CRC configuration is performed (use of user-defined Polynomial value).
CRC code of a given data buffer is computed. 
Data buffer length has been chosen as not an exact nb of u32 (32-bit words), in order to illustrate 
use of offered API for feeding the calculator (u32, u16 or u8 inputs).
The calculated CRC code is stored in ubCRCValue variable.
Once calculated, CRC value (ubCRCValue) is compared to the CRC expected value (ubExpectedCRCValue),
and if both are equal, LED is turned On. 
In case of errors, LED is blinking (1sec period).

@par Directory contents 

  - CRC/CRC_UserDefinedPolynomial/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - CRC/CRC_UserDefinedPolynomial/Inc/main.h                  Header for main.c module
  - CRC/CRC_UserDefinedPolynomial/Inc/stm32_assert.h          Template file to include assert_failed function
  - CRC/CRC_UserDefinedPolynomial/Src/stm32l4xx_it.c          Interrupt handlers
  - CRC/CRC_UserDefinedPolynomial/Src/main.c                  Main program
  - CRC/CRC_UserDefinedPolynomial/Src/system_stm32l4xx.c      STM32L4xx system source file


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
 