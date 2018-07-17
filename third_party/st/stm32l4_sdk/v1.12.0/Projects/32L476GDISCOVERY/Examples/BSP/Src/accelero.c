/**
  ******************************************************************************
  * @file    BSP/Src/accelero.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the accelerometer feature in the 
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
#define ACCELERO_THRESHOLD_DETECTION 10000
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void Accelero_SetHint(void);
static void Accelero_Convert(uint8_t Axis, int32_t Value, uint16_t *DisplayString);
/* Private functions ---------------------------------------------------------*/
/* Extern variables ---------------------------------------------------------*/
extern __IO FlagStatus KeyPressed;

/*
  * @brief  Test Gyroscope MEMS Hardware.
  *         The main objectif of this test is to check accelerometer hardware connection, and 
  *         display angular data.
  * @param  None
  * @retval None
  */
void Accelero_demo(void)
{
  /* display variable */
  uint16_t datatodisplay[LCD_DIGIT_MAX_NUMBER] = {0};
  uint8_t i = 0;
  
  /* Gyroscope variables */
  int16_t buffer[3] = {0};
  int16_t xval = 0;
  int16_t yval = 0;
  int16_t zval = 0;
  uint16_t xvalabs = 0;
  uint16_t yvalabs = 0;
  uint16_t zvalabs = 0;

  /* Display accelerometer application hint */
  Accelero_SetHint();
  
  /* Init Gyroscope Mems */
  if(BSP_ACCELERO_Init() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  while(KeyPressed != SET)
  {
    /* Read Gyroscope Angular data */
    BSP_ACCELERO_GetXYZ(buffer);

    /* Get absolute value */
    xval = buffer[0];
    yval = buffer[1];
    zval = buffer[2];
    xvalabs = ABS(xval);
    yvalabs = ABS(yval);
    zvalabs = ABS(zval);
    
    /* Treat only significant datas */
    if((xvalabs > ACCELERO_THRESHOLD_DETECTION) || (yvalabs > ACCELERO_THRESHOLD_DETECTION) ||
       (zvalabs > ACCELERO_THRESHOLD_DETECTION))
    {
      /* reset display buffer */
      for(i = 0; i < LCD_DIGIT_MAX_NUMBER; i++)
      {
        datatodisplay[i] = 0;
      }
      
      /* Angular acceleration around X axis is higher than on Y */
      if(xvalabs > yvalabs)
      {
        /* Angular acceleration around X axis is higher than on Z */
        if(xvalabs > zvalabs)
        {
          Accelero_Convert('X', xval, datatodisplay);
          BSP_LCD_GLASS_DisplayStrDeci(datatodisplay);
        }
        /* Angular acceleration around X axis is lower than on Z */
        else
        { 
          Accelero_Convert('Z', zval, datatodisplay);
          BSP_LCD_GLASS_DisplayStrDeci(datatodisplay);
        }
      }
      /* Angular acceleration around X axis is lower than on Y */
      else
      {
        /* Angular acceleration around Y axis is higher than on Z */
        if(yvalabs > zvalabs)
        {
          Accelero_Convert('Y', yval, datatodisplay);
          BSP_LCD_GLASS_DisplayStrDeci(datatodisplay);
        }
        /* Angular acceleration around Y axis is lower than on Z */
        else
        { 
          Accelero_Convert('Z', zval, datatodisplay);
          BSP_LCD_GLASS_DisplayStrDeci(datatodisplay);
        }
      }
    }
    else
    {
      BSP_LCD_GLASS_DisplayString("STABLE");
    }
    /* insert Delay */
    HAL_Delay(200);
  }
}
/**
  * @}
  */ 

/**
  * @brief  Convert value to display string
  * @param  None
  * @retval None
  */

static void Accelero_Convert(uint8_t Axis, int32_t Value, uint16_t *DisplayString)
{
  uint8_t i = 0;
  uint32_t valuetoconvert = 0;

  valuetoconvert = (uint32_t) (ABS(Value) >> 6);

  Convert_IntegerIntoChar(valuetoconvert, DisplayString);

  while(*(DisplayString + i) == '0')
  {
    *(DisplayString + i) = ' ';
    i++;
  }

  /* Add Axis informationon 1st digi */
  *(DisplayString) = (uint16_t) Axis | DOUBLE_DOT;

  /* Handle negative value */
  if(Value < 0)
  {
    *(DisplayString + 1) = '-';
  }
}
/**
  * @}
  */ 


/**
  * @brief  Display Gyroscope demo hint
  * @param  None
  * @retval None
  */
static void Accelero_SetHint(void)
{
#if LCD_GLASS
  /* Clear the LCD */ 
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  
  /* Set Led Demo description */
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), 80);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE); 
  BSP_LCD_SetFont(&Font24);
  BSP_LCD_DisplayStringAt(0, 0, (uint8_t *)"Led", CENTER_MODE);
  BSP_LCD_SetFont(&Font12);
  BSP_LCD_DisplayStringAt(0, 30, (uint8_t *)"This example shows how to", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 45, (uint8_t *)"initialize and turn on, turn off", CENTER_MODE); 
  BSP_LCD_DisplayStringAt(0, 60, (uint8_t *)"and toggle the leds", CENTER_MODE); 
  
  /* Set the LCD Text Color */
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);  
  BSP_LCD_DrawRect(10, 90, BSP_LCD_GetXSize() - 20, BSP_LCD_GetYSize()- 100);
  BSP_LCD_DrawRect(11, 91, BSP_LCD_GetXSize() - 22, BSP_LCD_GetYSize()- 102);
#endif
}
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
