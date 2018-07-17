/**
  @page FatFs_RAMDisk   FatFs with RAM disk drive application

  @verbatim
  ******************************************************************************
  * @file    readme.txt
  * @author  MCD Application Team
  * @brief   Description of the FatFs with RAM disk drive application
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

This application provides a description on how to use STM32Cube firmware with FatFs
middleware component as a generic FAT file system module. The objective is to
develop an application that exploits the FatFs features to configure a RAM disk
(SRAM) drive.

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system clock
(SYSCLK) to run at 80 MHz.

The application is based on writing and reading back a text file from a drive,
and it's performed using FatFs APIs to access the FAT volume as described
in the following steps:

 - Link the SRAM disk I/O driver;
 - Register the file system object (mount) to the FatFs module for the SRAM drive;
 - Create a FAT file system (format) on the SRAM drive;
 - Create and Open new text file object with write access;
 - Write data to the text file;
 - Close the open text file;
 - Open text file object with read access;
 - Read back data from the text file;
 - Close the open text file;
 - Check on read data from text file;
 - Unlink the SRAM disk I/O driver.

Notice that the application manages possible errors that might occur during the
access to FAT volume, when using FatFs APIs.

It is possible to fine tune needed FatFs features by modifying defines values
in FatFs configuration file �ffconf.h� available under the project includes
directory, in a way to fit the application requirements.

STM32 board's LEDs can be used to monitor the application status:
  - LED1 is ON when the application runs successfully.
  - LED3 is ON when any error occurs.

@par Directory contents

  - FatFs/FatFs_RAMDisk/Inc/stm32l4xx_hal_conf.h    HAL configuration file
  - FatFs/FatFs_RAMDisk/Inc/stm32l4xx_it.h          Interrupt handlers header file
  - FatFs/FatFs_RAMDisk/Inc/main.h                  Header for main.c module
  - FatFs/FatFs_RAMDisk/Inc/ffconf.h                FAT file system module configuration file
  - FatFs/FatFs_RAMDisk/Inc/sram_diskio.h           sram FatFs diskio drvier header file
  - FatFs/FatFs_RAMDisk/Src/stm32l4xx_it.c          Interrupt handlers
  - FatFs/FatFs_RAMDisk/Src/main.c                  Main program
  - FatFs/FatFs_RAMDisk/Src/sram_diskio.c           sram FatFs diskio driver implementation
  - FatFs/FatFs_RAMDisk/Src/system_stm32l4xx.c      STM32L4xx system source file

@par Hardware and Software environment
  - This application runs on STM32L4xx devices.


  - This application has been tested with STM32L476G-EVAL board and can be
    easily tailored to any other supported device and development board.

  - STM32L476G-EVAL Set-up
    - Make sure that LCD Glass is in position IO.

@par How to use it ?

In order to make the program work, you must do the following:
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the application

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
