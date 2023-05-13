
#include "hal_spi.h"

#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*SPI_InterruptHandler)(void) = NULL;
#endif

static Std_ReturnType SPI_ClockInit(const SPI_cfg_t *SPI_obj);
static Std_ReturnType SPI_SampleInit(const SPI_cfg_t *SPI_obj);
static Std_ReturnType SPI_SetInterruptHandler(const SPI_cfg_t *SPI_obj);
static Std_ReturnType SPI_MASTER_GPIO_CFG(const SPI_cfg_t *SPI_obj);
static Std_ReturnType SPI_SLAVE_GPIO_CFG(const SPI_cfg_t *SPI_obj);
static void SPI_Interrupt_CFG(const SPI_cfg_t *SPI_obj);


Std_ReturnType SPI_vInit(const SPI_cfg_t *SPI_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(SPI_obj != NULL){
        SPI_DISABLE_MODULE();
        ret = SPI_ClockInit(SPI_obj);
        ret = SPI_SampleInit(SPI_obj);
        SPI_Interrupt_CFG(SPI_obj);
        SPI_ENABLE_MODULE();
    }
    return ret;
}

void SPI_vDeInit(){
    SPI_DISABLE_MODULE();
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    MSSP_SPI_INTERRUPT_DISABLE();
#endif
}

Std_ReturnType SPI_vSendByte(uint8 Copy_u8Data){
    Std_ReturnType ret = E_OK;
    SSPBUF = Copy_u8Data;
    while(!PIR1bits.SSPIF);
    PIR1bits.SSPIF = 0;
    return ret;
}

Std_ReturnType SPI_u8ReceiveByte(uint8 *_Data){
    Std_ReturnType ret = E_NOT_OK;
    if(_Data != NULL){
        while(SSPSTATbits.BF == 0);
        *_Data = SSPBUF;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType SPI_vSendByte_NonBlocking(uint8 Copy_u8Data){
    Std_ReturnType ret = E_OK;
    if(PIR1bits.SSPIF == 0){
        SSPBUF = Copy_u8Data;
    }
    if(PIR1bits.SSPIF == 1){
        PIR1bits.SSPIF = 0;
    }
    return ret;
}

Std_ReturnType SPI_u8ReceiveByte_NonBlocking(uint8 *_Data){
    Std_ReturnType ret = E_NOT_OK;
    if(_Data != NULL){
        if(SSPSTATbits.BF == 1){
            *_Data = SSPBUF;
            ret = E_OK;
        }
    }
    return ret;
}

static Std_ReturnType SPI_ClockInit(const SPI_cfg_t *SPI_obj){
    Std_ReturnType ret = E_NOT_OK;
    switch(SPI_obj->Prescale){
        case SPI_MASTER_FOSC_DIV4:
            SSPCON1 = (SSPCON1 & 0xF8);
            ret = SPI_MASTER_GPIO_CFG(SPI_obj);
            break;
        case SPI_MASTER_FOSC_DIV16:
            SSPCON1 = (SSPCON1 & 0xF8) | 0x01;
            ret = SPI_MASTER_GPIO_CFG(SPI_obj);
            break;
        case SPI_MASTER_FOSC_DIV64:
            SSPCON1 = (SSPCON1 & 0xF8) | 0x02;
            ret = SPI_MASTER_GPIO_CFG(SPI_obj);
            break;
        case SPI_MASTER_FOSC_TMR2:
            SSPCON1 = (SSPCON1 & 0xF8) | 0x03;
            ret = SPI_MASTER_GPIO_CFG(SPI_obj);
            break;
        case SPI_SLAVE_SS_ENABLED:
            SSPCON1 = (SSPCON1 & 0xF8) | 0x04;
            ret = SPI_SLAVE_GPIO_CFG(SPI_obj);
            break;
        case SPI_SLAVE_SS_DISABLED:
            SSPCON1 = (SSPCON1 & 0xF8) | 0x05;
            ret = SPI_SLAVE_GPIO_CFG(SPI_obj);
            break;
        default: ret = E_NOT_OK; break;
    }
    return ret;
}

static Std_ReturnType SPI_SampleInit(const SPI_cfg_t *SPI_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(SPI_obj != NULL){
        if(SPI_obj->ClockPolarity == CLK_IDLE_LOW){
            SSPCON1bits.CKP = 0;
        }
        else if(SPI_obj->ClockPolarity == CLK_IDLE_HIGH){
            SSPCON1bits.CKP = 1;
        }
        else{ /* Do Nothing */ }
        if(SPI_obj->Sampling == SAMPLE_MIDDLE){
            SSPSTATbits.SMP = 0;
        }
        else if(SPI_obj->Sampling == SAMPLE_END){
            SSPSTATbits.SMP = 1;
        }
        else{ /* Do Nothing */ }
        if(SPI_obj->TransmitMode == SPI_TRANSMIT_ACTIVE_TO_IDLE){
            SSPSTATbits.CKE = 1;
        }
        else if(SPI_obj->TransmitMode == SPI_TRANSMIT_IDLE_TO_ACTIVE){
            SSPSTATbits.CKE = 0;
        }
        else{ /* Do Nothing */ }
        ret = E_OK;
    }
    return ret;
}

static Std_ReturnType SPI_MASTER_GPIO_CFG(const SPI_cfg_t *SPI_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(SPI_obj != NULL){
        pin_config_t SPI_SDO = {.port = GPIO_PORTC_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_OUTPUT};
        pin_config_t SPI_SDI = {.port = GPIO_PORTC_INDEX, .pin = GPIO_PIN4, .direction = GPIO_DIRECTION_INPUT};
        pin_config_t SPI_CLK = {.port = GPIO_PORTC_INDEX, .pin = GPIO_PIN3, .direction = GPIO_DIRECTION_OUTPUT};

        ret = gpio_pin_direction_initialize(&SPI_SDO); 
        ret = gpio_pin_direction_initialize(&SPI_SDI);
        ret = gpio_pin_direction_initialize(&SPI_CLK);
    }
    return ret;
}

static Std_ReturnType SPI_SLAVE_GPIO_CFG(const SPI_cfg_t *SPI_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(SPI_obj != NULL){
        pin_config_t SPI_SDO = {.port = GPIO_PORTC_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_OUTPUT};
        pin_config_t SPI_SDI = {.port = GPIO_PORTC_INDEX, .pin = GPIO_PIN4, .direction = GPIO_DIRECTION_INPUT};
        pin_config_t SPI_CLK = {.port = GPIO_PORTC_INDEX, .pin = GPIO_PIN3, .direction = GPIO_DIRECTION_INPUT};
        pin_config_t SPI_SS = {.port = GPIO_PORTC_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_INPUT};

        ret = gpio_pin_direction_initialize(&SPI_SDO); 
        ret = gpio_pin_direction_initialize(&SPI_SDI);
        ret = gpio_pin_direction_initialize(&SPI_CLK); 

        if(SPI_obj->Prescale == SPI_SLAVE_SS_ENABLED){
            ret = gpio_pin_direction_initialize(&SPI_SS);
        }
    }
    return ret;
}

static void SPI_Interrupt_CFG(const SPI_cfg_t *SPI_obj){
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    MSSP_SPI_INTERRUPT_ENABLE();
    MSSP_SPI_FLAG_CLEAR();
    SPI_InterruptHandler = SPI_obj->MSSP_SPI_IntHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriorityLevelsEnable();
    if(SPI_obj->INT_Prio == INTERRUPT_HIGH_PRIORITY){
        MSSP_SPI_HighPrioritySet();
        INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(SPI_obj->INT_Prio == INTERRUPT_LOW_PRIORITY){
        MSSP_SPI_LowPrioritySet();
        INTERRUPT_GlobalInterruptLowEnable();
    }
    else{ /* Do Nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
}
