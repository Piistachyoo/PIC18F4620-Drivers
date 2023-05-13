
#include "hal_usart.h"

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*EUSART_TxInterruptHandler)(void);
#endif

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*EUSART_RxInterruptHandler)(void);
static void (*EUSART_FramingErrorHandler)(void);
static void (*EUSART_OverrunErrorHandler)(void);
#endif

static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart);
static void EUSART_ASYNC_TX_Init(const usart_t *_eusart);
static void EUSART_ASYNC_RX_Init(const usart_t *_eusart);

Std_ReturnType EUSART_Init(const usart_t *_eusart){
    Std_ReturnType ret = E_NOT_OK;
    if(_eusart != NULL){
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
        TRISCbits.RC6 = 1;
        TRISCbits.RC7 = 1;
        EUSART_Baud_Rate_Calculation(_eusart);
        EUSART_ASYNC_TX_Init(_eusart);
        EUSART_ASYNC_RX_Init(_eusart);
        RCSTAbits.SPEN = EUSART_MODULE_ENABLE;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType EUSART_DeInit(const usart_t *_eusart){
    Std_ReturnType ret = E_NOT_OK;
    if(_eusart != NULL){
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType EUSART_ReadByteBlocking(uint8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    if(_data != NULL){
        while(!PIR1bits.RCIF);
        *_data = RCREG;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType EUSART_ReadByteNonBlocking(uint8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    if(_data != NULL){
        if(1 == PIR1bits.RCIF){
            *_data = RCREG;
            ret = E_OK;
        }
        else{
            ret = E_NOT_OK;
        }
    }
    return ret;
}

Std_ReturnType EUSART_WriteByteBlocking(uint8 _data){
    Std_ReturnType ret = E_OK;
    while(!TXSTAbits.TRMT);
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EUSART_TX_INTERRUPT_ENABLE();
#endif
    TXREG = _data;
    return ret;
}

Std_ReturnType EUSART_SendStringBlocking(uint8 *_string){
    Std_ReturnType ret = E_NOT_OK;
    int i=0;
    if(_string != NULL){
        while(_string[i] != '\0'){
            EUSART_WriteByteBlocking(_string[i]);
            i++;
        }
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType EUSART_WriteByteNonBlocking(uint8 _data){
    Std_ReturnType ret = E_NOT_OK;
    if(TXSTAbits.TRMT == 1){
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EUSART_TX_INTERRUPT_ENABLE();
#endif
        TXREG = _data;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType EUSART_SendStringNonBlocking(uint8 *_string){
    Std_ReturnType ret = E_NOT_OK;
    int i=0;
    if(_string != NULL){
        while(_string[i] != '\0'){
            EUSART_WriteByteNonBlocking(_string[i]);
            i++;
        }
        ret = E_OK;
    }
    return ret;
}

/* Function used for overrun error */
Std_ReturnType EUSART_ASYNC_RX_Restart(void){
    Std_ReturnType ret = E_OK;
    RCSTAbits.CREN = 0; // Disable receiver
    RCSTAbits.CREN = 1; // Enable receiver
    return ret;
}

static void EUSART_Baud_Rate_Calculation(const usart_t *_eusart){
    float Baud_Rate_temp;
    switch(_eusart->baudrate_cfg){
        case BAUDRATE_ASYN_8BIT_LOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
            Baud_Rate_temp = ((_XTAL_FREQ/(float)_eusart->baudrate)/64) - 1;
            SPBRG = (uint8)((uint32)Baud_Rate_temp);
            break;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
            Baud_Rate_temp = ((_XTAL_FREQ/(float)_eusart->baudrate)/16) - 1;
            SPBRG = (uint8)((uint32)Baud_Rate_temp);
            break;
        case BAUDRATE_ASYN_16BIT_LOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_temp = ((_XTAL_FREQ/(float)_eusart->baudrate)/16) - 1;
            SPBRG = (uint8)((uint32)Baud_Rate_temp);
            SPBRGH = (uint8)((uint32)Baud_Rate_temp>>8);
            break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_temp = ((_XTAL_FREQ/(float)_eusart->baudrate)/4) - 1;
            SPBRG = (uint8)((uint32)Baud_Rate_temp);
            break;
        case BAUDRATE_SYN_8BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
            break;
        case BAUDRATE_SYN_16BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            break;
        default: /* Do Nothing */ break;
    }
}

static void EUSART_ASYNC_TX_Init(const usart_t *_eusart){
    if(_eusart->tx_cfg.usart_tx_enable == EUSART_ASYNCHRONOUS_TX_ENABLE){
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
        
        
        if(_eusart->tx_cfg.usart_tx_9bit_enable == EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE;
        }
        else if(_eusart->tx_cfg.usart_tx_9bit_enable == EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE){
            TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE;
        }
        else{ /* Do Nothing */ }
        
        if(_eusart->tx_cfg.usart_tx_interrupt_enable == EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE){
            /* Interrupt Configuration */
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            EUSART_TX_FLAG_CLEAR();
            EUSART_TxInterruptHandler = _eusart->EUSART_TxDefaultInterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriorityLevelsEnable();
            if(_eusart->tx_cfg.tx_prio == INTERRUPT_HIGH_PRIORITY){
                EUSART_TX_HighPrioritySet();
                INTERRUPT_GlobalInterruptHighEnable();
            }
            else if(_eusart->tx_cfg.tx_prio == INTERRUPT_LOW_PRIORITY){
                EUSART_TX_LowPrioritySet();
                INTERRUPT_GlobalInterruptLowEnable();
            }
            else{ /* Do Nothing */ }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
            
#endif
        }
        else if(_eusart->tx_cfg.usart_tx_interrupt_enable == EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE){
            PIE1bits.TXIE = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
        }
        else{ /* Do Nothing */ }
    }
    else if(_eusart->tx_cfg.usart_tx_enable == EUSART_ASYNCHRONOUS_TX_DISABLE){
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_DISABLE;
    }
    else{ /* Do Nothing */ }
}

static void EUSART_ASYNC_RX_Init(const usart_t *_eusart){
    if(_eusart->rx_cfg.usart_rx_enable == EUSART_ASYNCHRONOUS_RX_ENABLE){
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
        
        if(_eusart->rx_cfg.usart_rx_interrupt_enable == EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE){
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE;
            /* Interrupt Configuration */
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            EUSART_RX_INTERRUPT_ENABLE();
            EUSART_RX_FLAG_CLEAR();
            EUSART_RxInterruptHandler = _eusart->EUSART_RxDefaultInterruptHandler;
            EUSART_FramingErrorHandler = _eusart->EUSART_FramingErrorHandler;
            EUSART_OverrunErrorHandler = _eusart->EUSART_OverrunErrorHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriorityLevelsEnable();
            if(_eusart->rx_cfg.rx_prio == INTERRUPT_HIGH_PRIORITY){
                EUSART_RX_HighPrioritySet();
                INTERRUPT_GlobalInterruptHighEnable();
            }
            else if(_eusart->rx_cfg.rx_prio == INTERRUPT_LOW_PRIORITY){
                EUSART_RX_LowPrioritySet();
                INTERRUPT_GlobalInterruptLowEnable();
            }
            else{ /* Do Nothing */ }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
            
#endif
        }
        else if(_eusart->rx_cfg.usart_rx_interrupt_enable == EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE){
            PIE1bits.RCIE = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
        }
        else{ /* Do Nothing */ }

        if(_eusart->rx_cfg.usart_rx_9bit_enable == EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE;
        }
        else if(_eusart->rx_cfg.usart_rx_9bit_enable == EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE){
            RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE;
        }
        else{ /* Do Nothing */ }
    }
    else if(_eusart->rx_cfg.usart_rx_enable == EUSART_ASYNCHRONOUS_RX_DISABLE){
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_DISABLE;
    }
    else{ /* Do Nothing */ }
}

void EUSART_TX_ISR(void){
    #if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EUSART_TX_INTERRUPT_DISABLE();
    EUSART_TX_FLAG_CLEAR();
    if(EUSART_TxInterruptHandler != NULL){
        EUSART_TxInterruptHandler();
    }else{ /* Do Nothing */ }
    #endif
}


void EUSART_RX_ISR(void){
    #if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    EUSART_RX_FLAG_CLEAR();
    if(EUSART_RxInterruptHandler != NULL){
        EUSART_RxInterruptHandler();
    }else{ /* Do Nothing */ }
    if((EUSART_FramingErrorHandler != NULL) && (RCSTAbits.FERR == INTERRUPT_OCCUR)){
        EUSART_FramingErrorHandler();
    }else{ /* Do Nothing */ }
    if((EUSART_OverrunErrorHandler != NULL) && (RCSTAbits.OERR == INTERRUPT_OCCUR)){
        EUSART_OverrunErrorHandler();
    }else{ /* Do Nothing */ }
    #endif
}

