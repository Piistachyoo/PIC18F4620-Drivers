/* 
 * File:   hal_ccp1.h
 * Author: omarm
 *
 * Created on May 10, 2023, 5:37 PM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/* Section : Includes */
#include "../compiler.h"
#include "../device_config.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "ccp1_cfg.h"

/* Section : Macro Declarations */
#define CCP1_MODULE_DISABLE         0x00
#define CCP1_CAPTURE_MODE_1_FALLING_EDGE    ((uint8)0x04)
#define CCP1_CAPTURE_MODE_1_RISING_EDGE     ((uint8)0x05)
#define CCP1_CAPTURE_MODE_4_FALLING_EDGE    ((uint8)0x06)
#define CCP1_CAPTURE_MODE_16_FALLING_EDGE   ((uint8)0x07)
#define CCP1_COMPARE_MODE_SET_PIN_LOW       ((uint8)0x08)
#define CCP1_COMPARE_MODE_SET_PIN_HIGH      ((uint8)0x09)
#define CCP1_COMPARE_MODE_TOGGLE_ON_MATCH   ((uint8)0x02)
#define CCP1_COMPARE_MODE_GEN_SW_INTERRUPT  ((uint8)0x0A)
#define CCP1_COMPARE_MODE_GEN_EVENT         ((uint8)0x0B)
#define CCP1_PWM_MODE                       ((uint8)0x0C)

#define CCP1_CAPTURE_NOT_READY              0x00
#define CCP1_CAPTURE_READY                  0x01

#define CCP1_COMPARE_NOT_READY              0x00
#define CCP1_COMPARE_READY                  0x01

/* Section : Macro Functions Declarations */
#define CCP1_SET_MODE(_CONFIG)              (CCP1CONbits.CCP1M = _CONFIG)



/* Section : Data Type Declarations */
typedef union{
    struct{
        uint8 ccpr1_low;
        uint8 ccpr1_high;
    };
    struct{
        uint16 ccpr1_16bit;
    };
}CCP1_REG_t;

typedef enum{
    CCP1_CAPTURE_MODE_SELECTED = 0,
    CCP1_COMPARE_MODE_SELECTED,
    CCP1_PWM_MODE_SELECTED
}ccp1_mode_t;

typedef struct{
    ccp1_mode_t ccp1_mode;
    uint8 ccp1_mode_variant;
    pin_config_t ccp1_pin;
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* CCP1_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    

#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED
    uint32 PWM_Frequency;
    uint8 timer2_postscaler_value :4;
    uint8 timer2_prescaler_value  :2;
#endif
}ccp1_t;

/* Section : Function Declarations */
Std_ReturnType CCP1_Init(const ccp1_t *_ccp_obj);
Std_ReturnType CCP1_DeInit(const ccp1_t *_ccp_obj);
 
#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELECTED
Std_ReturnType CCP1_IsCapturedDataReady(uint8 *_capture_status);
Std_ReturnType CCP1_Capture_Mode_Read_Value(uint16 *_capture_value);
#endif

#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_COMPARE_MODE_SELECTED
Std_ReturnType CCP1_IsCompareComplete(uint8 *_compare_status);
Std_ReturnType CCP1_Compare_Mode_Set_Value(uint16 _compare_value);
#endif

#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED
Std_ReturnType CCP1_PWM1_Set_Duty(const uint8 _duty);
Std_ReturnType CCP1_PWM1_Start(void);
Std_ReturnType CCP1_PWM1_Stop(void);
#endif

#endif	/* HAL_CCP1_H */

