/**
  ******************************************************************************
  * @file    TouchSensing\TouchSensing_1touchkey\Src\main.c 
  * @author  MCD Application Team
  * @brief   Main program body
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
#include "main.h"

/** @addtogroup STM32L4xx_HAL_Examples
  * @{
  */

/** @addtogroup TouchSensing_1touchkey
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Select to use or not the LCD (0=No, 1=Yes) */
#define USE_LCD (1)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* TSC handler declaration */
TSC_HandleTypeDef TscHandle;

/* Private function prototypes -----------------------------------------------*/
  
void SystemClock_Config(void);
static void Error_Handler(void);
static void Process_Sensors(tsl_user_status_t status);

/* Utility functions for the LCD */
#if USE_LCD > 0
static uint8_t LcdMakeLine(uint8_t *output, uint8_t *name, uint8_t *state, uint8_t *data);
static uint8_t *LcdState2String(TSL_StateId_enum_T State);
static void LcdValue2String(uint8_t *output, int16_t input);
#endif

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{ 
  tsl_user_status_t tsl_status;

  /* STM32L4xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the system clock to 80 MHz */
  SystemClock_Config();

  /* Configure LEDs */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED3);

  /* Configure the TSC peripheral */
  TscHandle.Instance                     = TSCx;
  TscHandle.Init.AcquisitionMode         = TSC_ACQ_MODE_NORMAL;
  TscHandle.Init.CTPulseHighLength       = TSC_CTPH_2CYCLES;
  TscHandle.Init.CTPulseLowLength        = TSC_CTPL_2CYCLES;
  TscHandle.Init.IODefaultMode           = TSC_IODEF_OUT_PP_LOW;
  TscHandle.Init.MaxCountInterrupt       = DISABLE;
  TscHandle.Init.MaxCountValue           = TSC_MCV_8191;
  TscHandle.Init.PulseGeneratorPrescaler = TSC_PG_PRESC_DIV32;
  TscHandle.Init.SpreadSpectrum          = DISABLE;
  TscHandle.Init.SpreadSpectrumDeviation = 127;
  TscHandle.Init.SpreadSpectrumPrescaler = TSC_SS_PRESC_DIV1;
  TscHandle.Init.SynchroPinPolarity      = TSC_SYNC_POLARITY_FALLING;
  /* All channel, shield and sampling IOs must be declared below */
  TscHandle.Init.ChannelIOs              = TSC_GROUP1_IO1;
  TscHandle.Init.SamplingIOs             = TSC_GROUP1_IO2 | TSC_GROUP4_IO2;
  TscHandle.Init.ShieldIOs               = TSC_GROUP4_IO1;

  if (HAL_TSC_Init(&TscHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* Just to indicate the fw is alive... */
  BSP_LED_On(LED1);
  BSP_LED_On(LED4);
  BSP_LED_On(LED3);
  
  /* Configure LCD */
#if USE_LCD > 0
  BSP_LCD_Init();
  BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE); 
  BSP_LCD_Clear(LCD_COLOR_WHITE);
  BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
  BSP_LCD_DisplayStringAt(0, 10, (uint8_t *)"STM32L476xx", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 35, (uint8_t *)"TouchSensing", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 55, (uint8_t *)"Example", CENTER_MODE);
#endif
  
  BSP_LED_Off(LED1);
  BSP_LED_Off(LED4);
  BSP_LED_Off(LED3);
  
  /* Initialize the STMTouch driver */
  tsl_user_Init();
  
  /* Infinite loop */
  while (1)
  {
    /* Execute STMTouch Driver state machine */
    tsl_status = tsl_user_Exec();
    if (tsl_status != TSL_USER_STATUS_BUSY)
    {
      Process_Sensors(tsl_status);
    }
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
#if defined(USE_STM32L476G_EVAL_REVA)
  * @ note REVA dependency, need AHBCLK div 2 to perform correctly LCD access
  *            AHB Prescaler                  = 2
#elif defined(USE_STM32L476G_EVAL_REVB)
  *            AHB Prescaler                  = 1
#endif
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 1
  *            PLL_N                          = 20
  *            PLL_R                          = 2
  *            PLL_P                          = 7
  *            PLL_Q                          = 4
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* Enable HSE Oscillator and activate PLL with HSE as source   */
  /* (Default MSI Oscillator enabled at system reset remains ON) */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 20;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLP = 7;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
#if defined(USE_STM32L476G_EVAL_REVA)
  /* REVA dependency, need AHBCLK div 2 to perform correctly LCD access */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
#elif defined(USE_STM32L476G_EVAL_REVB)
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
#endif
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
}

/**
  * @brief  Display sensors information on LEDs and LCD
  * @param  status TSL user status
  * @retval None
  */
void Process_Sensors(tsl_user_status_t status)
{
#if USE_LCD > 0  
  uint8_t TheLine[20];
  uint8_t str_value[6]; /* sign + 4 digits + empty char */
#endif

#if USE_LCD > 0
  /* Display TS1 sensor information */
  LcdValue2String(str_value, MyTKeys[0].p_ChD->Delta);
  LcdMakeLine(TheLine, (uint8_t *)("TS1"), LcdState2String(MyTKeys[0].p_Data->StateId), str_value);
  BSP_LCD_DisplayStringAtLine(7, TheLine);
  BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
#endif
    
  /* LED1 is ON when TS1 on board is touched */
  if (MyTKeys[0].p_Data->StateId == TSL_STATEID_DETECT)
  {
    BSP_LED_On(LED1);
  }
  else
  {
    BSP_LED_Off(LED1);
  }

  /* ECS information */
  switch (status)
  {
    case TSL_USER_STATUS_OK_ECS_OFF:
      BSP_LED_Off(LED4);
#if USE_LCD > 0
      BSP_LCD_DisplayStringAtLine(4, (uint8_t *)("ECS OFF"));
#endif      
      break;
    case TSL_USER_STATUS_OK_ECS_ON:
      BSP_LED_Toggle(LED4);
#if USE_LCD > 0
      BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
      BSP_LCD_DisplayStringAtLine(4, (uint8_t *)("ECS ON "));
      BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
#endif      
      break;
    default:
      break;
  }
}

#if USE_LCD > 0
/**
  * @brief Converts a value in string
  * @param[out] output String
  * @param[in]  input  Value (between -9999 and +9999)
  * @retval None
  */
void LcdValue2String(uint8_t *output, int16_t input)
{
  uint8_t *temp;
  temp = output;

  if ((input > 9999) || (input < -9999))
  {
    *temp = 0;
    return;
  }
  
  /* 1st char: sign */
  if (input < 0)
  {
    *temp = '-';
    input = -input;
  }
  else
  {
    *temp = '+';
  }

  temp++;
  
  /* 2nd char: first digit */
  if ((input > 999) && (input < 10000))
  {
    *temp = 48 + (input / 1000); /* First digit */
  }
  else
  {
    *temp = ' ';
  }
    
  temp++;

  /* 3rd char: second digit */
  if (input > 99)
  {
    *temp = 48 + ((input % 1000) / 100); /* Second digit */
  }
  else
  {
    *temp = ' ';
  }
  
  temp++;
  
  /* 4th char: third digit */
  if (input > 9)
  {
    *temp = 48 + ((input % 100) / 10); /* Third digit */
  }
  else
  {
    *temp = ' ';
  }
    
  temp++;
  
  /* 5th char: fourth digit */
  *temp = 48 + (input % 10); /* Fourth digit */
  
  temp++;

  /* 5th char: null value */
  *temp = 0;
}

/**
  * @brief Converts the sensor state ID in a string
  * @param[in] state Sensor state ID
  * @retval String Sensor state string
  */
uint8_t* LcdState2String(TSL_StateId_enum_T state)
{
  BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
  switch (state)
  {
    case TSL_STATEID_DEB_CALIB:
        return (uint8_t*)("DB_CALIB");
    case TSL_STATEID_CALIB:
        return (uint8_t*)("CALIB   ");
    case TSL_STATEID_RELEASE:
        return (uint8_t*)("RELEASE ");
    case TSL_STATEID_DEB_RELEASE_PROX:	
    case TSL_STATEID_DEB_RELEASE_DETECT:
    case TSL_STATEID_DEB_RELEASE_TOUCH:
        return (uint8_t*)("DB_REL  ");
    case TSL_STATEID_PROX:
        BSP_LCD_SetTextColor(LCD_COLOR_MAGENTA);
        return (uint8_t*)("PROX    ");
    case TSL_STATEID_DEB_PROX:
    case TSL_STATEID_DEB_PROX_DETECT:
    case TSL_STATEID_DEB_PROX_TOUCH:
        return (uint8_t*)("DB_PROX ");
    case TSL_STATEID_DETECT:
        BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
        return (uint8_t*)("DETECT  ");
    case TSL_STATEID_DEB_DETECT:
        return (uint8_t*)("DB_DET  ");
    case TSL_STATEID_TOUCH:
        BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
        return (uint8_t*)("TOUCH   ");
    case TSL_STATEID_ERROR:
        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        return (uint8_t*)("ERROR   ");
    case TSL_STATEID_DEB_ERROR_CALIB:
    case TSL_STATEID_DEB_ERROR_RELEASE:
    case TSL_STATEID_DEB_ERROR_PROX:
    case TSL_STATEID_DEB_ERROR_DETECT:
    case TSL_STATEID_DEB_ERROR_TOUCH:
        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        return (uint8_t*)("DB_ERR  ");
    case TSL_STATEID_OFF:
        return (uint8_t*)("OFF     ");
    default:
        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        return (uint8_t*)("UNKNOWN ");
  }
}

/**
  * @brief Create the string to be displayed
  * @param[out] output Output string
  * @param[in]  name   Sensor name (3 characters)
  * @param[in]  state  Sensor state (8 characters)
  * @param[in]  data   Sensor data (-9999 to +9999)
  * @retval uint8_t Number of characters in the output string
  */
uint8_t LcdMakeLine(uint8_t *output, uint8_t *name, uint8_t *state, uint8_t *data)
{
  uint8_t index = 0;
  uint8_t index2;
  
  /* Sensor name: 3 characters */
  for (index2 = 0; index2 < 3; index2++)
  {
    output[index++] = name[index2];
  }
  output[index++] = ' ';

  /* Sensor state: 8 characters */
  for (index2 = 0; index2 < 8; index2++)
  {
    output[index++] = state[index2];
  }
  output[index++] = ' ';
  
  /* Sensor data */
  for (index2 = 0; data[index2] != 0; index2++)
  {
    output[index++] = data[index2];
  }
  
  output[index++] = 0;
  
  return index;
}
#endif /* if USE_LCD > 0 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while (1)
  {
    BSP_LED_Toggle(LED3);
    HAL_Delay(200);
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
    BSP_LED_Toggle(LED3);
    HAL_Delay(100);
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
