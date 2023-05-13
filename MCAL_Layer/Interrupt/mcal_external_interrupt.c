/* 
 * File:   mcal_external_interrupt.c
 * Author: omarm
 *
 * Created on March 15, 2023, 12:26 AM
 */



#include "mcal_external_interrupt.h"

static void (*INT0_InterruptHandler) (void) = NULL;
static void (*INT1_InterruptHandler) (void) = NULL;
static void (*INT2_InterruptHandler) (void) = NULL;

static void (*RB4_InterruptHandler_High) (void) = NULL;
static void (*RB4_InterruptHandler_Low) (void) = NULL;
static void (*RB5_InterruptHandler_High) (void) = NULL;
static void (*RB5_InterruptHandler_Low) (void) = NULL;
static void (*RB6_InterruptHandler_High) (void) = NULL;
static void (*RB6_InterruptHandler_Low) (void) = NULL;
static void (*RB7_InterruptHandler_High) (void) = NULL;
static void (*RB7_InterruptHandler_Low) (void) = NULL;

static Std_ReturnType interrupt_INTx_Enable(const interrupt_INTX_t *int_obj);
static Std_ReturnType interrupt_INTx_Disable(const interrupt_INTX_t *int_obj);
static Std_ReturnType interrupt_INTx_EdgeSet(const interrupt_INTX_t *int_obj);
static Std_ReturnType interrupt_INTx_PrioritySet (const interrupt_INTX_t *int_obj);
static Std_ReturnType interrupt_INTx_PinConfig (const interrupt_INTX_t *int_obj);
static Std_ReturnType interrupt_INTx_ClearFlag (const interrupt_INTX_t *int_obj);
static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType interrupt_INTx_SetInterruptHandler(const interrupt_INTX_t *int_obj);

static Std_ReturnType interrupt_RBx_Enable(const interrupt_RBX_t *int_obj);
static Std_ReturnType interrupt_RBx_Disable(const interrupt_RBX_t *int_obj);
static Std_ReturnType interrupt_RBx_PrioritySet (const interrupt_RBX_t *int_obj);
static Std_ReturnType RBX_SetInterruptHandler(const interrupt_RBX_t *int_obj);
static Std_ReturnType interrupt_RBx_PinConfig (const interrupt_RBX_t *int_obj);

#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType interrupt_INTx_Init(const interrupt_INTX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(int_obj != NULL){
        /* Disable external interrupt */
        ret = interrupt_INTx_Disable(int_obj);
        
        /* Clear interrupt flag */
        ret = interrupt_INTx_ClearFlag(int_obj);
        
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* Configure external interrupt priority */
        ret = interrupt_INTx_PrioritySet(int_obj);
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        
        /* Configure external interrupt edge */
        ret = interrupt_INTx_EdgeSet(int_obj);
        
        /* Configure external interrupt I/O pin */
        ret = interrupt_INTx_PinConfig(int_obj);
        
        /* Configure default interrupt callback */
        interrupt_INTx_SetInterruptHandler(int_obj);
        
        /* Enable external interrupt */
        ret = interrupt_INTx_Enable(int_obj);
        
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType interrupt_INTx_DeInit(const interrupt_INTX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(int_obj != NULL){
        ret = interrupt_INTx_Disable(int_obj);
    }
    return ret;
}


static Std_ReturnType interrupt_INTx_Enable(const interrupt_INTX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(int_obj != NULL){
        switch(int_obj->int_scr){
            case INTERRUPT_INT0:
                EXT_INT0_InterruptEnable();
                ret = E_OK;
                break;
            case INTERRUPT_INT1:
                EXT_INT1_InterruptEnable();
                ret = E_OK;
                break;
            case INTERRUPT_INT2:
                EXT_INT2_InterruptEnable();
                ret = E_OK;
                break;
            default: ret = E_NOT_OK; break;
        }
    }
    return ret;
}

static Std_ReturnType interrupt_INTx_Disable(const interrupt_INTX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(int_obj != NULL){
        switch(int_obj->int_scr){
            case INTERRUPT_INT0:
                EXT_INT0_InterruptDisable();
                ret = E_OK;
                break;
            case INTERRUPT_INT1:
                EXT_INT1_InterruptDisable();
                ret = E_OK;
                break;
            case INTERRUPT_INT2:
                EXT_INT2_InterruptDisable();
                ret = E_OK;
                break;
            default: ret = E_NOT_OK; break;
        }
    }
    return ret;
}

static Std_ReturnType interrupt_INTx_EdgeSet(const interrupt_INTX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(int_obj != NULL){
        switch(int_obj->int_scr){
            case INTERRUPT_INT0:
                if(int_obj->int_edge == INTERRUPT_RISING_EDGE){
                    EXT_INT0_RisingEdgeSet();
                    ret = E_OK;
                }
                else if(int_obj->int_edge == INTERRUPT_FALLING_EDGE){
                    EXT_INT0_FallingEdgeSet();
                    ret = E_OK;
                }
                else{ ret = E_NOT_OK; }
                break;
            case INTERRUPT_INT1:
                if(int_obj->int_edge == INTERRUPT_RISING_EDGE){
                    EXT_INT1_RisingEdgeSet();
                    ret = E_OK;
                }
                else if(int_obj->int_edge == INTERRUPT_FALLING_EDGE){
                    EXT_INT1_FallingEdgeSet();
                    ret = E_OK;
                }
                else{ ret = E_NOT_OK; }
                break;
            case INTERRUPT_INT2:
                if(int_obj->int_edge == INTERRUPT_RISING_EDGE){
                    EXT_INT2_RisingEdgeSet();
                    ret = E_OK;
                }
                else if(int_obj->int_edge == INTERRUPT_FALLING_EDGE){
                    EXT_INT2_FallingEdgeSet();
                    ret = E_OK;
                }
                else{ ret = E_NOT_OK; }
                break;
            default: ret = E_NOT_OK; break;
        }
    }
    return ret;
}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

static Std_ReturnType interrupt_INTx_PrioritySet (const interrupt_INTX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(int_obj != NULL){
        switch(int_obj->int_scr){
            case INTERRUPT_INT0:
                INTERRUPT_PriorityLevelsEnable();
                INTERRUPT_GlobalInterruptHighEnable();
                break;
            case INTERRUPT_INT1:
                if(int_obj->int_prio == INTERRUPT_HIGH_PRIORITY){
                    INTERRUPT_PriorityLevelsEnable();
                    INTERRUPT_GlobalInterruptHighEnable();
                    EXT_INT1_HighPrioritySet();
                    ret = E_OK;
                }
                else if(int_obj->int_prio == INTERRUPT_LOW_PRIORITY){
                    INTERRUPT_PriorityLevelsEnable();
                    INTERRUPT_GlobalInterruptLowEnable();
                    EXT_INT1_LowPrioritySet();
                    ret = E_OK;
                }
                else{ ret = E_NOT_OK; }
                break;
            case INTERRUPT_INT2:
                if(int_obj->int_prio == INTERRUPT_HIGH_PRIORITY){
                    INTERRUPT_PriorityLevelsEnable();
                    INTERRUPT_GlobalInterruptHighEnable();
                    EXT_INT2_HighPrioritySet();
                    ret = E_OK;
                }
                else if(int_obj->int_prio == INTERRUPT_LOW_PRIORITY){
                    INTERRUPT_PriorityLevelsEnable();
                    INTERRUPT_GlobalInterruptLowEnable();
                    EXT_INT2_LowPrioritySet();
                    ret = E_OK;
                }
                else{ ret = E_NOT_OK; }
                break;
            default: ret = E_NOT_OK; break;
        }
    }
    return ret;
}

#endif

static Std_ReturnType interrupt_INTx_PinConfig (const interrupt_INTX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(int_obj != NULL){
        ret = gpio_pin_initialize(&(int_obj->gpio_pin));
    }
    return ret;
}

static Std_ReturnType interrupt_INTx_ClearFlag (const interrupt_INTX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(int_obj != NULL){
        switch(int_obj->int_scr){
            case INTERRUPT_INT0:
                EXT_INT0_InterruptFlagClear();
                ret = E_OK;
                break;
            case INTERRUPT_INT1:
                EXT_INT1_InterruptFlagClear();
                ret = E_OK;
                break;
            case INTERRUPT_INT2:
                EXT_INT2_InterruptFlagClear();
                ret = E_OK;
                break;
            default: ret = E_NOT_OK; break;
        }
    }
    return ret;
}

static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(InterruptHandler != NULL){
        INT0_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(InterruptHandler != NULL){
        INT1_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(InterruptHandler != NULL){
        INT2_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

static Std_ReturnType interrupt_INTx_SetInterruptHandler(const interrupt_INTX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(int_obj != NULL){
        switch(int_obj->int_scr){
            case INTERRUPT_INT0:
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_INT1:
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_INT2:
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            default: ret = E_NOT_OK; break;
        }
    }
    return ret;
}
#endif
void INT0_ISR(void){
    #if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* Clear INT0 Interrupt Flag */
    INTCONbits.INT0IF = 0;
    
    /* Execute Code */
    
    /* Call back function gets called every time this ISR occurs */
    if(INT0_InterruptHandler != NULL){
        INT0_InterruptHandler();
    }
    #endif
}

void INT1_ISR(void){
    #if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* Clear INT0 Interrupt Flag */
    INTCON3bits.INT1IF = 0;
    
    /* Execute Code */
    
    /* Call back function gets called every time this ISR occurs */
    if(INT1_InterruptHandler != NULL){
        INT1_InterruptHandler();
    }
    #endif
}

void INT2_ISR(void){
    #if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    /* Clear INT0 Interrupt Flag */
    INTCON3bits.INT2IF = 0;
    
    /* Execute Code */
    
    /* Call back function gets called every time this ISR occurs */
    if(INT2_InterruptHandler != NULL){
        INT2_InterruptHandler();
    }
    #endif
}


#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/**
 * 
 * @param interrupt_RBX_t
 * @return 
 */
Std_ReturnType interrupt_RBx_Init(const interrupt_RBX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(int_obj != NULL){
        /* Disable external interrupt */
        ret = interrupt_RBx_Disable(int_obj);
        
        /* Clear interrupt flag */
        EXT_RBx_InterruptFlagClear();
            
        
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* Configure external interrupt priority */
        ret = interrupt_RBx_PrioritySet(int_obj);
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        
        /* Set call back function */
        ret = RBX_SetInterruptHandler(int_obj);
        
        /* initialize GPIO pin */
        ret = interrupt_RBx_PinConfig(int_obj);
        
        /* Enable external interrupt */
        ret = interrupt_RBx_Enable(int_obj);
        ret = E_OK;
    }
    return ret;
}

/**
 * 
 * @param interrupt_RBX_t
 * @return 
 */
Std_ReturnType interrupt_RBx_DeInit(const interrupt_RBX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(int_obj != NULL){
        EXT_RBx_InterruptDisable();
        ret = E_OK;
    }
    return ret;
}


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

static Std_ReturnType interrupt_RBx_PrioritySet (const interrupt_RBX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(int_obj != NULL){
        if(int_obj->int_prio == INTERRUPT_HIGH_PRIORITY){
            INTERRUPT_PriorityLevelsEnable();
            INTERRUPT_GlobalInterruptHighEnable();
            EXT_RBx_Priority_High();
            ret = E_OK;
        }
        else if(int_obj->int_prio == INTERRUPT_LOW_PRIORITY){
            INTERRUPT_PriorityLevelsEnable();
            INTERRUPT_GlobalInterruptLowEnable();
            EXT_RBx_Priority_Low();
            ret = E_OK;
        }
        else{ ret = E_NOT_OK; }
    }
    return ret;
}

#endif

static Std_ReturnType RBX_SetInterruptHandler(const interrupt_RBX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(int_obj != NULL){
        if(int_obj->EXT_InterruptHandler_High != NULL){
            switch(int_obj->gpio_pin.pin){
            case GPIO_PIN4:
                RB4_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                ret = E_OK;
                break;
            case GPIO_PIN5:
                RB5_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                ret = E_OK;
                break;
            case GPIO_PIN6:
                RB6_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                ret = E_OK;
                break;
            case GPIO_PIN7:
                RB7_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                ret = E_OK;
                break;
            default: ret = E_NOT_OK; break;
        }
        }
        if(int_obj->EXT_InterruptHandler_Low != NULL){
            switch(int_obj->gpio_pin.pin){
            case GPIO_PIN4:
                RB4_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                ret = E_OK;
                break;
            case GPIO_PIN5:
                RB5_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                ret = E_OK;
                break;
            case GPIO_PIN6:
                RB6_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                ret = E_OK;
                break;
            case GPIO_PIN7:
                RB7_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                ret = E_OK;
                break;
            default: ret = E_NOT_OK; break;
        }
        }
        
    }
    return ret;
}

static Std_ReturnType interrupt_RBx_Enable(const interrupt_RBX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(int_obj != NULL){
        EXT_RBx_InterruptEnable();
    }
    return ret;
}

static Std_ReturnType interrupt_RBx_Disable(const interrupt_RBX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(int_obj != NULL){
        EXT_RBx_InterruptDisable();
    }
    return ret;
}

static Std_ReturnType interrupt_RBx_PinConfig (const interrupt_RBX_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    ret = gpio_pin_direction_initialize(&(int_obj->gpio_pin));
    return ret;
}
#endif
void RB4_ISR(uint8 status){
    #if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EXT_RBx_InterruptFlagClear();
    
    if(status == STD_HIGH){
        if(RB4_InterruptHandler_High != NULL){
            RB4_InterruptHandler_High();
        }
    }
    else if(status == STD_LOW){
        if(RB4_InterruptHandler_Low != NULL){
            RB4_InterruptHandler_Low();
        }
    }
    #endif
}

void RB5_ISR(uint8 status){
    #if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EXT_RBx_InterruptFlagClear();
    
    if(status == STD_HIGH){
        if(RB5_InterruptHandler_High != NULL){
            RB5_InterruptHandler_High();
        }
    }
    else if(status == STD_LOW){
        if(RB5_InterruptHandler_Low != NULL){
            RB5_InterruptHandler_Low();
        }
    }
    #endif
}

void RB6_ISR(uint8 status){
    #if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EXT_RBx_InterruptFlagClear();
    
    if(status == STD_HIGH){
        if(RB6_InterruptHandler_High != NULL){
            RB6_InterruptHandler_High();
        }
    }
    else if(status == STD_LOW){
        if(RB6_InterruptHandler_Low != NULL){
            RB6_InterruptHandler_Low();
        }
    }
    #endif
}

void RB7_ISR(uint8 status){
    #if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EXT_RBx_InterruptFlagClear();
    
    if(status == STD_HIGH){
        if(RB7_InterruptHandler_High != NULL){
            RB7_InterruptHandler_High();
        }
    }
    else if(status == STD_LOW){
        if(RB7_InterruptHandler_Low != NULL){
            RB7_InterruptHandler_Low();
        }
    }
    #endif
}


