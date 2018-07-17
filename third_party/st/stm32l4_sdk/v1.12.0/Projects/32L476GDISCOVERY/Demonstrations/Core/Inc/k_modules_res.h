/**
  ******************************************************************************
  * @file    k_modules_res.h
  * @author  MCD Application Team
  * @brief   Header for k_modules_res.c file
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
#ifndef __K_MODULE_RES_H
#define __K_MODULE_RES_H

#ifdef __cplusplus
 extern "C" {
#endif
 
/* Includes ------------------------------------------------------------------*/   
#include <stdlib.h>
#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

/* Exported types ------------------------------------------------------------*/   
extern GUI_CONST_STORAGE GUI_BITMAP bmrecord_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmrecord_not_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplay_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplay_not_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmnext_not_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmnext_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmprevious_not_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmprevious_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmstop_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmstop_not_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmadd_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmadd_not_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplaylist_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmplaylist_not_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmopen_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmopen_not_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmclose_not_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmclose_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmhide_not_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmhide_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmpause_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmpause_not_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmpause1_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmpause1_not_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmspeaker_not_mute;
extern GUI_CONST_STORAGE GUI_BITMAP bmspeaker_mute;
extern GUI_CONST_STORAGE GUI_BITMAP bmrepeat1;
extern GUI_CONST_STORAGE GUI_BITMAP bmrepeat_all;
extern GUI_CONST_STORAGE GUI_BITMAP bmrepeat_off;
extern GUI_CONST_STORAGE GUI_BITMAP bmwindowfullscreen;
extern GUI_CONST_STORAGE GUI_BITMAP bmwindownofullscreen;
extern GUI_CONST_STORAGE GUI_BITMAP bmsettings_button_not_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmsettings_button_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmstop2_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmstop2_not_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmstart_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmstart_not_pressed;
extern GUI_CONST_STORAGE GUI_BITMAP bmok32;
extern GUI_CONST_STORAGE GUI_BITMAP bmDelete32;

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void DrawRect3D(int x0, int y0, int width, int height);

#ifdef __cplusplus
}
#endif

#endif /*__K_MODULE_RES_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
