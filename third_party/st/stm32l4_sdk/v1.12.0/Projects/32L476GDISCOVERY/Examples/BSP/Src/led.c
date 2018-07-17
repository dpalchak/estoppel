/**
  ******************************************************************************
  * @file    BSP/Src/led.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the led display feature in the 
  *          STM32L476G-Discovery driver
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

/** @addtogroup BSP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Led demo
  * @param  None
  * @retval None
  */
void Led_demo(void)
{ 
  uint32_t index = 0; 

  /* -1- LEDs initialization =================================================*/ 
  /* Init LED4 and LED5 */
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED5);
  
  /* -2- LEDs turn on / turn off =============================================*/
  BSP_LCD_GLASS_ScrollSentence((uint8_t *)"      LED4 AND LED5 ON", 1, SCROLL_SPEED_HIGH);

  BSP_LED_On(LED4);
  BSP_LED_On(LED5);
  
  /* Keep the LEDs on for one seconds */
  HAL_Delay(1000);
  
  /* Turn off the LEDs */ 
  BSP_LCD_GLASS_ScrollSentence((uint8_t *)"      LED4 AND LED5 OFF", 1, SCROLL_SPEED_HIGH);
  BSP_LED_Off(LED4);
  BSP_LED_Off(LED5);

  /* Keep the LEDs off for one seconds */
  HAL_Delay(1000);
  
  /* -3- LEDs toggling =======================================================*/
  BSP_LCD_GLASS_ScrollSentence((uint8_t *)"      ALTERNATE TOGGLE", 1, SCROLL_SPEED_HIGH);
  
  /* For about five seconds, toggle all the LEDs */
  BSP_LED_On(LED4);
  BSP_LED_On(LED4);
  index = 0;
  
  while (index < 25)
  {
    HAL_Delay(200);
    index++;
    BSP_LED_Toggle(LED4);
    BSP_LED_Toggle(LED5);
  }
  
  /* -3- LEDs Off  =======================================================*/
  BSP_LCD_GLASS_ScrollSentence((uint8_t *)"      LEDS OFF", 1, SCROLL_SPEED_HIGH);
  BSP_LED_Off(LED4);
  BSP_LED_Off(LED5);
}

/**
  * @}
  */ 

/**
  * @}
  */ 
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
