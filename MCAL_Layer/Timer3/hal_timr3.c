/* 
 * File:   hal_timr3.c
 * Author: omarm
 *
 * Created on May 9, 2023, 4:32 PM
 */

#include "hal_timr3.h"

static inline void Timer3_Mode_Select(const timer3_t *_timer);

static uint16 TIMER3_Preload = 0;

#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TMR3_InterruptHandler)(void);
#endif

Std_ReturnType Timer3_Init(const timer3_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        /* Disable timer module */
        TIMER3_MODULE_DISABLE();
        
        /* Prescaler Configuration */\
        TIMER3_PRESCALER_SELECT(_timer->timer3_prescaler_value);

        /* Configure Timer Mode */
        Timer3_Mode_Select(_timer);
        
        /* Set Preload Value */
        TMR3H = (_timer->timer3_preload_value) >> 8;
        TMR3L = (uint8)(_timer->timer3_preload_value);
        TIMER3_Preload = _timer->timer3_preload_value;
                                     
        /* Interrupt Configurations */
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_ENABLE();
        TIMER3_FLAG_CLEAR();
        TMR3_InterruptHandler = _timer->Timer3_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(_timer->priority == INTERRUPT_HIGH_PRIORITY){ TIMER3_HighPrioritySet(); }
        else if(_timer->priority == INTERRUPT_LOW_PRIORITY){ TIMER3_LowPrioritySet(); }
        else{ /* Do Nothing */ }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        TIMER3_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer3_DeInit(const timer3_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        TIMER3_MODULE_DISABLE();
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_DISABLE();
#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 _value){
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        TMR3H = (_value) >> 8;
        TMR3L = (uint8)(_value);
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *_value){
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        *_value = (uint16)(TMR3L + (TMR3H << 8));
        ret = E_OK;
    }
    return ret;
}

static inline void Timer3_Mode_Select(const timer3_t *_timer){
    if(_timer->timer3_mode == TIMER3_TIMER_MODE){
        TIMER3_TIMER_MODE_ENABLE();
    }
    else if(_timer->timer3_mode == TIMER3_COUNTER_MODE){
        TIMER3_COUNTER_MODE_ENABLE();
        if(_timer->timer3_counter_mode == TIMER3_ASYNC_COUNTER_MODE){
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(_timer->timer3_counter_mode == TIMER3_SYNC_COUNTER_MODE){
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }
        else{ /* Do Nothing */ }
    }
    else{ /* Do Nothing */ }
}

void TMR3_Int_ISR(void){
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    TIMER3_FLAG_CLEAR();
    TMR3H = (TIMER3_Preload) >> 8;
    TMR3L = (uint8)(TIMER3_Preload);
    if(TMR3_InterruptHandler){
        TMR3_InterruptHandler();
    }
#endif
}
