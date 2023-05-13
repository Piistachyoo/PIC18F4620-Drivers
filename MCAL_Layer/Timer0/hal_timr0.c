/* 
 * File:   hal_timr0.h
 * Author: omarm
 *
 * Created on May 8, 2023, 9:00 AM
 */

#include "hal_timr0.h"

static inline void Timer0_Prescaler_Config(const timer0_t *_timer);
static inline void Timer0_Mode_Select(const timer0_t *_timer);
static inline void Timer0_Register_Size_Config(const timer0_t *_timer);
static inline void Timer0_Interrupt_Config(const timer0_t *_timer);

static uint16 TIMER0_Preload = 0;

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TMR0_InterruptHandler)(void);
#endif

Std_ReturnType Timer0_Init(const timer0_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        /* Disable Timer0 */
        TIMER0_MODULE_DISABLE();
        
        /* Configure Prescaler */
        Timer0_Prescaler_Config(_timer);
        
        /* Configure Timer Mode */
        Timer0_Mode_Select(_timer);
        
        /* Timer0 Register Size Config*/
        Timer0_Register_Size_Config(_timer);
        
        /* Set Preload Value */
        TMR0H = (_timer->timer0_preload_value) >> 8;
        TMR0L = (uint8)(_timer->timer0_preload_value);
        TIMER0_Preload = _timer->timer0_preload_value;
        /* Configure Interrupt */
        Timer0_Interrupt_Config(_timer);
        
        /* Enable Timer0 */
        TIMER0_MODULE_ENABLE();
        
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer0_DeInit(const timer0_t *_timer){
    
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        TIMER0_MODULE_DISABLE();
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_DISABLE();
#endif
    }
    return ret;
}

Std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint16 _value){
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        TMR0H = (_value) >> 8;
        TMR0L = (uint8)(_value);
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer0_Read_Value(const timer0_t *_timer, uint16 *_value){
    Std_ReturnType ret = E_NOT_OK;
    if(_timer != NULL){
        *_value = (uint16)(TMR0L + (TMR0H << 8));
        ret = E_OK;
    }
    return ret;
}

void TMR0_Int_ISR(void){
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    TIMER0_FLAG_CLEAR();
    TMR0H = (TIMER0_Preload) >> 8;
    TMR0L = (uint8)(TIMER0_Preload);
    if(TMR0_InterruptHandler){
        TMR0_InterruptHandler();
    }
#endif
}

static inline void Timer0_Prescaler_Config(const timer0_t *_timer){
    if(_timer->prescaler_enable == TIMER0_PRESCALER_ENABLE_CFG){
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = _timer->prescaler_value;
    }
    else if(_timer->prescaler_enable == TIMER0_PRESCALER_DISABLE_CFG){
        TIMER0_PRESCALER_DISABLE();
    }
    else{ /* Do Nothing */ }
}

static inline void Timer0_Mode_Select(const timer0_t *_timer){
    if(_timer->timer0_mode == TIMER0_TIMER_MODE){
        TIMER0_TIMER_MODE_ENABLE();
    }
    else if(_timer->timer0_mode == TIMER0_COUNTER_MODE){
        TIMER0_COUNTER_MODE_ENABLE();
        if(_timer->timer0_counter_edge == TIMER0_RISING_EDGE_CFG){
            TIMER0_RISING_EDGE_ENABLE();
        }
        else if(_timer->timer0_counter_edge == TIMER0_FALLING_EDGE_CFG){
            TIMER0_FALLING_EDGE_ENABLE();
        }
        else{ /* Do Nothing */ }
    }
    else{ /* Do Nothing */ }
}

static inline void Timer0_Register_Size_Config(const timer0_t *_timer){
    if(_timer->timer0_register_size == TIMER0_8BIT_REGISTER_MODE){
        TIMER0_8BIT_REGISTER_ENABLE();
    }
    else if(_timer->timer0_register_size == TIMER0_16BIT_REGISTER_MODE){
        TIMER0_16BIT_REGISTER_ENABLE();
    }
    else{ /* Do Nothing */ }
}

static inline void Timer0_Interrupt_Config(const timer0_t *_timer){
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    TIMER0_INTERRUPT_ENABLE();
    TIMER0_FLAG_CLEAR();
    TMR0_InterruptHandler = _timer->Timer0_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriorityLevelsEnable();
    if(_timer->priority == INTERRUPT_HIGH_PRIORITY){ TIMER0_HighPrioritySet(); }
    else if(_timer->priority == INTERRUPT_LOW_PRIORITY){ TIMER0_LowPrioritySet(); }
    else{ /* Do Nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
}
