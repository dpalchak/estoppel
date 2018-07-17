/**
  ******************************************************************************
  * @file    k_bsp.c
  * @author  MCD Application Team   
  * @brief   This file provides the kernel bsp functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
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
  */

/* Includes ------------------------------------------------------------------*/
#include "k_bsp.h"
#include "k_calibration.h"
#include "GUI.h"
#include "DIALOG.h"
#include "k_temperature.h"

/** @addtogroup CORE
  * @{
  */

/** @defgroup KERNEL_BSP
  * @brief Kernel BSP routines
  * @{
  */


/* External variables --------------------------------------------------------*/
uint32_t GPIOModeSaved[8];
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes LEDs, touch screen, CRC and SRAM.
  * @param  None 
  * @retval None
  */
void k_BspInit(void)
{
  /* Configure LED1 */
  BSP_LED_Init(LED1);
  
  /* Configure IO expanders */
  BSP_IO_Init();
  
  /* Initialize the SRAM */
  BSP_SRAM_Init();
  
  /* Initialize the NOR */
  BSP_NOR_Init();

  /* Initialize the Touch screen */
  BSP_TS_Init(320, 240);
  
  /* Enable CRC to Unlock GUI */
  __HAL_RCC_CRC_CLK_ENABLE();
}

/**
  * @brief  Initializes BSP Audio
  * @param  None 
  * @retval None
  */
void k_BspAudioInit(void)
{
  BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_BOTH, AUDIO_DEFAULT_VOLUME, SAI_AUDIO_FREQUENCY_44K);
  BSP_AUDIO_OUT_SetAudioFrameSlot(CODEC_AUDIOFRAME_SLOT_02);
}

/**
  * @brief  Initializes BSP IDD
  * @param  None 
  * @retval None
  */
void k_BspIDDInit(void)
{
  BSP_IDD_Init();
}

/**
  * @brief  Disable GPIOs and IPs CLK.
  * @param  None 
  * @retval None
  */
void k_BspDeInitForLowPower(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  *GPIOModeSaved    =GPIOA->MODER;
  *(GPIOModeSaved+1)=GPIOB->MODER;
  *(GPIOModeSaved+2)=GPIOC->MODER;
  *(GPIOModeSaved+3)=GPIOD->MODER;
  *(GPIOModeSaved+4)=GPIOE->MODER;
  *(GPIOModeSaved+5)=GPIOF->MODER;
  *(GPIOModeSaved+6)=GPIOG->MODER;
  *(GPIOModeSaved+7)=GPIOH->MODER;

  k_TemperatureDeInit();
  
  /* Set all GPIO in analog state to reduce power consumption,
      except GPIOC to keep user button interrupt enabled */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();    

  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Pin = GPIO_PIN_All;
  
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);  
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);  
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);  
  
  GPIO_InitStruct.Pin = GPIO_PIN_All;
  GPIO_InitStruct.Pin &= ~(GPIO_PIN_5);
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);   
  
  GPIO_InitStruct.Pin = GPIO_PIN_All;
  GPIO_InitStruct.Pin &= ~(GPIO_PIN_10);
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
  
  __HAL_RCC_GPIOA_CLK_DISABLE();
  __HAL_RCC_GPIOB_CLK_DISABLE();
  __HAL_RCC_GPIOD_CLK_DISABLE();
  __HAL_RCC_GPIOE_CLK_DISABLE();
  __HAL_RCC_GPIOG_CLK_DISABLE();
  __HAL_RCC_GPIOH_CLK_DISABLE();

  /* Module Audio Player & Audio Recorder */
  __HAL_RCC_SAI1_CLK_DISABLE();
  __HAL_RCC_DFSDM1_CLK_DISABLE();

  __HAL_RCC_CRC_CLK_DISABLE();
  __HAL_RCC_SDMMC1_CLK_DISABLE();
  __HAL_RCC_DMA1_CLK_DISABLE();
  __HAL_RCC_DMA2_CLK_DISABLE();
  __HAL_RCC_SYSCFG_CLK_DISABLE();

  /* Module USB */
  __HAL_RCC_USB_OTG_FS_FORCE_RESET();
  __HAL_RCC_USB_OTG_FS_RELEASE_RESET();
  __HAL_RCC_USB_OTG_FS_CLK_DISABLE();

  __HAL_RCC_I2C1_CLK_DISABLE();
  __HAL_RCC_FMC_CLK_DISABLE();
  
  /* Add some delay */
  HAL_Delay(500);
}

/**
  * @brief  Enable GPIOs and IPs CLK.
  * @param  None 
  * @retval None
  */
void k_BspInitAfterLowPower(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_FMC_CLK_ENABLE();
  __HAL_RCC_I2C1_CLK_ENABLE();
  __HAL_RCC_SAI1_CLK_ENABLE();
  __HAL_RCC_DFSDM1_CLK_ENABLE();
  __HAL_RCC_CRC_CLK_ENABLE();
  __HAL_RCC_SDMMC1_CLK_ENABLE();
  __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();


  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();    
  
  GPIOA->MODER = *GPIOModeSaved;
  GPIOB->MODER = *(GPIOModeSaved+1);
  GPIOC->MODER = *(GPIOModeSaved+2);
  GPIOD->MODER = *(GPIOModeSaved+3);
  GPIOE->MODER = *(GPIOModeSaved+4);
  GPIOF->MODER = *(GPIOModeSaved+5);
  GPIOG->MODER = *(GPIOModeSaved+6);
  GPIOH->MODER = *(GPIOModeSaved+7);
  
  k_TemperatureInit();
}

/**
  * @brief  Read the coordinate of the point touched and assign their
  *         value to the variables u32_TSXCoordinate and u32_TSYCoordinate
  * @param  None
  * @retval None
  */
void k_TouchUpdate(void)
{
  GUI_PID_STATE TS_State;
  static TS_StateTypeDef prev_state;
  __IO TS_StateTypeDef  ts;
  uint16_t xDiff, yDiff;  
  
  BSP_TS_GetState((TS_StateTypeDef *)&ts);
  
  TS_State.Pressed = ts.TouchDetected;

  xDiff = (prev_state.x > ts.x) ? (prev_state.x - ts.x) : (ts.x - prev_state.x);
  yDiff = (prev_state.y > ts.y) ? (prev_state.y - ts.y) : (ts.y - prev_state.y);
  
  if((prev_state.TouchDetected != ts.TouchDetected )||
     (xDiff > 3 )||
       (yDiff > 3))
  {
    prev_state.TouchDetected = ts.TouchDetected;
    
    if((ts.x != 0) &&  (ts.y != 0)) 
    {
      prev_state.x = ts.x;
      prev_state.y = ts.y;
    }
      
    if(k_CalibrationIsDone())
    {
      TS_State.Layer = 0;
      TS_State.x = k_CalibrationGetX (prev_state.x);
      TS_State.y = k_CalibrationGetY (prev_state.y);
    }
    else
    {
      TS_State.Layer = 0;
      TS_State.x = prev_state.x;
      TS_State.y = prev_state.y;
    }
    
    GUI_TOUCH_StoreStateEx(&TS_State);
  }
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
