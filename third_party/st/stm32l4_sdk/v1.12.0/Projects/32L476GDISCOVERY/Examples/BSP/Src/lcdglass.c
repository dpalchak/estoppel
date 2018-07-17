/**
  ******************************************************************************
  * @file    BSP/Src/lcdglass.c 
  * @author  MCD Application Team
  * @brief   This example code shows how to use LCD Glass display feature 
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
typedef enum {
  DISPLAY_BAR = 0,
  DISPLAY_CHAR,
  DISPLAY_STRING,
  SCROLLING,
  CONTRAST_MIN,
  CONTRAST_MAX,
  INT_TO_CHAR,
  LCDGLASS_FEATURES_NB
} LCDGlassFeature_TypeDef;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void LCDGlass_Show_Feature(LCDGlassFeature_TypeDef feature);
/* Private functions ---------------------------------------------------------*/
/* extern variables ----------------------------------------------------------*/
extern FlagStatus LcdInitialized;
extern FlagStatus KeyPressed;

/**
  * @brief  LCD demo
  * @param  None
  * @retval None
  */
void LCDGlass_demo (void)
{ 
  LCDGlassFeature_TypeDef LCDGlass_Feature ;

  if(LcdInitialized != SET)
  {
    BSP_LCD_GLASS_Init();
  }
  
  LCDGlass_Feature = DISPLAY_BAR;
  
  while(LCDGlass_Feature < LCDGLASS_FEATURES_NB)
  {
    if(KeyPressed != RESET)
    {
      /* Reset Key press global variable */
      KeyPressed = RESET;
      break;
    }

    LCDGlass_Show_Feature(LCDGlass_Feature);
    BSP_LCD_GLASS_Clear();
    HAL_Delay(100);
    LCDGlass_Feature++;
  }
  return;
}

/**
  * @brief  Show LCD Features
  * @param  feature : feature index
  * @retval None
  */

static void LCDGlass_Show_Feature(LCDGlassFeature_TypeDef feature)
{
  uint16_t tab[6];
  switch (feature)
  {
  case DISPLAY_BAR:
    BSP_LCD_GLASS_DisplayBar(LCD_BAR_0);
    HAL_Delay(300);
    BSP_LCD_GLASS_ClearBar(LCD_BAR_0);
    BSP_LCD_GLASS_DisplayBar(LCD_BAR_1);
    HAL_Delay(300);
    BSP_LCD_GLASS_ClearBar(LCD_BAR_1);
    BSP_LCD_GLASS_DisplayBar(LCD_BAR_2);
    HAL_Delay(300);
    BSP_LCD_GLASS_ClearBar(LCD_BAR_2);
    BSP_LCD_GLASS_DisplayBar(LCD_BAR_3);
    HAL_Delay(300);
    BSP_LCD_GLASS_ClearBar(LCD_BAR_3);
    HAL_Delay(300);
    BSP_LCD_GLASS_BarLevelConfig(BATTERYLEVEL_OFF);
    HAL_Delay(300);
    BSP_LCD_GLASS_BarLevelConfig(BATTERYLEVEL_1_4);
    HAL_Delay(300);
    BSP_LCD_GLASS_BarLevelConfig(BATTERYLEVEL_1_2);
    HAL_Delay(300);
    BSP_LCD_GLASS_BarLevelConfig(BATTERYLEVEL_3_4);
    HAL_Delay(300);
    BSP_LCD_GLASS_BarLevelConfig(BATTERYLEVEL_FULL);
    HAL_Delay(300);
    BSP_LCD_GLASS_BlinkConfig(LCD_BLINKMODE_ALLSEG_ALLCOM, LCD_BLINKFREQUENCY_DIV512);
    HAL_Delay(2000);
    /* Clear screen for new feature */
    BSP_LCD_GLASS_Clear();
    BSP_LCD_GLASS_BlinkConfig(LCD_BLINKMODE_OFF, LCD_BLINKFREQUENCY_DIV512);
    break;
    
  case DISPLAY_CHAR:
    BSP_LCD_GLASS_DisplayChar((uint8_t *)"8", POINT_ON, DOUBLEPOINT_ON, LCD_DIGIT_POSITION_1);
    HAL_Delay(300);
    BSP_LCD_GLASS_DisplayChar((uint8_t *)"8", POINT_ON, DOUBLEPOINT_ON, LCD_DIGIT_POSITION_2);
    HAL_Delay(300);
    BSP_LCD_GLASS_DisplayChar((uint8_t *)"8", POINT_ON, DOUBLEPOINT_ON, LCD_DIGIT_POSITION_3);
    HAL_Delay(300);
    BSP_LCD_GLASS_DisplayChar((uint8_t *)"8", POINT_ON, DOUBLEPOINT_ON, LCD_DIGIT_POSITION_4);
    HAL_Delay(300);
    BSP_LCD_GLASS_DisplayChar((uint8_t *)"8", POINT_ON, DOUBLEPOINT_ON, LCD_DIGIT_POSITION_5);
    HAL_Delay(300);
    BSP_LCD_GLASS_DisplayChar((uint8_t *)"8", POINT_ON, DOUBLEPOINT_ON, LCD_DIGIT_POSITION_6);
    HAL_Delay(300);
    break;
    
  case DISPLAY_STRING:
    BSP_LCD_GLASS_DisplayString((uint8_t *)"88888888");
    HAL_Delay(1000);
    break;
    
  case SCROLLING:
    BSP_LCD_GLASS_ScrollSentence((uint8_t *)"      TEST SCROLLING", 1, SCROLL_SPEED_MEDIUM);
    HAL_Delay(1000);
    break;

  case CONTRAST_MIN:
    BSP_LCD_GLASS_Contrast(LCD_CONTRASTLEVEL_0);
    BSP_LCD_GLASS_ScrollSentence((uint8_t *)"      SET CONTRAST MIN", 1, SCROLL_SPEED_MEDIUM);
    HAL_Delay(1000);
    break;

  case CONTRAST_MAX:
    BSP_LCD_GLASS_Contrast(LCD_CONTRASTLEVEL_7);
    BSP_LCD_GLASS_ScrollSentence((uint8_t *)"      SET CONTRAST MAX", 1, SCROLL_SPEED_MEDIUM);
    HAL_Delay(1000);
    break;
    
  case INT_TO_CHAR:
    Convert_IntegerIntoChar(3500, tab);
    tab[5] = 'A';
    tab[4] = '�';
    
    /* Test the significant digit for displays 3 or 4 digits*/
    if (tab[0] != '0')
    {
      tab[1] |= DOT; /* To add decimal point */
    }
    else
    {
      /* To shift for suppress '0' before decimal */
      tab[0] = tab[1] ;
      tab[0] |= DOT ;
      tab[1] = tab[2] ;
      tab[2] = tab[3] ;
      tab[3] = ' ';
    }
  
    BSP_LCD_GLASS_DisplayStrDeci(tab);
    HAL_Delay(1000);
    break;

  default:
	break;
  }
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
