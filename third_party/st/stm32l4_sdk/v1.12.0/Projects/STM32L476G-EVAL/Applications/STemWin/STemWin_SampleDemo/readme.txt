/**
  @page STemWin_SampleDemo Readme file
 
  @verbatim
  ******************************************************************************
  * @file    STemWin_SampleDemo/readme.txt 
  * @author  MCD Application Team
  * @brief
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

This application shows how to implement a sample demonstration example allowing 
to show some of the STemWin Library capabilities.

The list of modules to be used is configured into the file Demo/GUIDEMO.h

At the first run, after power OFF/ON, a touch screen calibration is needed: in
order to do this, user is just requested to follow the displayed instructions.
Then all the demo modules are run sequentially. Throughout the demonstration, a
control frame window is displayed at the bottom right of the touch screen: it
includes a progress bar and two control buttons (Next + Halt) allowing to skip
or pause the currently running module.

LED 1 is continuously toggling to indicate that the Demo runs properly.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@note Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select the RTC clock source; in this 
      case the Backup domain will be reset in order to modify the RTC Clock source, as consequence RTC  
      registers (including the backup registers) and RCC_BDCR register are set to their reset values.
	   
@par Directory contents 

  - STemWin/STemWin_SampleDemo/Inc/GUIConf.h                        Header for GUIConf_stm32l476g_eval.c
  - STemWin/STemWin_SampleDemo/Inc/LCDConf_stm3240g_eval.h          Header for LCDConf_stm32l476g_eval.c
  - STemWin/STemWin_SampleDemo/Inc/rtc.h                            Header for rtc.c
  - STemWin/STemWin_SampleDemo/Inc/calibration.h                    Header for calibration.c
  - STemWin/STemWin_SampleDemo/Inc/main.h                           Main program header file
  - STemWin/STemWin_SampleDemo/Inc/stm32l4xx_hal_conf.h             Library Configuration file
  - STemWin/STemWin_SampleDemo/Inc/stm32l4xx_it.h                   Interrupt handlers header file
  - STemWin/STemWin_SampleDemo/Src/rtc.c                            Main file to configure RTC clock
  - STemWin/STemWin_SampleDemo/Src/calibration.c                    Main file to calibrate TS
  - STemWin/STemWin_SampleDemo/Src/GUIConf_stm32l476g_eval.c        Display controller initialization file
  - STemWin/STemWin_SampleDemo/Src/LCDConf_stm32l476g_eval.c        Configuration file for the GUI library
  - STemWin/STemWin_SampleDemo/Src/main.c                           Main program file
  - STemWin/STemWin_SampleDemo/Src/stm32l4xx_it.c                   STM32L4xx Interrupt handlers
  - STemWin/STemWin_SampleDemo/Src/system_stm32l4xx.c               STM32L4xx system file
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO_*.c                     All the sources files provided for SEGGER DEMO
  - STemWin/STemWin_SampleDemo/Demo/GUIDEMO.h                       DEMO modules configuration file

@par Hardware and Software environment

  - This example runs on STM32L476xx devices.
    
  - This example has been tested with STM32L476G-EVAL board and can be
    easily tailored to any other supported device and development board.  
    
    @note Make sure that LCD Glass is in IO Position

@par How to use it ? 

In order to make the program work, you must do the following :
  - Open your preferred toolchain 
  - Rebuild all files
  - Open STM32 ST-Link Utility V3.6 or later, click on "External Loader" menu and select 
    "M29W128GL_STM32L476G-EVAL" via the "Add External Loader" submenu
  - Connect the STM32L476G-EVAL board to PC with USB cable through CN17
  - Program "STM32L476G_EVAL.hex" file with STM32 ST-Link Utility to program both internal Flash and external NOR memories
  - Run the example
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
