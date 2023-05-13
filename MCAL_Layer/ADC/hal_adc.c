 /* 
 * File:   hal_adc.c
 * Author: omarm
 *
 * Created on May 5, 2023, 1:01 PM
 */

#include "hal_adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*ADC_InterruptHandler)(void) = NULL;
#endif

static inline void adc_input_channel_port_configure(adc_channel_select_t channel);
static inline void select_result_format(const adc_cfg_t *_adc);
static inline void configure_voltage_reference(const adc_cfg_t *_adc);

Std_ReturnType ADC_Init(const adc_cfg_t *_adc){
    Std_ReturnType ret = E_NOT_OK;
    if(_adc != NULL){
        /* Disable ADC */
        ADC_CONVERTER_DISABLE();
        /* Configure the acquisition time */
        ADCON2bits.ACQT = _adc->acquisition_time;
        
        /* Configure the conversion clock */
        ADCON2bits.ADCS = _adc->conversion_clock;
        
        /* Configure the default channel */
        ADCON0bits.CHS = _adc->adc_channel;
        adc_input_channel_port_configure(_adc->adc_channel);
        
        /* Configure the interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_ENABLE();
        ADC_FLAG_CLEAR();
        ADC_InterruptHandler = _adc->ADC_Interrupt_Handler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(_adc->priority == INTERRUPT_HIGH_PRIORITY){ ADC_HighPrioritySet(); }
        else if(_adc->priority == INTERRUPT_LOW_PRIORITY){ ADC_LowPrioritySet(); }
        else{ /* Do Nothing */ }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        /* Configure the result format */
        select_result_format(_adc);
        
        /* Configure the voltage reference */
        configure_voltage_reference(_adc);
        
        /* Enable ADC */
        ADC_CONVERTER_ENABLE();
        
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_DeInit(const adc_cfg_t *_adc){
    Std_ReturnType ret = E_NOT_OK;
    if(_adc != NULL){
        /* Disable ADC */
        ADC_CONVERTER_DISABLE();
        
        /* Disable interrupts */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_DISABLE();
#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_SelectChannel(const adc_cfg_t *_adc, adc_channel_select_t channel){
    Std_ReturnType ret = E_NOT_OK;
    if(_adc != NULL){
        ADCON0bits.CHS = channel;
        adc_input_channel_port_configure(channel);
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_StartConversion(const adc_cfg_t *_adc){
    Std_ReturnType ret = E_NOT_OK;
    if(_adc != NULL){
        ADC_START_CONVERSION();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_IsConversionDone(const adc_cfg_t *_adc, uint8 *conversion_status){
    Std_ReturnType ret = E_NOT_OK;
    if(_adc != NULL){
        *conversion_status = (uint8)(!ADCON0bits.GODONE);
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_GetConversionResult(const adc_cfg_t *_adc, uint16 *conversion_result){
    Std_ReturnType ret = E_NOT_OK;
    if(_adc != NULL){
        if(ADC_RESULT_RIGHT == _adc->result_format){
            *conversion_result = (uint16)((ADRESH << 8) + (ADRESL));
        }
        else if(ADC_RESULT_LEFT == _adc->result_format){
            *conversion_result = (uint16)(((ADRESH << 8) + (ADRESL)) >> 6);
        }
        else{  }
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_GetConversion_Blocking(const adc_cfg_t *_adc, adc_channel_select_t channel, uint16 *conversion_result){
    Std_ReturnType ret = E_NOT_OK;
    uint8 local_conversion_status = 0;
    if(_adc != NULL){
        /* Select the A/D channel */
        ret = ADC_SelectChannel(_adc, channel);
        
        /* Start conversion */
        ret = ADC_StartConversion(_adc);
        
        /* Check if conversion is completed */
        while(ADCON0bits.GODONE){
            ret = ADC_IsConversionDone(_adc, &local_conversion_status);
        }
        
        /* Return conversion result */
        ret = ADC_GetConversionResult(_adc, conversion_result);
    }
    return ret;
}

Std_ReturnType ADC_StartConversion_Interrupt(const adc_cfg_t *_adc, adc_channel_select_t channel){
    Std_ReturnType ret = E_NOT_OK;
    uint8 local_conversion_status = 0;
    if(_adc != NULL){
        /* Select the A/D channel */
        ret = ADC_SelectChannel(_adc, channel);
        
        /* Start conversion */
        ret = ADC_StartConversion(_adc);
        
    }
    return ret;
}

static inline void adc_input_channel_port_configure(adc_channel_select_t channel){
    switch(channel){
        case ADC_CHANNEL_AN0: SET_BIT(TRISA, _TRISA_RA0_POSITION); break;
        case ADC_CHANNEL_AN1: SET_BIT(TRISA, _TRISA_RA1_POSITION); break;
        case ADC_CHANNEL_AN2: SET_BIT(TRISA, _TRISA_RA2_POSITION); break;
        case ADC_CHANNEL_AN3: SET_BIT(TRISA, _TRISA_RA3_POSITION); break;
        case ADC_CHANNEL_AN4: SET_BIT(TRISA, _TRISA_RA5_POSITION); break;
        case ADC_CHANNEL_AN5: SET_BIT(TRISE, _TRISE_RE0_POSITION); break;
        case ADC_CHANNEL_AN6: SET_BIT(TRISE, _TRISE_RE1_POSITION); break;
        case ADC_CHANNEL_AN7: SET_BIT(TRISE, _TRISE_RE2_POSITION); break;
        case ADC_CHANNEL_AN8: SET_BIT(TRISB, _TRISB_RB2_POSITION); break;
        case ADC_CHANNEL_AN9: SET_BIT(TRISB, _TRISB_RB3_POSITION); break;
        case ADC_CHANNEL_AN10: SET_BIT(TRISB, _TRISB_RB1_POSITION); break;
        case ADC_CHANNEL_AN11: SET_BIT(TRISB, _TRISB_RB4_POSITION); break;
        case ADC_CHANNEL_AN12: SET_BIT(TRISB, _TRISB_RB0_POSITION); break;
        default: /* Do Nothing */ break;
    }
}

static inline void select_result_format(const adc_cfg_t *_adc){
    if(ADC_RESULT_RIGHT == _adc->result_format){
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if(ADC_RESULT_LEFT == _adc->result_format){
        ADC_RESULT_LEFT_FORMAT();
    }
    else{ 
        ADC_RESULT_RIGHT_FORMAT();
    }
}

static inline void configure_voltage_reference(const adc_cfg_t *_adc){
    if(ADC_VOLTAGE_REFERENCE_ENABLED == _adc->voltage_reference){
        ADC_ENABLE_VOLTAGE_REFERENCE();
    }
    else if(ADC_VOLTAGE_REFERENCE_DISABLED == _adc->voltage_reference){
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
    else{ ADC_DISABLE_VOLTAGE_REFERENCE(); }
}

void ADC_Interrupt_ISR(){
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    ADC_FLAG_CLEAR();
    if(ADC_InterruptHandler != NULL){
        ADC_InterruptHandler();
    }
#endif
}
