/**
  @page I2C_OneBoard_Communication_IT I2C example (IT Mode)
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/I2C/I2C_OneBoard_Communication_IT/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the I2C_OneBoard_Communication_IT I2C example (IT Mode).
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

This example describes how to receive one data byte from an I2C Slave device to an 
I2C Master device. Both devices operate in Interrupt mode. The peripheral initialization
is done using LL unitary service functions for optimization purpose (performance and size).

This example guides you through the different configuration steps by mean of LL API
to configure GPIO and I2C peripherals using only one NUCLEO-L476RG Rev C.

I2C1 Peripheral is configured in Slave mode with EXTI (Clock 400Khz, Own address 7-bit enabled).
I2C3 Peripheral is configured in Master mode with EXTI (Clock 400Khz).
GPIO associated to User push-button is linked with EXTI. 

LED2 blinks quickly to wait for user-button press. 

Example execution:
Press the User push-button to initiate a read request by Master.
This action will generate an I2C start condition with the Slave address and a read bit condition.
When address Slave match code is received on I2C1, an ADDR interrupt occurs.
I2C1 IRQ Handler routine is then checking Address Match Code and direction Read.
This will allow Slave to enter in transmitter mode and then send a byte when TXIS interrupt occurs.
When byte is received on I2C3, an RXNE interrupt occurs.
When RXDR register is read, Master auto-generate a NACK and STOP condition
to inform the Slave that the transfer is finished.
The NACK condition generate a NACK interrupt in Slave side treated in the I2C1 IRQ handler routine by a clear of NACK flag.
The STOP condition generate a STOP interrupt in both side (Slave and Master). I2C1 and I2C3 IRQ handler routine are then
clearing the STOP flag in both side.

LED2 is On if data is well received.

In case of errors, LED2 is blinking.

@par Directory contents 

  - I2C/I2C_OneBoard_Communication_IT/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - I2C/I2C_OneBoard_Communication_IT/Inc/main.h                  Header for main.c module
  - I2C/I2C_OneBoard_Communication_IT/Inc/stm32_assert.h          Template file to include assert_failed function
  - I2C/I2C_OneBoard_Communication_IT/Src/stm32l4xx_it.c          Interrupt handlers
  - I2C/I2C_OneBoard_Communication_IT/Src/main.c                  Main program
  - I2C/I2C_OneBoard_Communication_IT/Src/system_stm32l4xx.c      STM32L4xx system source file

@par Hardware and Software environment

  - This example runs on STM32L476xx devices.
    
  - This example has been tested with NUCLEO-L476RG Rev C board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-L476RG Rev C Set-up
    - Connect GPIOs connected to I2C1 SCL/SDA (PB.8 and PB.9)
    to respectively SCL and SDA pins of I2C3 (PC.0 and PC.1).
      - I2C1_SCL  PB.8 (CN10, pin 3) : connected to I2C3_SCL PC.0 (CN7, pin 38) 
      - I2C1_SDA  PB.9 (CN10, pin 5) : connected to I2C3_SDA PC.1 (CN7, pin 36)

  - Launch the program. Press User push-button to initiate a read request by Master 
      then Slave send a byte.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
