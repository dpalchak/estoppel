/**
  ******************************************************************************
  * @file    BSP/Src/joystick.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the joystick feature in the 
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
/* extern variables ----------------------------------------------------------*/
extern JOYState_TypeDef JoyState;
extern FlagStatus KeyPressed;

/**
  * @brief  Joystick demo
  * @param  None
  * @retval None
  */
void Joystick_demo (void)
{
  JOYState_TypeDef previousstate = JOY_NONE;
  
  while(previousstate != JOY_LEFT)
  {
    if (KeyPressed)
    {
      switch(JoyState)
      {
      case JOY_LEFT:
        BSP_LED_Toggle(LED4);
        BSP_LCD_GLASS_DisplayString((uint8_t *)"  LEFT");
        HAL_Delay(1000);
        break;
        
      case JOY_RIGHT:
        BSP_LED_Toggle(LED5);
        BSP_LCD_GLASS_DisplayString((uint8_t *)" RIGHT");
        break;
        
      case JOY_UP:
        BSP_LED_Toggle(LED4);
        BSP_LED_Toggle(LED5);
        BSP_LCD_GLASS_DisplayString((uint8_t *)"    UP");
        break;
        
      case JOY_DOWN:
        BSP_LED_Toggle(LED4);
        BSP_LED_Toggle(LED5);
        BSP_LCD_GLASS_DisplayString((uint8_t *)"  DOWN");
        break;
        
      case JOY_SEL:
        BSP_LED_On(LED4);
        BSP_LED_On(LED5);
        BSP_LCD_GLASS_DisplayString((uint8_t *)"   SEL");
        break;
        
      default:
        break;
      }
      
      if(previousstate != JoyState)
      {
        BSP_LED_Off(LED4);
        BSP_LED_Off(LED5);
        if(JoyState == JOY_UP)
        {
          BSP_LED_On(LED5);
        }
      }
      
      previousstate = JoyState;
      KeyPressed = RESET;   
      HAL_Delay(200);
    }
  }
}

/**
  * @}
  */ 

/**
  * @}
  */ 
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
