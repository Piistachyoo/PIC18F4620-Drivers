/* 
 * File:   hal_ccp1.c
 * Author: omarm
 *
 * Created on May 10, 2023, 5:37 PM
 */

#include "hal_ccp1.h"

#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*CCP1_Interrupt_Handler)(void) = NULL;
#endif

Std_ReturnType CCP1_Init(const ccp1_t *_ccp_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(_ccp_obj != NULL){
        /* CCP1 Module Disable */
        CCP1_SET_MODE(CCP1_MODULE_DISABLE);
        
        /* CCP1 Module Initialization */
        if(_ccp_obj->ccp1_mode == CCP1_CAPTURE_MODE_SELECTED){
            switch(_ccp_obj->ccp1_mode_variant){
                case CCP1_CAPTURE_MODE_1_FALLING_EDGE:
                    CCP1_SET_MODE(CCP1_CAPTURE_MODE_1_FALLING_EDGE);
                    ret = E_OK;
                    break;
                case CCP1_CAPTURE_MODE_1_RISING_EDGE:
                    CCP1_SET_MODE(CCP1_CAPTURE_MODE_1_RISING_EDGE);
                    ret = E_OK;
                    break;
                case CCP1_CAPTURE_MODE_4_FALLING_EDGE:
                    CCP1_SET_MODE(CCP1_CAPTURE_MODE_4_FALLING_EDGE);
                    ret = E_OK;
                    break;
                case CCP1_CAPTURE_MODE_16_FALLING_EDGE:
                    CCP1_SET_MODE(CCP1_CAPTURE_MODE_16_FALLING_EDGE);
                    ret = E_OK;
                    break;
                default: ret = E_NOT_OK; break;
            }
        }
        else if(_ccp_obj->ccp1_mode == CCP1_COMPARE_MODE_SELECTED){
            switch(_ccp_obj->ccp1_mode_variant){
                case CCP1_COMPARE_MODE_SET_PIN_LOW:
                    CCP1_SET_MODE(CCP1_COMPARE_MODE_SET_PIN_LOW);
                    ret = E_OK;
                    break;
                case CCP1_COMPARE_MODE_SET_PIN_HIGH:
                    CCP1_SET_MODE(CCP1_COMPARE_MODE_SET_PIN_HIGH);
                    ret = E_OK;
                    break;
                case CCP1_COMPARE_MODE_TOGGLE_ON_MATCH:
                    CCP1_SET_MODE(CCP1_COMPARE_MODE_TOGGLE_ON_MATCH);
                    ret = E_OK;
                    break;
                case CCP1_COMPARE_MODE_GEN_SW_INTERRUPT:
                    CCP1_SET_MODE(CCP1_COMPARE_MODE_GEN_SW_INTERRUPT);
                    ret = E_OK;
                    break;
                case CCP1_COMPARE_MODE_GEN_EVENT:
                    CCP1_SET_MODE(CCP1_COMPARE_MODE_GEN_EVENT);
                    ret = E_OK;
                    break;
                default: ret = E_NOT_OK; break;
            }
        }
        else if(_ccp_obj->ccp1_mode == CCP1_PWM_MODE_SELECTED){
            if(_ccp_obj->ccp1_mode_variant == CCP1_PWM_MODE){
#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED
                CCP1_SET_MODE(CCP1_PWM_MODE);
                PR2 = (uint8)((_XTAL_FREQ / (_ccp_obj->PWM_Frequency * 4.0 * _ccp_obj->timer2_prescaler_value * 
                        _ccp_obj->timer2_postscaler_value)) - 1);
                ret = E_OK;
#endif
            }
            else{ ret = E_NOT_OK; }
        }
        else{ ret = E_NOT_OK; }
        
        /* GPIO Pin Configuration */
        ret = gpio_pin_initialize(&(_ccp_obj->ccp1_pin));
        
        /* Interrupt Configurations */
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_ENABLE();
        CCP1_FLAG_CLEAR();
        CCP1_Interrupt_Handler = _ccp_obj->CCP1_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(_ccp_obj->priority == INTERRUPT_HIGH_PRIORITY){
            CCP1_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(_ccp_obj->priority == INTERRUPT_LOW_PRIORITY){
            CCP1_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable();
        }
        else{ /* Do Nothing */ }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif

    }
    return ret;
}

Std_ReturnType CCP1_DeInit(const ccp1_t *_ccp_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(_ccp_obj != NULL){
        /* CCP1 Module Disable */
        CCP1_SET_MODE(CCP1_MODULE_DISABLE);
        
        /* Disable Interrupt */
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_DISABLE();
#endif
        ret = E_OK;
    }
    return ret;
}

#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELECTED
Std_ReturnType CCP1_IsCapturedDataReady(uint8 *_capture_status){
    Std_ReturnType ret = E_NOT_OK;
    if(_capture_status != NULL){
        if(PIR1bits.CCP1IF == CCP1_CAPTURE_READY){
            *_capture_status = CCP1_CAPTURE_READY;
            CCP1_FLAG_CLEAR();
        }
        else{
            *_capture_status = CCP1_CAPTURE_NOT_READY;
        }
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType CCP1_Capture_Mode_Read_Value(uint16 *_capture_value){
    Std_ReturnType ret = E_NOT_OK;
    CCP1_REG_t capture_temp_value;
    if(_capture_value != NULL){
        capture_temp_value.ccpr1_low = CCPR1L;
        capture_temp_value.ccpr1_high = CCPR1H;
        *_capture_value = capture_temp_value.ccpr1_16bit;
        ret = E_OK;
    }
    return ret;
}

#endif
    
#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_COMPARE_MODE_SELECTED 
Std_ReturnType CCP1_IsCompareComplete(uint8 *_compare_status){
    Std_ReturnType ret = E_NOT_OK;
    if(_compare_status != NULL){
        if(PIR1bits.CCP1IF == CCP1_COMPARE_READY){
            *_compare_status = CCP1_COMPARE_READY;
            CCP1_FLAG_CLEAR();
        }
        else{
            *_compare_status = CCP1_COMPARE_NOT_READY;
        }
    }
        ret = E_OK;
    return ret;
}

Std_ReturnType CCP1_Compare_Mode_Set_Value(uint16 _compare_value){
    Std_ReturnType ret = E_NOT_OK;
    CCP1_REG_t compare_temp_value;
    compare_temp_value.ccpr1_16bit = _compare_value;
    CCPR1L = compare_temp_value.ccpr1_low;
    CCPR1H = compare_temp_value.ccpr1_high;
    ret = E_OK;
    return ret;
}

#endif
    
#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED
Std_ReturnType CCP1_PWM1_Set_Duty(const uint8 _duty){
    Std_ReturnType ret = E_NOT_OK;
    uint16 duty_temp = 0;
    duty_temp = (uint16)(4 * (PR2 + 1) * (_duty / 100.0));
    CCP1CONbits.DC1B = (uint8)(duty_temp & 0x0003);
    CCPR1L = (uint8)(duty_temp >> 2);
    ret = E_OK;
    return ret;
}

Std_ReturnType CCP1_PWM1_Start(void){
    Std_ReturnType ret = E_NOT_OK;
    CCP1_SET_MODE(CCP1_PWM_MODE);
    ret = E_OK;
    return ret;
}

Std_ReturnType CCP1_PWM1_Stop(void){
    Std_ReturnType ret = E_NOT_OK;
    CCP1_SET_MODE(CCP1_MODULE_DISABLE);
    ret = E_OK;
    return ret;
}

#endif
