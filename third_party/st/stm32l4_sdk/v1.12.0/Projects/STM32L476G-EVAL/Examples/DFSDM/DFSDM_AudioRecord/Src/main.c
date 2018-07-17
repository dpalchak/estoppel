/**
  ******************************************************************************
  * @file    DFSDM/DFSDM_AudioRecord/Src/main.c
  * @author  MCD Application Team
  * @brief   This example describes how to use DFSDM HAL API to realize
  *          audio recording.
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

/** @addtogroup DFSDM_AudioRecord
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define SaturaLH(N, L, H) (((N)<(L))?(L):(((N)>(H))?(H):(N)))
/* Private variables ---------------------------------------------------------*/
DFSDM_Channel_HandleTypeDef  DfsdmLeftChannelHandle;
DFSDM_Channel_HandleTypeDef  DfsdmRightChannelHandle;
DFSDM_Filter_HandleTypeDef   DfsdmLeftFilterHandle;
DFSDM_Filter_HandleTypeDef   DfsdmRightFilterHandle;
DMA_HandleTypeDef            hLeftDma;
DMA_HandleTypeDef            hRightDma;
SAI_HandleTypeDef            SaiHandle;
DMA_HandleTypeDef            hSaiDma;
AUDIO_DrvTypeDef            *audio_drv;
int32_t                      LeftRecBuff[2048];
int32_t                      RightRecBuff[2048];
int16_t                      PlayBuff[4096];
uint32_t                     DmaLeftRecHalfBuffCplt  = 0;
uint32_t                     DmaLeftRecBuffCplt      = 0;
uint32_t                     DmaRightRecHalfBuffCplt = 0;
uint32_t                     DmaRightRecBuffCplt     = 0;
uint32_t                     PlaybackStarted         = 0;
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void DFSDM_Init(void);
static void Playback_Init(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t i;
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

  /* Configure the system clock to have a frequency of 80 MHz */
  SystemClock_Config();

  /* Configure LED1 */
  BSP_LED_Init(LED1);

  /* Initialize DFSDM channels and filter for record */
  DFSDM_Init();

  /* Initialize playback */
  Playback_Init();
  
  /* Start DFSDM conversions */
  if(HAL_OK != HAL_DFSDM_FilterRegularStart_DMA(&DfsdmRightFilterHandle, RightRecBuff, 2048))
  {
    Error_Handler();
  }
  if(HAL_OK != HAL_DFSDM_FilterRegularStart_DMA(&DfsdmLeftFilterHandle, LeftRecBuff, 2048))
  {
    Error_Handler();
  }
  
  /* Start loopback */
  while(1)
  {
    if((DmaLeftRecHalfBuffCplt == 1) && (DmaRightRecHalfBuffCplt == 1))
    {
      /* Store values on Play buff */
      for(i = 0; i < 1024; i++)
      {
        PlayBuff[2*i]     = SaturaLH((LeftRecBuff[i] >> 8), -32768, 32767);
        PlayBuff[(2*i)+1] = SaturaLH((RightRecBuff[i] >> 8), -32768, 32767);
      }
      if(PlaybackStarted == 0)
      {
        if(0 != audio_drv->Play(AUDIO_I2C_ADDRESS, (uint16_t *) &PlayBuff[0], 4096))
        {
          Error_Handler();
        }
        if(HAL_OK != HAL_SAI_Transmit_DMA(&SaiHandle, (uint8_t *) &PlayBuff[0], 4096))
        {
          Error_Handler();
        }
        PlaybackStarted = 1;
      }      
      DmaLeftRecHalfBuffCplt  = 0;
      DmaRightRecHalfBuffCplt = 0;
    }
    if((DmaLeftRecBuffCplt == 1) && (DmaRightRecBuffCplt == 1))
    {
      /* Store values on Play buff */
      for(i = 1024; i < 2048; i++)
      {
        PlayBuff[2*i]     = SaturaLH((LeftRecBuff[i] >> 8), -32768, 32767);
        PlayBuff[(2*i)+1] = SaturaLH((RightRecBuff[i] >> 8), -32768, 32767);
      }
      DmaLeftRecBuffCplt  = 0;
      DmaRightRecBuffCplt = 0;
    }
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 1
  *            PLL_N                          = 20
  *            PLL_P                          = 7
  *            PLL_Q                          = 4
  *            PLL_R                          = 2
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
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
}

/**
  * @brief  DFSDM channels and filter initialization
  * @param  None
  * @retval None
  */
static void DFSDM_Init(void)
{
  /* Initialize channel 4 (left channel)*/
  __HAL_DFSDM_CHANNEL_RESET_HANDLE_STATE(&DfsdmLeftChannelHandle);
  DfsdmLeftChannelHandle.Instance                      = DFSDM1_Channel4;
  DfsdmLeftChannelHandle.Init.OutputClock.Activation   = ENABLE;
  DfsdmLeftChannelHandle.Init.OutputClock.Selection    = DFSDM_CHANNEL_OUTPUT_CLOCK_AUDIO;
  DfsdmLeftChannelHandle.Init.OutputClock.Divider      = 4; /* 11.294MHz/4 = 2.82MHz */
  DfsdmLeftChannelHandle.Init.Input.Multiplexer        = DFSDM_CHANNEL_EXTERNAL_INPUTS;
  DfsdmLeftChannelHandle.Init.Input.DataPacking        = DFSDM_CHANNEL_STANDARD_MODE; /* N.U. */
  DfsdmLeftChannelHandle.Init.Input.Pins               = DFSDM_CHANNEL_SAME_CHANNEL_PINS;
  DfsdmLeftChannelHandle.Init.SerialInterface.Type     = DFSDM_CHANNEL_SPI_RISING;
  DfsdmLeftChannelHandle.Init.SerialInterface.SpiClock = DFSDM_CHANNEL_SPI_CLOCK_INTERNAL;
  DfsdmLeftChannelHandle.Init.Awd.FilterOrder          = DFSDM_CHANNEL_FASTSINC_ORDER; /* N.U. */
  DfsdmLeftChannelHandle.Init.Awd.Oversampling         = 10; /* N.U. */
  DfsdmLeftChannelHandle.Init.Offset                   = 0;
  DfsdmLeftChannelHandle.Init.RightBitShift            = 2;
  if(HAL_OK != HAL_DFSDM_ChannelInit(&DfsdmLeftChannelHandle))
  {
    Error_Handler();
  }

  /* Initialize channel 3 (right channel)*/
  __HAL_DFSDM_CHANNEL_RESET_HANDLE_STATE(&DfsdmRightChannelHandle);
  DfsdmRightChannelHandle.Instance                      = DFSDM1_Channel3;
  DfsdmRightChannelHandle.Init.OutputClock.Activation   = ENABLE;
  DfsdmRightChannelHandle.Init.OutputClock.Selection    = DFSDM_CHANNEL_OUTPUT_CLOCK_AUDIO;
  DfsdmRightChannelHandle.Init.OutputClock.Divider      = 4; /* 11.294MHz/4 = 2.82MHz */
  DfsdmRightChannelHandle.Init.Input.Multiplexer        = DFSDM_CHANNEL_EXTERNAL_INPUTS;
  DfsdmRightChannelHandle.Init.Input.DataPacking        = DFSDM_CHANNEL_STANDARD_MODE; /* N.U. */
  DfsdmRightChannelHandle.Init.Input.Pins               = DFSDM_CHANNEL_FOLLOWING_CHANNEL_PINS;
  DfsdmRightChannelHandle.Init.SerialInterface.Type     = DFSDM_CHANNEL_SPI_FALLING;
  DfsdmRightChannelHandle.Init.SerialInterface.SpiClock = DFSDM_CHANNEL_SPI_CLOCK_INTERNAL;
  DfsdmRightChannelHandle.Init.Awd.FilterOrder          = DFSDM_CHANNEL_FASTSINC_ORDER; /* N.U. */
  DfsdmRightChannelHandle.Init.Awd.Oversampling         = 10; /* N.U. */
  DfsdmRightChannelHandle.Init.Offset                   = 0;
  DfsdmRightChannelHandle.Init.RightBitShift            = 2;
  if(HAL_OK != HAL_DFSDM_ChannelInit(&DfsdmRightChannelHandle))
  {
    Error_Handler();
  }
  
  /* Initialize filter 0 (left channel) */
  __HAL_DFSDM_FILTER_RESET_HANDLE_STATE(&DfsdmLeftFilterHandle);
  DfsdmLeftFilterHandle.Instance                          = DFSDM1_Filter0;
  DfsdmLeftFilterHandle.Init.RegularParam.Trigger         = DFSDM_FILTER_SW_TRIGGER;
  DfsdmLeftFilterHandle.Init.RegularParam.FastMode        = ENABLE;
  DfsdmLeftFilterHandle.Init.RegularParam.DmaMode         = ENABLE;
  DfsdmLeftFilterHandle.Init.InjectedParam.Trigger        = DFSDM_FILTER_SW_TRIGGER; /* N.U. */
  DfsdmLeftFilterHandle.Init.InjectedParam.ScanMode       = ENABLE; /* N.U. */
  DfsdmLeftFilterHandle.Init.InjectedParam.DmaMode        = DISABLE; /* N.U. */
  DfsdmLeftFilterHandle.Init.InjectedParam.ExtTrigger     = DFSDM_FILTER_EXT_TRIG_TIM1_TRGO; /* N.U. */
  DfsdmLeftFilterHandle.Init.InjectedParam.ExtTriggerEdge = DFSDM_FILTER_EXT_TRIG_RISING_EDGE; /* N.U. */
  DfsdmLeftFilterHandle.Init.FilterParam.SincOrder        = DFSDM_FILTER_SINC3_ORDER;
  DfsdmLeftFilterHandle.Init.FilterParam.Oversampling     = 64; /* 11.294MHz/(4*64) = 44.1KHz */
  DfsdmLeftFilterHandle.Init.FilterParam.IntOversampling  = 1;
  if(HAL_OK != HAL_DFSDM_FilterInit(&DfsdmLeftFilterHandle))
  {
    Error_Handler();
  }

  /* Initialize filter 1 (right channel) */
  __HAL_DFSDM_FILTER_RESET_HANDLE_STATE(&DfsdmRightFilterHandle);
  DfsdmRightFilterHandle.Instance                          = DFSDM1_Filter1;
  DfsdmRightFilterHandle.Init.RegularParam.Trigger         = DFSDM_FILTER_SYNC_TRIGGER;
  DfsdmRightFilterHandle.Init.RegularParam.FastMode        = ENABLE;
  DfsdmRightFilterHandle.Init.RegularParam.DmaMode         = ENABLE;
  DfsdmRightFilterHandle.Init.InjectedParam.Trigger        = DFSDM_FILTER_SW_TRIGGER; /* N.U. */
  DfsdmRightFilterHandle.Init.InjectedParam.ScanMode       = ENABLE; /* N.U. */
  DfsdmRightFilterHandle.Init.InjectedParam.DmaMode        = DISABLE; /* N.U. */
  DfsdmRightFilterHandle.Init.InjectedParam.ExtTrigger     = DFSDM_FILTER_EXT_TRIG_TIM1_TRGO; /* N.U. */
  DfsdmRightFilterHandle.Init.InjectedParam.ExtTriggerEdge = DFSDM_FILTER_EXT_TRIG_RISING_EDGE; /* N.U. */
  DfsdmRightFilterHandle.Init.FilterParam.SincOrder        = DFSDM_FILTER_SINC3_ORDER;
  DfsdmRightFilterHandle.Init.FilterParam.Oversampling     = 64; /* 11.294MHz/(4*64) = 44.1KHz */
  DfsdmRightFilterHandle.Init.FilterParam.IntOversampling  = 1;
  if(HAL_OK != HAL_DFSDM_FilterInit(&DfsdmRightFilterHandle))
  {
    Error_Handler();
  }
  
  /* Configure regular channel and continuous mode for filter 0 (left channel) */
  if(HAL_OK != HAL_DFSDM_FilterConfigRegChannel(&DfsdmLeftFilterHandle, DFSDM_CHANNEL_4, DFSDM_CONTINUOUS_CONV_ON))
  {
    Error_Handler();
  }

  /* Configure regular channel and continuous mode for filter 1 (right channel) */
  if(HAL_OK != HAL_DFSDM_FilterConfigRegChannel(&DfsdmRightFilterHandle, DFSDM_CHANNEL_3, DFSDM_CONTINUOUS_CONV_ON))
  {
    Error_Handler();
  }
}

/**
  * @brief  Playback initialization
  * @param  None
  * @retval None
  */
static void Playback_Init(void)
{
  /* Initialize SAI */
  __HAL_SAI_RESET_HANDLE_STATE(&SaiHandle);

  SaiHandle.Instance = SAI1_Block_B;

  SaiHandle.Init.AudioMode      = SAI_MODEMASTER_TX;
  SaiHandle.Init.Synchro        = SAI_ASYNCHRONOUS;
  SaiHandle.Init.SynchroExt     = SAI_SYNCEXT_DISABLE;
  SaiHandle.Init.OutputDrive    = SAI_OUTPUTDRIVE_ENABLE;
  SaiHandle.Init.NoDivider      = SAI_MASTERDIVIDER_ENABLE;
  SaiHandle.Init.FIFOThreshold  = SAI_FIFOTHRESHOLD_1QF;
  SaiHandle.Init.AudioFrequency = SAI_AUDIO_FREQUENCY_44K;
  SaiHandle.Init.Mckdiv         = 0; /* N.U */
  SaiHandle.Init.MonoStereoMode = SAI_STEREOMODE;
  SaiHandle.Init.CompandingMode = SAI_NOCOMPANDING;
  SaiHandle.Init.TriState       = SAI_OUTPUT_NOTRELEASED;
  SaiHandle.Init.Protocol       = SAI_FREE_PROTOCOL;
  SaiHandle.Init.DataSize       = SAI_DATASIZE_16;
  SaiHandle.Init.FirstBit       = SAI_FIRSTBIT_MSB;
  SaiHandle.Init.ClockStrobing  = SAI_CLOCKSTROBING_FALLINGEDGE;

  SaiHandle.FrameInit.FrameLength       = 32; 
  SaiHandle.FrameInit.ActiveFrameLength = 16;
  SaiHandle.FrameInit.FSDefinition      = SAI_FS_CHANNEL_IDENTIFICATION;
  SaiHandle.FrameInit.FSPolarity        = SAI_FS_ACTIVE_LOW;
  SaiHandle.FrameInit.FSOffset          = SAI_FS_BEFOREFIRSTBIT;

  SaiHandle.SlotInit.FirstBitOffset = 0;
  SaiHandle.SlotInit.SlotSize       = SAI_SLOTSIZE_DATASIZE;
  SaiHandle.SlotInit.SlotNumber     = 2; 
  SaiHandle.SlotInit.SlotActive     = (SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_1);

  if(HAL_OK != HAL_SAI_Init(&SaiHandle))
  {
    Error_Handler();
  }
  
  /* Enable SAI to generate clock used by audio driver */
  __HAL_SAI_ENABLE(&SaiHandle);
  
  /* Initialize audio driver */
  if(WM8994_ID != wm8994_drv.ReadID(AUDIO_I2C_ADDRESS))
  {
    Error_Handler();
  }
  audio_drv = &wm8994_drv;
  audio_drv->Reset(AUDIO_I2C_ADDRESS);  
  if(0 != audio_drv->Init(AUDIO_I2C_ADDRESS, OUTPUT_DEVICE_HEADPHONE, 100, AUDIO_FREQUENCY_44K))
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  while (1)
  {
    /* Toggle LED1 with a period of one second */
    BSP_LED_Toggle(LED1);
    HAL_Delay(1000);
  }
}

/**
  * @brief  Initializes the DFSDM channel MSP.
  * @param  hdfsdm_channel : DFSDM channel handle.
  * @retval None
  */
void HAL_DFSDM_ChannelMspInit(DFSDM_Channel_HandleTypeDef *hdfsdm_channel)
{
  /* Init of clock, gpio and PLLSAI1 clock only needed one time */
  if(hdfsdm_channel == &DfsdmLeftChannelHandle)
  {
    GPIO_InitTypeDef GPIO_Init;
    RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInitStruct;
    
    /* Enable DFSDM clock */
    __HAL_RCC_DFSDM1_CLK_ENABLE();
    
    /* Configure PC2 for DFSDM_CKOUT and PC0 for DFSDM_DATIN4 */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_Init.Mode      = GPIO_MODE_AF_PP;
    GPIO_Init.Pull      = GPIO_PULLDOWN;
    GPIO_Init.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_Init.Alternate = GPIO_AF6_DFSDM1;
    GPIO_Init.Pin = GPIO_PIN_2;
    HAL_GPIO_Init(GPIOC, &GPIO_Init);
    GPIO_Init.Pin = GPIO_PIN_0;
    HAL_GPIO_Init(GPIOC, &GPIO_Init);
    
    /* Configure and enable PLLSAI1 clock to generate 11.294MHz */
    RCC_PeriphCLKInitStruct.PeriphClockSelection    = RCC_PERIPHCLK_SAI1;
    RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1Source   = RCC_PLLSOURCE_HSE;
    RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1M        = 1;
    RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1N        = 24;
    RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1P        = 17;
    RCC_PeriphCLKInitStruct.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_SAI1CLK;
    RCC_PeriphCLKInitStruct.Sai1ClockSelection      = RCC_SAI1CLKSOURCE_PLLSAI1;
    if(HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct) != HAL_OK)
    {
      Error_Handler();
    }
  }
}

/**
  * @brief  Initializes the DFSDM filter MSP.
  * @param  hdfsdm_filter : DFSDM filter handle.
  * @retval None
  */
void HAL_DFSDM_FilterMspInit(DFSDM_Filter_HandleTypeDef *hdfsdm_filter)
{
  if(hdfsdm_filter == &DfsdmLeftFilterHandle)
  {
    /* Configure DMA1_Channel4 */
    __HAL_RCC_DMA1_CLK_ENABLE();
    hLeftDma.Init.Request             = DMA_REQUEST_0;
    hLeftDma.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    hLeftDma.Init.PeriphInc           = DMA_PINC_DISABLE;
    hLeftDma.Init.MemInc              = DMA_MINC_ENABLE;
    hLeftDma.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hLeftDma.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
    hLeftDma.Init.Mode                = DMA_CIRCULAR;
    hLeftDma.Init.Priority            = DMA_PRIORITY_HIGH;
    hLeftDma.Instance                 = DMA1_Channel4;
    __HAL_LINKDMA(hdfsdm_filter, hdmaReg, hLeftDma);
    if (HAL_OK != HAL_DMA_Init(&hLeftDma))
    {
      Error_Handler();
    }
    HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0x01, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
  }
  else if(hdfsdm_filter == &DfsdmRightFilterHandle)
  {
    /* Configure DMA1_Channel5 */
    __HAL_RCC_DMA1_CLK_ENABLE();
    hRightDma.Init.Request             = DMA_REQUEST_0;
    hRightDma.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    hRightDma.Init.PeriphInc           = DMA_PINC_DISABLE;
    hRightDma.Init.MemInc              = DMA_MINC_ENABLE;
    hRightDma.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hRightDma.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
    hRightDma.Init.Mode                = DMA_CIRCULAR;
    hRightDma.Init.Priority            = DMA_PRIORITY_HIGH;
    hRightDma.Instance                 = DMA1_Channel5;
    __HAL_LINKDMA(hdfsdm_filter, hdmaReg, hRightDma);
    if (HAL_OK != HAL_DMA_Init(&hRightDma))
    {
      Error_Handler();
    }
    HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0x01, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
  }
}

/**
  * @brief  SAI MSP Init.
  * @param  hsai : pointer to a SAI_HandleTypeDef structure that contains
  *                the configuration information for SAI module.
  * @retval None
  */
void HAL_SAI_MspInit(SAI_HandleTypeDef *hsai)
{
  GPIO_InitTypeDef  GPIO_Init;
  
  /* Enable SAI1 clock */
  __HAL_RCC_SAI1_CLK_ENABLE();
  
  /* Configure GPIOs used for SAI1 */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  GPIO_Init.Mode      = GPIO_MODE_AF_PP;
  GPIO_Init.Pull      = GPIO_NOPULL;
  GPIO_Init.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_Init.Alternate = GPIO_AF13_SAI1;
  GPIO_Init.Pin       = (GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
  HAL_GPIO_Init(GPIOF, &GPIO_Init);
  
  /* Configure DMA used for SAI1 */
  __HAL_RCC_DMA2_CLK_ENABLE();
  hSaiDma.Init.Request             = DMA_REQUEST_1;
  hSaiDma.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  hSaiDma.Init.PeriphInc           = DMA_PINC_DISABLE;
  hSaiDma.Init.MemInc              = DMA_MINC_ENABLE;
  hSaiDma.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  hSaiDma.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
  hSaiDma.Init.Mode                = DMA_CIRCULAR;
  hSaiDma.Init.Priority            = DMA_PRIORITY_HIGH;
  hSaiDma.Instance                 = DMA2_Channel2;
  __HAL_LINKDMA(hsai, hdmatx, hSaiDma);
  if (HAL_OK != HAL_DMA_Init(&hSaiDma))
  {
    Error_Handler();
  }
  HAL_NVIC_SetPriority(DMA2_Channel2_IRQn, 0x01, 0);
  HAL_NVIC_EnableIRQ(DMA2_Channel2_IRQn);
}

/**
  * @brief  Half regular conversion complete callback. 
  * @param  hdfsdm_filter : DFSDM filter handle.
  * @retval None
  */
void HAL_DFSDM_FilterRegConvHalfCpltCallback(DFSDM_Filter_HandleTypeDef *hdfsdm_filter)
{
  if(hdfsdm_filter == &DfsdmLeftFilterHandle)
  {
    DmaLeftRecHalfBuffCplt = 1;
  }
  else
  {
    DmaRightRecHalfBuffCplt = 1;
  }
}

/**
  * @brief  Regular conversion complete callback. 
  * @note   In interrupt mode, user has to read conversion value in this function
            using HAL_DFSDM_FilterGetRegularValue.
  * @param  hdfsdm_filter : DFSDM filter handle.
  * @retval None
  */
void HAL_DFSDM_FilterRegConvCpltCallback(DFSDM_Filter_HandleTypeDef *hdfsdm_filter)
{
  if(hdfsdm_filter == &DfsdmLeftFilterHandle)
  {
    DmaLeftRecBuffCplt = 1;
  }
  else
  {
    DmaRightRecBuffCplt = 1;
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
