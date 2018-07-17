/**
  ******************************************************************************
  * @file    GuitarTuner_glo.h
  * @author  MCD Application Team   
  * @brief   This file contains GuitarTuner module definitions to export
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
#ifndef GUITAR_TUNER_GLO_H
#define GUITAR_TUNER_GLO_H

/* Includes ------------------------------------------------------------------*/


/*============================================================================*/
/*      C O D E   D E F I N I T I O N S                                       */
/*============================================================================*/

#define GT_DISABLE                  (0)
#define GT_ENABLE                   (1)

/* Number of strings supported */
#define GT_NB_STRINGS               (6)     // 6 strings guitar only

/* Supported Tuning types */
#define GT_TYPE_STANDARD            (0)     // Standard EADGBE tuning
#define GT_TYPE_ALL_FOURTHS_TUNING  (1)     // Each string is the exact fourth of previous string
#define GT_TYPE_DROP_D              (2)     // For Rock/Metal tuning
#define GT_TYPE_OPEN_E              (3)     // For Folk/Blues tuning
#define GT_TYPE_VASTOPOL            (4)     // For Blues tuning
#define GT_TYPE_DADGAD              (5)     // For Celtic/Oriental tuning
#define GT_TYPE_MAX                 (6)     // Maximum number of supported tuning types

/* Supported Tuning Modes */
#define GT_MODE_UNKNOWN_STRING      (0)
#define GT_MODE_STRING_1            (1)
#define GT_MODE_STRING_2            (2)
#define GT_MODE_STRING_3            (3)
#define GT_MODE_STRING_4            (4)
#define GT_MODE_STRING_5            (5)
#define GT_MODE_STRING_6            (6)
#define GT_MODE_ALL_STRINGS         (7)
#define GT_MODE_MAX                 (8)

/* Returned output */
#define GT_OUTPUT_STRING_WELL_TUNED                                 (0)
#define GT_OUTPUT_STRING_NOT_TUNED                                  (1)
#define GT_OUTPUT_STRING_NOT_STRAINED_ENOUGH                        (2)
#define GT_OUTPUT_STRING_NOT_STRAINED_ENOUGH_CLOSE_TO_FINE_TUNE     (3)
#define GT_OUTPUT_STRING_TOO_STRAINED                               (4)
#define GT_OUTPUT_STRING_TOO_STRAINED_CLOSE_TO_FINE_TUNE            (5)
#define GT_OUTPUT_STRING_TUNING_NEARLY_COMPLETED                    (6)
#define GT_OUTPUT_FUNDAMENTAL_NOT_FOUND                             (7)



/*============================================================================*/
/*      E R R O R   V A L U E S                                               */
/*============================================================================*/
#define GT_ERROR_NONE                           (0)
#define GT_UNSUPPORTED_NUMBER_OF_BYTEPERSAMPLE  (-1)
#define GT_UNSUPPORTED_NUMBER_OF_CHANNELS       (-2)
#define GT_UNSUPPORTED_TYPE                     (-3)
#define GT_UNSUPPORTED_MODE                     (-4)
#define GT_UNSUPPORTED_FRAME_SIZE               (-5)
#define GT_FFT_ERROR                            (-6)
#define GT_BAD_HW                               (-7)


/*============================================================================*/
/*      D Y N A M I C   P A R A M E T E R S   S T R U C T U R E               */
/*============================================================================*/
struct GuitarTuner_dynamic_param {
    int32_t   enable;                               // GT_DISABLE to disable processing, GT_ENABLE to enable or re-enable processing
    float32_t expected_frequency[GT_NB_STRINGS];    // Contains frequencies to match for right tuning
    float32_t measured_frequency[GT_NB_STRINGS];    // Contains estimated frequencies
    int16_t   output_estimated[GT_NB_STRINGS];      // Contains algorithm output analysis per string: see GT_OUTPUT_XXX messages above
    int16_t   general_output_estimated;             // Contains algorithm general output analysis : see GT_OUTPUT_XXX messages above
};
typedef struct GuitarTuner_dynamic_param GuitarTuner_dynamic_param_t;


/*============================================================================*/
/*      S T A T I C   P A R A M E T E R S   S T R U C T U R E                 */
/*============================================================================*/
struct GuitarTuner_static_param {
    int16_t   tuning_type;                          // can be one of GT_TYPE_XXX supported tuning types
    int16_t   tuning_mode;                          // can be one of GT_MODE_XXX supported tuning modes
};
typedef struct GuitarTuner_static_param GuitarTuner_static_param_t;


/*============================================================================*/
/*      I N T E R N A L   S T A T I C   M E M O R Y                           */
/*============================================================================*/
extern const uint32_t GuitarTuner_dynamic_mem_size;


/*============================================================================*/
/*      I N T E R N A L   D Y N A M I C   M E M O R Y                         */
/*============================================================================*/
extern const uint32_t GuitarTuner_static_mem_size;


/*============================================================================*/
/*      I N T E R F A C E S   D E C L A R A T I O N S                         */
/*============================================================================*/
/* GuitarTuner_reset() : initializes static memory, states machines, ... */
extern int32_t GuitarTuner_reset(void *static_mem_ptr, void *dynamic_mem_ptr);
/* GuitarTuner_setConfig() : use to change dynamically some parameters */
extern int32_t GuitarTuner_setConfig(GuitarTuner_dynamic_param_t *input_dynamic_param_ptr, void *static_mem_ptr);
/* GuitarTuner_getConfig() : use to get values of dynamic parameters */
extern int32_t GuitarTuner_getConfig(GuitarTuner_dynamic_param_t *input_dynamic_param_ptr, void *static_mem_ptr);
/* GuitarTuner_setParam() : use to set parameters that won't change during processing */
extern int32_t GuitarTuner_setParam(GuitarTuner_static_param_t *input_static_param_ptr, void *static_mem_ptr);
/* GuitarTuner_getParam() : use to get values of static parameters */
extern int32_t GuitarTuner_getParam(GuitarTuner_static_param_t *input_static_param_ptr, void *static_mem_ptr);
/* GuitarTuner_process() : this is the main processing routine */
extern int32_t GuitarTuner_process(buffer_t *input_buffer_ptr, buffer_t *output_buffer_ptr, void *static_mem_ptr);


#endif  /* GUITAR_TUNER_GLO_H */

/******************** COPYRIGHT(c) 2017 STMicroelectronics *****END OF FILE****/
