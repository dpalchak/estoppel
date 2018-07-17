/**
  @page CRYP_AESModes_Suspension  Suspension and Resumption of AES ECB, CBC and CTR algorithms.
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    CRYP/CRYP_AESModes_Suspension/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the suspension and resumption of ECB, CBC and CTR processing  
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

This example provides a short description of how to use the CRYP AES peripheral to
suspend then resume the AES ECB, CBC and CTR processing of a message in order to
carry out the encryption or decryption of a higher priority message. 


For ECB algorithm,
  AES 128 ECB encryption of a low priority message (8-bit data type) is interrupted by the
  AES 256 ECB encryption of a high priority message (32-bit data type).
For CBC algorithm, 
  AES 256 CBC encryption of a low priority message (32-bit data type) is interrupted by the
  AES 128 CBC encryption of a high priority message (8-bit data type).
For CTR algorithm,  
  AES 128 CTR encryption of a low priority message (8-bit data type) is interrupted by the
  AES 256 CTR decryption of a high priority message (32-bit data type).
  
Once the high priority message processing is over, the low priority message
encryption is resumed.  
 
Note that the AES HW IP allows to suspend a specific chaining algorithm to
carry out another chaining algorithm processing (e.g. a CTR processing can
interrupt a CBC processing, which can be resumed once the CTR encryption or
decryption is over).




The example unrolls as follows: 
- AES ECB low-priority message encryption started, suspended by high priority message ECB encryption
  then resumed to end the low priority message processing
- AES CBC low-priority message encryption started, suspended by high priority message CBC encryption
  then resumed to end the low priority message processing
- AES CTR low-priority message encryption started, suspended by high priority message CTR decryption
  then resumed to end the low priority message processing  



Low and high-priority blocks AES outputs are compared with expected outputs.
When resorting to IAR Embedded Workbench IDE, AES algorithms processing status
are displayed on debugger Terminal I/O as follows: View --> Terminal I/O.
When resorting to MDK-ARM KEIL IDE, AES algorithms processing status 
are displayed on debugger as follows:  View --> Serial Viewer --> Debug (printf) Viewer.
When resorting to ATOLLIC TrueSTUDIO IDE:  debug --> view--> others-->SWV console.
When resorting to AC6 SW4STM32 IDE:
 In Debug configuration window\ Startup, in addition to "monitor reset halt" add the command "monitor arm semihosting enable"
 Command Code is displayed on debugger as follows: Window--> Show View--> Console.

When all ciphering and deciphering operations are successful, LED1 is turned on.
In case of ciphering or deciphering issue, LED3 is turned on. 
 

@par Directory contents 

  - CRYP/CRYP_AESModes_Suspension/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - CRYP/CRYP_AESModes_Suspension/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - CRYP/CRYP_AESModes_Suspension/Inc/main.h                  Header for main.c module  
  - CRYP/CRYP_AESModes_Suspension/Src/stm32l4xx_it.c          Interrupt handlers
  - CRYP/CRYP_AESModes_Suspension/Src/main.c                  Main program
  - CRYP/CRYP_AESModes_Suspension/Src/stm32l4xx_hal_msp.c     HAL MSP module
  - CRYP/CRYP_AESModes_Suspension/Src/system_stm32l4xx.c      STM32L4xx system source file


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
