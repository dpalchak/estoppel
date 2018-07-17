/**
  @page TouchSensing 1 touchkey sensor example
 
  @verbatim
  ******************************************************************************
  * @file    TouchSensing\TouchSensing_1touchkey\readme.txt
  * @author  MCD Application Team
  * @brief   Description of the TouchSensing 1 touchkey sensor example.
  ******************************************************************************
  *
  * Copyright(c) 2017 STMicroelectronics International N.V. All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  @endverbatim

@par Application Description

This firmware is a basic application on how to use the STMTouch driver with 1 touchkey
sensor. The Environment Change System (ECS) and Detection Time Out (DTO) are also used.

Observed behaviour:

- The LED1 is ON when the TS1 sensor is touched.
- The LED4 blinks each time the ECS process is finished.
- The LED3 blinks continuously in case of error.

- On the LCD are also displayed:
  * The ECS state (ON/OFF).
  * The TS1 touchkey sensor state (RELEASE, DETECT, ...) and the delta value.

- The ECS is ON when no touch is detected (sensor is in the RELEASE state).
  The ECS is always present but its behaviour can be modified using some parameters in
  the tsl_conf.h file.

- You can experiment the DTO by touching a sensor for few seconds. The RELEASE state
  is automatically entered and a re-calibration is performed after the timeout is reached.
  This timeout is programmable by the TSLPRM_DTO parameter in the tsl_conf.h file.

@par Project Directory contents

    - TouchSensing_1touchkey\Inc\main.h                Header for main.c file
    - TouchSensing_1touchkey\Inc\stm32l4xx_hal_conf.h  HAL Library configuration file
    - TouchSensing_1touchkey\Inc\stm32l4xx_it.h        Header for stm32l4xx_it.c file
    - TouchSensing_1touchkey\Src\stmCriticalSection.h  Header for stmCriticalSection.c file
    - TouchSensing_1touchkey\Inc\tsl_conf.h            STMTouch driver configuration file
    - TouchSensing_1touchkey\Inc\tsl_user.h            Header for tsl_user.c file

    - TouchSensing_1touchkey\Src\main.c                Main program file
    - TouchSensing_1touchkey\Src\stm32l4xx_hal_msp.c   HAL MSP module file
    - TouchSensing_1touchkey\Src\stm32l4xx_it.c        Interrupt handlers file
    - TouchSensing_1touchkey\Src\stmCriticalSection.c  STMStudio lock/unlock mechanism file
    - TouchSensing_1touchkey\Src\system_stm32l4xx.c    System initialization file
    - TouchSensing_1touchkey\Src\tsl_user.c            Touchsensing channels/banks description file
    
@par Hardware and Software environment

  - This example runs on STM32L476xx devices.
    
  - This example has been tested with STM32L476G-EVAL board. It can be
    easily tailored to any other devices that embed the TSC peripheral and to
    any other development board supporting touchsensing sensor.

  - STM32L476G-EVAL Set-up :
    - Make sure that LCD Glass is in position IO.
    - Make sure that board is configured for touchsensing as 
      described in UM1855 "Evaluation board with STM32L476ZGT6 MCU" :
        - Resistors R33, R36, R38 and R39 removed
        - Solder bridges SB3, SB27 and SB30 opened (default)
        - Solder bridges SB2, SB4 and SB6 closed
    
@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
