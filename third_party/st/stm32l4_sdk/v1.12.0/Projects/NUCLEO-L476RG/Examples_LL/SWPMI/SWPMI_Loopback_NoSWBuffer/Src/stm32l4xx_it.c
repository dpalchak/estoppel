/** 
  ******************************************************************************
  * @file    Examples_LL/SWPMI/SWPMI_Loopback_NoSWBuffer/Src/stm32l4xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
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
#include "stm32l4xx_it.h"

/** @addtogroup STM32L4xx_LL_Examples
  * @{
  */

/** @addtogroup SWPMI_Loopback_NoSWBuffer
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32L4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles external lines 10 to 15 interrupt request.
  * @param  None
  * @retval None
  */
void USER_BUTTON_IRQHANDLER(void)
{
  /* Manage Flags */
  if(LL_EXTI_IsActiveFlag_0_31(USER_BUTTON_EXTI_LINE) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(USER_BUTTON_EXTI_LINE);

    /* Manage code in main.c. */
    UserButton_Callback(); 
  }
}

/**
  * @brief  This function handles SWPMI1 interrupt request.
  * @param  None
  * @retval None
  */
void SWPMI1_IRQHandler(void)
{
  uint32_t regisr = LL_SWPMI_ReadReg(SWPMI1, ISR);
  uint32_t regier = LL_SWPMI_ReadReg(SWPMI1, IER);

  /* SWPMI CRC error interrupt occurred --------------------------------------*/
  if(((regisr & LL_SWPMI_ISR_RXBERF) != RESET) && ((regier & LL_SWPMI_IER_RXBERIE) != RESET))
  {
    /* Clear Receive CRC and Receive buffer full flag */
    LL_SWPMI_ClearFlag_RXBER(SWPMI1);
    LL_SWPMI_ClearFlag_RXBF(SWPMI1);
    SWPMI_TransferError_Callback();
  }

  /* SWPMI Over-Run interrupt occurred -----------------------------------------*/
  if(((regisr & LL_SWPMI_ISR_RXOVRF) != RESET) && ((regier & LL_SWPMI_IER_RXOVRIE) != RESET))
  {
    /* Clear Receive overrun flag */
    LL_SWPMI_ClearFlag_RXOVR(SWPMI1);
    SWPMI_TransferError_Callback();
  }

  /* SWPMI Under-Run interrupt occurred -----------------------------------------*/
  if(((regisr & LL_SWPMI_ISR_TXUNRF) != RESET) && ((regier & LL_SWPMI_IER_TXUNRIE) != RESET))
  {
    /* Clear Transmit under run flag */
    LL_SWPMI_ClearFlag_TXUNR(SWPMI1);
    SWPMI_TransferError_Callback();
  }

  /* SWPMI in mode Receiver (Receive buffer full) -----------------------------*/
  if(((regisr & LL_SWPMI_ISR_RXBFF) != RESET) && ((regier & LL_SWPMI_IER_RXBFIE) != RESET)
    && (((regisr & LL_SWPMI_ISR_RXNE) != RESET) && ((regier & LL_SWPMI_IER_RIE)  != RESET)))
  {
    SWPMI_ReceiveBufferFull_Callback();
  }
  
  /* SWPMI in mode Receiver ---------------------------------------------------*/
  if((LL_SWPMI_IsActiveFlag_RXNE(SWPMI1) != RESET) && ((regier & LL_SWPMI_IER_RIE)  != RESET))
  {
    SWPMI_ReceiveData_Callback();
  }

  /* SWPMI in mode Transmitter ------------------------------------------------*/
  if(((regisr & LL_SWPMI_ISR_TXE) != RESET) && ((regier & LL_SWPMI_IER_TIE) != RESET))
  {
    /* New payload data can be transmitted */
    /* TXE flag is cleared automatically when the software is writing to the SWPMI_TDR 
       register */
    SWPMI_TransmitData_Callback();
  }

  /* SWPMI in mode Transmitter (Transmit buffer empty) ------------------------*/
  if(((regisr & LL_SWPMI_ISR_TXBEF) != RESET) && ((regier & LL_SWPMI_IER_TXBEIE) != RESET))
  {
    /* Clear the SWPMI Transmit buffer empty Flag */
    LL_SWPMI_ClearFlag_TXBE(SWPMI1);
    SWPMI_TransmitBufferEmpty_Callback();
  }

  /* Both Transmission and reception complete ---------------------------------*/
  if(((regisr & LL_SWPMI_ISR_TCF) != RESET) && ((regier & LL_SWPMI_IER_TCIE) != RESET))
  {
    LL_SWPMI_ClearFlag_TC(SWPMI1);
    SWPMI_EndTransfer_Callback();
  }
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
