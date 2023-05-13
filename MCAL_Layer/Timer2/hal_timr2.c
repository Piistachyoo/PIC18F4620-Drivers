/* 
 * File:   hal_timr2.c
 * Author: omarm
 *
 * Created on May 9, 2023, 4:32 PM
 */

#include "hal_timr2.h"

static uint8 TIMER2_Preload = 0;

#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TMR2_InterruptHandler)(void);
#endif

Std_ReturnType Timer2_Init(const timer2_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        TIMER2_MODULE_DISABLE();
        TIMER2_PRESCALER_SELECT(_timer->timer2_prescaler_value);
        TIMER2_POSTSCALER_SELECT(_timer->timer2_postscaler_value);
        TMR2 = _timer->timer2_preload_value;
        TIMER2_Preload = _timer->timer2_preload_value;
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_ENABLE();
        TIMER2_FLAG_CLEAR();
        TMR2_InterruptHandler = _timer->Timer2_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(_timer->priority == INTERRUPT_HIGH_PRIORITY){ TIMER2_HighPrioritySet(); }
        else if(_timer->priority == INTERRUPT_LOW_PRIORITY){ TIMER2_LowPrioritySet(); }
        else{ /* Do Nothing */ }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        TIMER2_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer2_DeInit(const timer2_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        TIMER2_MODULE_DISABLE();
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_DISABLE();
#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _value){
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        TMR2 = _value;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *_value){
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        *_value = TMR2;
        ret = E_OK;
    }
    return ret;
}

void TMR2_Int_ISR(void){
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    TIMER2_FLAG_CLEAR();
    TMR2 = TIMER2_Preload;
    if(TMR2_InterruptHandler){
        TMR2_InterruptHandler();
    }
#endif
}
