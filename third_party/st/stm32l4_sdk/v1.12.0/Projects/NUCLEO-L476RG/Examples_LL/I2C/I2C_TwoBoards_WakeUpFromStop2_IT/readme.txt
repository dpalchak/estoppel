/**
  @page I2C_TwoBoards_WakeUpFromStop2_IT I2C example (IT Mode)
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/I2C/I2C_TwoBoards_WakeUpFromStop2_IT/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the I2C_TwoBoards_WakeUpFromStop2_IT I2C example (IT Mode).
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
  
This example describes how to receive data byte from an I2C Slave device in Stop2 mode
using Interrupt mode to an I2C Master device Interrupt mode. The peripheral initialization
is done using LL unitary service functions for optimization purpose (performance and size).

This example guides you through the different configuration steps by mean of LL API 
to configure GPIO and I2C peripherals using two NUCLEO-L476RG Rev C.

Boards: NUCLEO-L476RG Rev C (embeds a STM32L476RGT6 device)
SCL Pin: PC.0 (CN7, pin 38)
SDA Pin: PC.1 (CN7, pin 36)

   ______BOARD SLAVE_____                       _____BOARD MASTER_____
  |        ______________|                     |______________        |
  |       |I2C3          |                     |          I2C3|       |
  |       |              |                     |              |       |
  |       |          SCL |_____________________| SCL          |       |
  |       |              |                     |              |       |
  |       |              |                     |              |       |
  |       |          SDA |_____________________| SDA          |       |
  |       |______________|                     |______________|       |
  |         __           |                     |             __       |
  |        |__|          |                     |            |__|      |
  |        USER       GND|_____________________|GND         USER      |
  |___STM32L4xx_Nucleo___|                     |___STM32L4xx_Nucleo___|

The project is splitted in two parts the Master Board and the Slave Board
- Master Board
  I2C3 Peripheral is configured in Master mode with EXTI (Clock 100Khz).
And GPIO associated to User push-button is linked with EXTI. 
- Slave Board
  I2C3 Peripheral is configured in Slave mode with EXTI (Clock 100Khz,
  Own address 7-bit enabled, WakeUpFromStop).

The user can choose between Master and Slave through "#define SLAVE_BOARD"
in the "main.h" file:
- Comment "#define SLAVE_BOARD" to select Master board.
- Uncomment "#define SLAVE_BOARD" to select Slave board.

A first program launch, BOARD SLAVE is in Stop 2 mode and BOARD MASTER is waiting User action on User button.
LED2 blinks quickly on BOARD MASTER to wait for user-button press. 

Example execution:
Press the User push-button on BOARD MASTER to initiate a read request by Master.
This action will generate an I2C start condition with the Slave address and a read bit condition.
When address Slave match code is received on I2C3 of BOARD SLAVE, a wake up is initiate and an ADDR interrupt occurs.
I2C3 Slave IRQ Handler routine is then checking Address Match Code and direction Read.
This will allow Slave to enter in transmitter mode and then send a byte when TXIS interrupt occurs.
When byte is received on I2C3 of BOARD MASTER, an RXNE interrupt occurs.
When RXDR register is read, Master auto-generate a NACK and STOP condition
to inform the Slave that the transfer is finished.
The NACK condition generate a NACK interrupt in Slave side treated in the I2C3 Slave IRQ handler routine by a clear of NACK flag.
The STOP condition generate a STOP interrupt in both side (Slave and Master). Both I2C3 IRQ handler routine are then
clearing the STOP flag in both side.

LED2 is On if data is well received.

In case of errors, LED2 is blinking.

@par Directory contents 

  - I2C/I2C_TwoBoards_WakeUpFromStop2_IT/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - I2C/I2C_TwoBoards_WakeUpFromStop2_IT/Inc/main.h                  Header for main.c module
  - I2C/I2C_TwoBoards_WakeUpFromStop2_IT/Inc/stm32_assert.h          Template file to include assert_failed function
  - I2C/I2C_TwoBoards_WakeUpFromStop2_IT/Src/stm32l4xx_it.c          Interrupt handlers
  - I2C/I2C_TwoBoards_WakeUpFromStop2_IT/Src/main.c                  Main program
  - I2C/I2C_TwoBoards_WakeUpFromStop2_IT/Src/system_stm32l4xx.c      STM32L4xx system source file

@par Hardware and Software environment

  - This example runs on STM32L476xx devices.
    
  - This example has been tested with NUCLEO-L476RG Rev C board and can be
    easily tailored to any other supported device and development board.

  - NUCLEO-L476RG Rev C Set-up
    - Connect GPIOs connected to Board Slave I2C3 SCL/SDA (PC.0 and PC.1)
    to respectively Board Master SCL and SDA pins of I2C3 (PC.0 and PC.1).
      - I2C3_SCL  PC.0 (CN7, pin 38) : connected to I2C3_SCL PC.0 (CN7, pin 38) 
      - I2C3_SDA  PC.1 (CN7, pin 36) : connected to I2C3_SDA PC.1 (CN7, pin 36)
    - Connect Master board GND to Slave Board GND

  - Launch the program. Press User push-button to initiate a read request by Master 
      then Slave after wake up from Stop 2 mode send a byte.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory (The user can choose between Master 
   and Slave target through "#define SLAVE_BOARD" in the "main.h" file)
    o Comment "#define SLAVE_BOARD" and load the project in Master Board
    o Uncomment "#define SLAVE_BOARD" and load the project in Slave Board
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
