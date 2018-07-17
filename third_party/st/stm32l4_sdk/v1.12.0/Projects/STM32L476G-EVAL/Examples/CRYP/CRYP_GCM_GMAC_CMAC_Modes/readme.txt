/**
  @page CRYP_GCM_GMAC_CMAC_Modes  Encrypt/decrypt data and compute authentication tag 
  with GCM, GMAC and CMAC AES algorithms.
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    CRYP/CRYP_GCM_GMAC_CMAC_Modes/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the CRYP GCM, GMAC and CMAC Algorithms
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

This example describes how to encrypt, decrypt data and compute authentication tag 
with GCM, GMAC and CMAC AES algorithms.

This example provides a short description of how to use the CRYP AES peripheral to
- encrypt and decrypt data as well as to compute an authentication tag using 
  AES-based GCM algorithm with a 128-bit long key,
- compute an authentication tag using AES-based GMAC algorithm with a 256-bit long key,
- compute an authentication tag using AES-based CMAC algorithm with a 256-bit long key.

For GCM algorithm,
  Ciphering/Tag computation with a 128-bit long key is used in interrupt mode with data type set to 32-bit (no swapping).
  Deciphering/Tag computation is used in polling mode.
  The ciphering output is used as deciphering input. 
For GMAC algorithm,
  Tag computation with a 256-bit long key is used in DMA mode with data type set to 1-bit (bit swapping).
For CMAC algorithm,
  Tag computation with a 256-bit long key is used in polling mode with data type set to 32-bit (no swapping).  


The example unrolls as follows: 
- GCM encryption and tag computation (Header + Plain Data --> Encrypted Data + Authentication tag)
- GCM decryption and tag computation (Header + Encrypted Data --> Decrypted Data + Authentication tag)
- GMAC tag computation (Header --> Authentication tag)
- CMAC tag computation (Header --> Authentication tag)



When resorting to IAR Embedded Workbench IDE, plain data and headers, encrypted and decrypted data, authentication
tags are displayed on debugger Terminal I/O as follows: View --> Terminal I/O.
When resorting to MDK-ARM KEIL IDE, plain data and headers, encrypted an decrypted data, authentication
tags are displayed on debugger as follows:  View --> Serial Viewer --> Debug (printf) Viewer.
When resorting to ATOLLIC TrueSTUDIO IDE:  debug --> view--> others-->SWV console.
When resorting to AC6 SW4STM32 IDE:
 In Debug configuration window\ Startup, in addition to "monitor reset halt" add the command "monitor arm semihosting enable"
 Command Code is displayed on debugger as follows: Window--> Show View--> Console. 
 
When all ciphering and deciphering operations are successful, LED1 is turned on.
In case of ciphering or deciphering issue, LED3 is turned on. 


@par Directory contents 

  - CRYP/CRYP_GCM_GMAC_CMAC_Modes/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - CRYP/CRYP_GCM_GMAC_CMAC_Modes/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - CRYP/CRYP_GCM_GMAC_CMAC_Modes/Inc/main.h                  Header for main.c module  
  - CRYP/CRYP_GCM_GMAC_CMAC_Modes/Src/stm32l4xx_it.c          Interrupt handlers
  - CRYP/CRYP_GCM_GMAC_CMAC_Modes/Src/main.c                  Main program
  - CRYP/CRYP_GCM_GMAC_CMAC_Modes/Src/stm32l4xx_hal_msp.c     HAL MSP module
  - CRYP/CRYP_GCM_GMAC_CMAC_Modes/Src/system_stm32l4xx.c      STM32L4xx system source file


@par Hardware and Software environment

   - This example runs on STM32L486xx devices.
  
    - This example has been tested with a STM32L486ZG embedded on an 
    STM32L476G-EVAL board and can be easily tailored to any other supported 
    device and development board.


@par How to use it ? 

In order to make the program work, you must do the following:
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
