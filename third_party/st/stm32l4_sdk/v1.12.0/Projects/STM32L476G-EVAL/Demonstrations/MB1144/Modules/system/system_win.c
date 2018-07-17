/**
  ******************************************************************************
  * @file    system_win.c
  * @author  MCD Application Team   
  * @brief   System information functions
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
#include "dialog.h"
#include "k_module.h"
#include "k_rtc.h"
#include "system_res.c"


/** @addtogroup SYSTEM_MODULE
  * @{
  */

/** @defgroup SYSTEM
  * @brief system routines 
  * @{
  */


/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void Startup(WM_HWIN hWin, uint16_t xpos, uint16_t ypos);

/* Private typedef -----------------------------------------------------------*/
K_ModuleItem_Typedef  system_info =
{
  4,
  "System",
  &bminfo,
  Startup,
  NULL,
}
;




/* Private defines -----------------------------------------------------------*/
#define ID_FRAMEWIN_INFO        (GUI_ID_USER + 0x01)
#define ID_TEXT_BOARD           (GUI_ID_USER + 0x02)
#define ID_TEXT_CORE            (GUI_ID_USER + 0x03)
#define ID_TEXT_CPU             (GUI_ID_USER + 0x04)
#define ID_TEXT_VERSION         (GUI_ID_USER + 0x05)
#define ID_TEXT_COPYRIGHT       (GUI_ID_USER + 0x06)
#define ID_MULTIPAGE            (GUI_ID_USER + 0x07)
#define ID_IMAGE_LOGO           (GUI_ID_USER + 0x08)    

#define ID_TEXT_WARNING               (GUI_ID_USER + 0x15)
#define ID_SPINBOX_HOUR               (GUI_ID_USER + 0x16)
#define ID_TEXT_0                     (GUI_ID_USER + 0x17)
#define ID_TEXT_1                     (GUI_ID_USER + 0x18)
#define ID_SPINBOX_MINUTE             (GUI_ID_USER + 0x19)
#define ID_BUTTON_APPLYSETTINGS       (GUI_ID_USER + 0x1A)
#define ID_BUTTON_1                   (GUI_ID_USER + 0x1B)
#define ID_TEXT_2                     (GUI_ID_USER + 0x1C)
#define ID_CALENDAR                   (GUI_ID_USER + 0x1D)
#define ID_SPINBOX_SEC                (GUI_ID_USER + 0x1E)

#define  PI                                3.14
#define  AA_FACTOR                         3

#define X0                                 49
#define Y0                                 48

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Dialog resource using a WINDOW widget*/
static const GUI_WIDGET_CREATE_INFO _aDialog[] = 
{
  
  { FRAMEWIN_CreateIndirect, "System", ID_FRAMEWIN_INFO, 0, 0, 320, 214, 0, 0x64, 0 },
  { MULTIPAGE_CreateIndirect, "Multipage", ID_MULTIPAGE, 10, 10, 300, 180, 0, 0x0, 0 },  
};

static const GUI_WIDGET_CREATE_INFO _aDialogSystemInformation[] = {
  { WINDOW_CreateIndirect, "System Information",                                     0,   0,   0,   300, 180, FRAMEWIN_CF_MOVEABLE },
  { TEXT_CreateIndirect, "Board : STM32L476G-EVAL", ID_TEXT_BOARD,                         15,  15,  200, 20,  0,   0x0, 0 },
  { TEXT_CreateIndirect, "Core: STM32L476ZG", ID_TEXT_CORE,                      15,  35,  200, 20,  0,   0x0, 0 },
  { TEXT_CreateIndirect, "CPU Speed : 80MHz", ID_TEXT_CPU,                          15,  55,  200, 20,  0,   0x0, 0 },
  { TEXT_CreateIndirect, "Demo Version : 1.0.4", ID_TEXT_VERSION,                  15,  75,  280, 20,  0,   0x0, 0 },
  { IMAGE_CreateIndirect, "Image", ID_IMAGE_LOGO,                                    90,  95,  40,  20,  0,   0,   0 },
  { TEXT_CreateIndirect, "Copyright (c) STMicroelectronics 2016", ID_TEXT_COPYRIGHT, 15,  125, 200, 20,  0,   0x0, 0 },  
};

static const GUI_WIDGET_CREATE_INFO _aDialogClockSettings[] = {
  { WINDOW_CreateIndirect, "Clock Settings",                          0, 0,   0, 300, 180, FRAMEWIN_CF_MOVEABLE },
  { SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_HOUR,               160, 87, 37, 30, 0, 0x0, 0 },  
  { SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_MINUTE,             200, 87, 36, 30, 0, 0x0, 0 },
  { SPINBOX_CreateIndirect, "Spinbox", ID_SPINBOX_SEC,                239, 87, 37, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Apply settings", ID_BUTTON_APPLYSETTINGS, 160, 122, 116, 37, 0, 0x0, 0 },
};

static const GUI_POINT aPoints[3][4] = {
   
  /* Hour Needle */
  {{ 0 * AA_FACTOR, 2 * AA_FACTOR},
   {-1 * AA_FACTOR,-4 * AA_FACTOR},
   { 0 * AA_FACTOR,-6 * AA_FACTOR},
   { 1 * AA_FACTOR,-4 * AA_FACTOR}},

  /* Min Needle */
  {{ 0 * AA_FACTOR, 2 * AA_FACTOR},
   {-1 * AA_FACTOR,-2 * AA_FACTOR},
   { 0 * AA_FACTOR,-8 * AA_FACTOR},
   { 1 * AA_FACTOR,-2 * AA_FACTOR}},
   /* Sec Needle */
  {{0 * AA_FACTOR, 1 * AA_FACTOR},
   { 1 * AA_FACTOR, 1 * AA_FACTOR},
   { 1 * AA_FACTOR,-34 * AA_FACTOR},
   {0 * AA_FACTOR,-34 * AA_FACTOR}},
};


GUI_POINT aPointsDest[3][4];

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Draw Needle
  * @param  index: Needle index  
  * @param  x0:    x position
  * @param  y0:    y position      
  * @retval None
  */
static void DrawNeedle(uint32_t index, uint16_t x0, uint16_t y0) 
{
  /* draw Needles */
  if(index == 2)
  {
    GUI_SetColor(GUI_RED);
    GUI_AA_FillPolygon(aPointsDest[index], 4, AA_FACTOR * x0, AA_FACTOR * y0);
  }
  else 
  {
    GUI_SetColor(GUI_LIGHTBLUE);
    GUI_AA_FillPolygon(aPointsDest[index], 4, AA_FACTOR * x0, AA_FACTOR * y0);
  }
}

/**
  * @brief  Update clock
  * @param  x0:   x position
  * @param  y0:   y position
  * @param  hour: updated hour
  * @param  min:  updated minute
  * @param  sec:  updated second      
  * @retval None
  */
static void GUI_UpdateClock (uint16_t x0, uint16_t y0, uint8_t hour, uint8_t min, uint8_t sec)
{
  int8_t i = 0;
  int32_t SinHQ, CosHQ ,a = 0;
  uint16_t xPos, yPos;
    
  GUI_AA_EnableHiRes();
  GUI_AA_SetFactor(AA_FACTOR);
  
  GUI_SetColor(GUI_LIGHTGRAY);   
  GUI_AA_DrawArc(AA_FACTOR * x0, AA_FACTOR * y0, AA_FACTOR * 39, AA_FACTOR * 39, 0, 360);  
  GUI_SetColor(GUI_GRAY);  
  GUI_AA_DrawArc(AA_FACTOR * x0, AA_FACTOR * y0, AA_FACTOR * 40, AA_FACTOR * 40, 0, 360);  
  GUI_SetColor(GUI_WHITE);  
  GUI_AA_FillCircle(AA_FACTOR * x0, AA_FACTOR * y0, AA_FACTOR * 38); 
  GUI_SetBkColor(GUI_TRANSPARENT);

  GUI_SetBkColor(GUI_WHITE);
  GUI_SetColor(GUI_GRAY);  
  GUI_DispStringAt("12", x0 - 5, y0 - 38 + 5);
  GUI_DispStringAt( "6", x0 - 2, y0 + 38 - 13);
  GUI_DispStringAt( "9", x0 - 38 + 5, y0 - 5);
  GUI_DispStringAt( "3", x0 + 38 - 10, y0 - 3);
  
  for (i = 0; i <= 12; i++) 
  {
    a = i * 30000;
    SinHQ = GUI__SinHQ(a);
    CosHQ = GUI__CosHQ(a);

    xPos = x0 + ((36 * CosHQ) >> 16);
    yPos = y0 - ((36 * SinHQ) >> 16);
    
    GUI_AA_FillCircle(AA_FACTOR * xPos, AA_FACTOR * yPos, AA_FACTOR * 1); 
  }
  
  GUI_MagnifyPolygon(aPointsDest[0], aPoints[0], 4, 4);
  GUI_RotatePolygon(aPointsDest[0], aPointsDest[0], 4, - 2 * PI * (float)((float)hour + (float)min /60) / 12);    
  DrawNeedle(0, x0, y0);
  
  GUI_MagnifyPolygon(aPointsDest[1], aPoints[1], 4, 4);
  GUI_RotatePolygon(aPointsDest[1], aPointsDest[1], 4, - 2 * PI * (float)((float)min + (float)sec / 60) / 60);
  DrawNeedle(1, x0, y0);  
  
  GUI_MagnifyPolygon(aPointsDest[2], aPoints[2], 4, 1);
  GUI_RotatePolygon(aPointsDest[2], aPointsDest[2], 4, - 2 * PI * sec / 60);    
  DrawNeedle(2, x0, y0); 
  GUI_AA_DisableHiRes();
}

/**
  * @brief  callback for System Information
  * @param  pMsg: Pointer to Date structure
  * @retval None
  */
static void _cbSystemInformation(WM_MESSAGE * pMsg) 
{
  WM_HWIN hItem;
  hItem = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:

    /* Initialization of 'Board : STM32L476G' */
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_BOARD);
    TEXT_SetFont(hItem, GUI_FONT_13HB_ASCII);
    TEXT_SetTextColor(hItem, GUI_DARKGRAY);

    /* Initialization of 'Core: STM32L4 Series' */
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CORE);
    TEXT_SetFont(hItem, GUI_FONT_13HB_ASCII);
    TEXT_SetTextColor(hItem, GUI_DARKGRAY);

    /* Initialization of 'CPU Speed : 80MHz' */
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CPU);
    TEXT_SetFont(hItem, GUI_FONT_13HB_ASCII);
    TEXT_SetTextColor(hItem, GUI_DARKGRAY);

    /* Initialization of 'Firmware Version : 1.0' */
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_VERSION);
    TEXT_SetFont(hItem, GUI_FONT_13HB_ASCII);
    TEXT_SetTextColor(hItem, GUI_DARKGRAY);

    /* ST Copyright */
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_COPYRIGHT);
    TEXT_SetFont(hItem, GUI_FONT_10_ASCII);
    TEXT_SetTextColor(hItem, GUI_DARKGRAY);
    
    /* Set ST Logo */
    hItem = WM_GetDialogItem(pMsg->hWin, ID_IMAGE_LOGO);
    IMAGE_SetBitmap(hItem, &bmSTLogo40x20);
    
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}


/**
  * @brief  callback for Clock Settings
  * @param  pMsg: Pointer to Date structure
  * @retval None
  */

static void _cbClockSettings(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int Id, NCode;  
  RTC_DateTypeDef          Date;  
  RTC_TimeTypeDef          Time; 
  static WM_HTIMER hTimerTime;
  static uint8_t DisableAutoRefresh = 0;
  static CALENDAR_DATE  hDate;
  
  hItem = pMsg->hWin;
  switch (pMsg->MsgId) {
    
  case WM_TIMER:
    WM_InvalidateWindow(pMsg->hWin);
    WM_RestartTimer(pMsg->Data.v, 1000);
    break; 
    
  case WM_DELETE:
    WM_DeleteTimer(hTimerTime);
    DisableAutoRefresh = 0;
    break;
    
  case WM_INIT_DIALOG:
    
    k_GetDate(&Date);  
    
    hTimerTime = WM_CreateTimer(pMsg->hWin, 0, 1000, 0); 
    CALENDAR_Create(pMsg->hWin,12, 12, 2016 + Date.Year, Date.Month, Date.Date, 2, ID_CALENDAR, WM_CF_SHOW);
    CALENDAR_SetDefaultFont(CALENDAR_FI_CONTENT,GUI_FONT_10_1 );
    CALENDAR_SetDefaultFont(CALENDAR_FI_HEADER, GUI_FONT_10_1) ;
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_HOUR);
    SPINBOX_SetRange(hItem, 0, 23);
      
    hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_MINUTE);
    SPINBOX_SetRange(hItem, 0, 59);
      
    hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_SEC);
    SPINBOX_SetRange(hItem, 0, 59);
      
    break;
    
  case WM_PAINT:
    if(DisableAutoRefresh == 0)
    {
      k_GetTime(&Time);   
      GUI_UpdateClock (220, 42, Time.Hours, Time.Minutes, Time.Seconds);
      
      hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_HOUR);
      SPINBOX_SetValue(hItem, Time.Hours);
      
      hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_MINUTE);
      SPINBOX_SetValue(hItem, Time.Minutes);
      
      hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_SEC);
      SPINBOX_SetValue(hItem, Time.Seconds); 
    }
    else
    {
      hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_HOUR);
      Time.Hours = SPINBOX_GetValue(hItem);
      
      hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_MINUTE);
      Time.Minutes = SPINBOX_GetValue(hItem); 
      
      hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_SEC);
      Time.Seconds = SPINBOX_GetValue(hItem); 
      
      GUI_UpdateClock (220, 42, Time.Hours, Time.Minutes, Time.Seconds);      
    }
    break;
    
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
    NCode = pMsg->Data.v;               /* Notification code */
    switch (NCode) {
      
    case WM_NOTIFICATION_CLICKED:      /* React only if released */
      switch (Id) {
      case ID_SPINBOX_HOUR:
      case ID_SPINBOX_MINUTE:
      case ID_SPINBOX_SEC:
        if(DisableAutoRefresh == 0)
        {         
          DisableAutoRefresh = 1;
        } 
        break;        
      }
      break;
      
    case WM_NOTIFICATION_RELEASED: 
      switch (Id) {
      case ID_BUTTON_APPLYSETTINGS:
        hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_SEC);
        Time.Seconds = SPINBOX_GetValue(hItem);
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_MINUTE);
        Time.Minutes = SPINBOX_GetValue(hItem); 
        
        hItem = WM_GetDialogItem(pMsg->hWin, ID_SPINBOX_HOUR);
        Time.Hours = SPINBOX_GetValue(hItem); 
        
        k_SetTime(&Time);
        hItem = WM_GetDialogItem(pMsg->hWin, ID_CALENDAR);
        CALENDAR_GetSel (hItem, &hDate);
        
        if((hDate.Day > 0) && (hDate.Day <= 31) && 
           (hDate.Month > 0)&& (hDate.Month <= 12) && 
             (hDate.Year >= 1900))
        {
          Date.Date = hDate.Day;
          Date.Month = hDate.Month;
          Date.Year = hDate.Year - 2016;
          Date.WeekDay = 0;
          k_SetDate(&Date);
        }
        DisableAutoRefresh = 0;
        break;  
      }
      break;
    }      
    break;    
  default:
    WM_DefaultProc(pMsg);
  }
}

/**
  * @brief  Callback routine of the dialog
  * @param  pMsg: pointer to data structure of type WM_MESSAGE
  * @retval None
  */

static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem, hDialog;

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:

    /* Initialization of 'System Information'  */
    hItem = pMsg->hWin;
    FRAMEWIN_AddCloseButton(hItem, FRAMEWIN_BUTTON_RIGHT, 0);    
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIPAGE);
    

   /* Create and attache the MULTIPAGE dialog windows */
    hDialog = GUI_CreateDialogBox(_aDialogSystemInformation, 
                                  GUI_COUNTOF(_aDialogSystemInformation), 
                                  &_cbSystemInformation, WM_UNATTACHED, 0, 0);
    MULTIPAGE_AddPage(hItem, hDialog, "System Information");
    
    hDialog = GUI_CreateDialogBox(_aDialogClockSettings, 
                                  GUI_COUNTOF(_aDialogClockSettings), 
                                  &_cbClockSettings, WM_UNATTACHED, 0, 0);
    MULTIPAGE_AddPage(hItem, hDialog, "Clock Settings");
    
    MULTIPAGE_SelectPage(hItem, 0);

    break;   
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/**
  * @brief  System info window Startup
  * @param  hWin: pointer to the parent handle.
  * @param  xpos: X position 
  * @param  ypos: Y position
  * @retval None
  */
static void Startup(WM_HWIN hWin, uint16_t xpos, uint16_t ypos)
{
  GUI_CreateDialogBox(_aDialog, GUI_COUNTOF(_aDialog), _cbDialog, hWin, xpos, ypos);
}
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

