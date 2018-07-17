/**
  ******************************************************************************
  * @file    main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif
   
/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "stm32l4xx_it.h"

/* Discovery includes component */
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_audio.h"
#include "stm32l476g_discovery_compass.h"
#include "stm32l476g_discovery_glass_lcd.h"
#include "stm32l476g_discovery_idd.h"
#include "stm32l476g_discovery_qspi.h"
#include "stm32l476g_discovery_gyroscope.h"
   
/* CMSIS OS includes component */
#include "cmsis_os.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  ULP_STOP2    = 0x00,
  ULP_STANDBY  = 0x01,
  ULP_OFF      = 0x02
} ULPMode;

typedef enum
{
  HWINIT_ERROR    = 0x00,
  HWINIT_STARTUP  = 0x01,
  HWINIT_IDD      = 0x02,
  HWINIT_STOP2    = 0x03,
  HWINIT_STANDBY  = 0x04
} HwInitMode;

typedef enum
{
  BACKUP_IDD        = 0x00,  /* IDD application backup data     */
  BACKUP_COMPASS    = 0x01,  /* Compass application backup data */
  BACKUP_SETTINGS   = 0x02   /* Kernel settings backup data     */
} DemoBackupId;

typedef struct
{
  uint32_t mode;  
} IddBackupData_TypeDef;

typedef struct
{
  uint32_t calibration;
  int32_t  xmax;
  int32_t  xmin;
  int32_t  ymax;
  int32_t  ymin;
  int32_t  zmax;
  int32_t  zmin;
} CompassBackupData_TypeDef;

typedef struct
{
  uint32_t lpmode;
} SettingsBackupData_TypeDef;

typedef struct
{
  /* IDD application */
  IddBackupData_TypeDef      idd;
  /* Compass application */
  CompassBackupData_TypeDef  compass;
  /* Global settings */
  SettingsBackupData_TypeDef settings;
} DemoBackupData_TypeDef;


/* Exported variables --------------------------------------------------------*/
extern SupplyMode_TypeDef PowerSupplyMode;
extern FlagStatus         DemoDebugMode;
extern FlagStatus         DemoEnterLowPower;
extern __IO FlagStatus    DemoStarted;
extern osMutexId          DemoLowPowerMutex;
extern ULPMode            DemoULPMode;
extern uint32_t           DemoMinIdleTime;
extern void              (*EnterLowPowerMode)(void);
extern void              (*ExitLowPowerMode)(void);


/* Exported constants --------------------------------------------------------*/
#define DEMOBACKUP_AREA_ADDRESS 0x08080000   /* Backup data in first section of Bank2 */

#define AUDIO_DEFAULT_VOLUME 70

/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void      SystemClock_Config(void);
void      SystemClock_BatterySupply_Config(void);
void      SystemClock_BatterySupply_ClockIncrease(void);
void      SystemClock_BatterySupply_ClockDecrease(void);
void      SystemLowClock_Config(void);
void      SystemHardwareInit(HwInitMode Mode);
void      SystemHardwareDeInit(HwInitMode Mode);
void      SystemPeripheralClockEnable(void);
void      SystemPeripheralClockDisable(void);
uint8_t   SystemStartupStatus(void);
void      SystemComponentsLowPower(void);
uint32_t  SystemBackupRead(DemoBackupId Id, void *Data);
void      SystemBackupWrite(DemoBackupId Id, void *Data);
void      EnterStop2Mode(void);
void      ExitStop2Mode(void);
void      EnterStandbyMode(void);
void      Convert_IntegerIntoChar(uint32_t number, uint16_t *p_tab);
void      Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
