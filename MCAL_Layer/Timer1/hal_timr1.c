/* 
 * File:   hal_timr1.h
 * Author: omarm
 *
 * Created on May 8, 2023, 5:02 PM
 */

#include "hal_timr1.h"

static inline void Timer1_Mode_Select(const timer1_t *_timer);

static uint16 TIMER1_Preload = 0;

#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TMR1_InterruptHandler)(void);
#endif

Std_ReturnType Timer1_Init(const timer1_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        /* Disable timer module */
        TIMER1_MODULE_DISABLE();
        
        /* Prescaler Configuration */\
        TIMER1_PRESCALER_SELECT(_timer->prescaler_value);

        /* Configure Timer Mode */
        Timer1_Mode_Select(_timer);
        
        /* Set Preload Value */
        TMR1H = (_timer->timer1_preload_value) >> 8;
        TMR1L = (uint8)(_timer->timer1_preload_value);
        TIMER1_Preload = _timer->timer1_preload_value;
                                     
        /* Interrupt Configurations */
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_FLAG_CLEAR();
        TMR1_InterruptHandler = _timer->Timer1_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(_timer->priority == INTERRUPT_HIGH_PRIORITY){ TIMER1_HighPrioritySet(); }
        else if(_timer->priority == INTERRUPT_LOW_PRIORITY){ TIMER1_LowPrioritySet(); }
        else{ /* Do Nothing */ }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        TIMER1_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer1_DeInit(const timer1_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        TIMER1_MODULE_DISABLE();
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_DISABLE();
#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 _value){
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        TMR1H = (_value) >> 8;
        TMR1L = (uint8)(_value);
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16 *_value){
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        *_value = (uint16)(TMR1L + (TMR1H << 8));
        ret = E_OK;
    }
    return ret;
}

void TMR1_Int_ISR(void){
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    TIMER1_FLAG_CLEAR();
    TMR1H = (TIMER1_Preload) >> 8;
    TMR1L = (uint8)(TIMER1_Preload);
    if(TMR1_InterruptHandler){
        TMR1_InterruptHandler();
    }
#endif
}

static inline void Timer1_Mode_Select(const timer1_t *_timer){
    if(_timer->timer1_mode == TIMER1_TIMER_MODE){
        TIMER1_TIMER_MODE_ENABLE();
    }
    else if(_timer->timer1_mode == TIMER1_COUNTER_MODE){
        TIMER1_COUNTER_MODE_ENABLE();
        if(_timer->timer1_counter_mode == TIMER1_ASYNC_COUNTER_MODE){
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(_timer->timer1_counter_mode == TIMER1_SYNC_COUNTER_MODE){
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
        }
        else{ /* Do Nothing */ }
    }
    else{ /* Do Nothing */ }
}
