/**
  ******************************************************************************
  * @file    LPTIM/LPTIM_Timeout/Src/stm32l4xx_hal_msp.c
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

/** @defgroup HAL_MSP
  * @brief HAL MSP module.
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
* @brief  LPTIM MSP Init
* @param  hlptim : LPTIM handle
* @retval None
*/
void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef *hlptim)
{
  GPIO_InitTypeDef     GPIO_InitStruct;
    
  /* ## - 1 - Enable LPTIM clock ############################################ */
  __HAL_RCC_LPTIM2_CLK_ENABLE();
  
  /* ## - 2 - Force & Release the LPTIM Periheral Clock Reset ############### */  
  /* Force the LPTIM Periheral Clock Reset */
  __HAL_RCC_LPTIM2_FORCE_RESET();
  
  /* Release the LPTIM Periheral Clock Reset */  
  __HAL_RCC_LPTIM2_RELEASE_RESET();
  
  /* ## - 3 - Enable & Configure LPTIM Ultra Low Power Input ################# */
  /* Configure PD.11 (LPTIM2_ETR) in alternate function,
  Low speed push-pull mode and pull-up enabled.
  Note: In order to reduce power consumption: GPIO Speed is configured in
  LowSpeed */
  
  /* Enable GPIO PORT(s)*/
  LPTIMx_GPIO_PORT_ENABLE;
  
  /* Configure PD.11 */
  GPIO_InitStruct.Pin = GPIO_PIN_ETR;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PUPD_ETR;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF_LPTIMx_ETR;  
  HAL_GPIO_Init(LPTIMx_ETR_GPIO_PORT, &GPIO_InitStruct);

  /* Enable and set LPTIM Interrupt to the highest priority */
  HAL_NVIC_SetPriority(LPTIM2_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(LPTIM2_IRQn);  
  
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
