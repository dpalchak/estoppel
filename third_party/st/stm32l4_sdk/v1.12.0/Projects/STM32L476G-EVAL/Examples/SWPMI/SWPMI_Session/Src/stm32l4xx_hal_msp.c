/**
  ******************************************************************************
  * @file    SWPMI_Session/Src/stm32l4xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   HAL MSP module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32L4xx_HAL_Examples
  * @{
  */

/** @addtogroup SWPMI_Session
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief SWPMI MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  *           - NVIC configuration
  * @param hswpmi: SWPMI handle pointer
  * @retval None
  */
void HAL_SWPMI_MspInit(SWPMI_HandleTypeDef *hswpmi)
{
  RCC_PeriphCLKInitTypeDef clkinit = {0};
  GPIO_InitTypeDef         gpioinit = {0};
  
  /*##-1- Configure the SWPMI1 clock source. The clock is derived from the SYSCLK #*/
  clkinit.PeriphClockSelection = RCC_PERIPHCLK_SWPMI1;
  clkinit.Swpmi1ClockSelection = RCC_SWPMI1CLKSOURCE_PCLK1;
  if(HAL_RCCEx_PeriphCLKConfig(&clkinit) != HAL_OK)
  {
    Error_Handler();
  }

  /*##-2- Enable peripherals and GPIO Clocks #################################*/
  /* Enable SWPMI clock */
  __HAL_RCC_SWPMI1_CLK_ENABLE();  
  /* Enable GPIOB clock */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*##-3- Configure peripheral GPIO ##########################################*/  
  /* SWPMI IO as alternate function  */
  gpioinit.Pin = GPIO_PIN_12;
  gpioinit.Mode = GPIO_MODE_AF_PP;
  gpioinit.Pull = GPIO_PULLDOWN;
  gpioinit.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  gpioinit.Alternate = GPIO_AF12_SWPMI1;
  HAL_GPIO_Init(GPIOB, &gpioinit);

  /*##-4- Configure the NVIC for SWPMI1 ######################################*/   
  /* NVIC for I2Cx */
  HAL_NVIC_SetPriority(SWPMI1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(SWPMI1_IRQn);

  HAL_Delay(1);
}

/**
  * @brief SWPMI MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO, DMA and NVIC configuration to their default state
  * @param hswpmi: SWPMI handle pointer
  * @retval None
  */
void HAL_SWPMI_MspDeInit(SWPMI_HandleTypeDef *hswpmi)
{
  /* Disable SWPMI clock */
  __HAL_RCC_SWPMI1_CLK_DISABLE();
  
  /* DeInit PB.12 SWPMI IO configuration */
  HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12);
  
  /* Disable GPIOB clock */
  __HAL_RCC_GPIOB_CLK_DISABLE();
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
