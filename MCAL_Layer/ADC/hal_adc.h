/* 
 * File:   hal_adc.h
 * Author: omarm
 *
 * Created on May 5, 2023, 1:01 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* Section : Includes */
#include "../compiler.h"
#include "hal_adc_cfg.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "../mcal_std_types.h"

/* Section : Macro Declarations */
#define ADC_AN0_ANALOG_FUNCTIONALITY    0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY    0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY    0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY    0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY    0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY    0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY    0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY    0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY    0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY    0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY   0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY   0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY   0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY    0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY   0x0F

#define ADC_RESULT_RIGHT                0x01U
#define ADC_RESULT_LEFT                 0x00U

#define ADC_VOLTAGE_REFERENCE_ENABLED   0x01U
#define ADC_VOLTAGE_REFERENCE_DISABLED  0x00U

#define ADC_CONVERSION_COMPLETED    1
#define ADC_CONVERSION_INPROGRESS   0

/* Section : Macro Functions Declarations */
#define ADC_CONVERSION_STATUS()     (ADCON0bits.GODONE)
#define ADC_START_CONVERSION()      (ADCON0bits.GODONE = 1)
#define ADC_CONVERTER_ENABLE()      (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE()     (ADCON0bits.ADON = 0)

#define ADC_ENABLE_VOLTAGE_REFERENCE()  do{ADCON1bits.VCFG1 = 1;\
                                           ADCON1bits.VCFG0 = 1;\
                                           }while(0)

#define ADC_DISABLE_VOLTAGE_REFERENCE() do{ADCON1bits.VCFG1 = 0;\
                                           ADCON1bits.VCFG0 = 0;\
                                           }while(0)

#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG)     (ADCON1bits.PCFG = _CONFIG)

#define ADC_RESULT_RIGHT_FORMAT()   (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()    (ADCON2bits.ADFM = 0)

/* Section : Data Type Declarations */
typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
}adc_channel_select_t;

typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD
}adc_acquisition_time_t;

typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
}adc_conversion_clock_t;

typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* ADC_Interrupt_Handler)(void);
    interrupt_priority_cfg priority;
#endif
    adc_acquisition_time_t acquisition_time; /* @ref adc_acquisition_time_t */
    adc_conversion_clock_t conversion_clock; /* @ref adc_conversion_clock_t */
    adc_channel_select_t   adc_channel;      /* @ref adc_channel_select_t */
    uint8 voltage_reference         :1;
    uint8 result_format             :1;
    uint8 adc_reserved              :6;
}adc_cfg_t;

/* Section : Function Declarations */
Std_ReturnType ADC_Init(const adc_cfg_t *_adc);
Std_ReturnType ADC_DeInit(const adc_cfg_t *_adc);
Std_ReturnType ADC_SelectChannel(const adc_cfg_t *_adc, adc_channel_select_t channel);
Std_ReturnType ADC_StartConversion(const adc_cfg_t *_adc);
Std_ReturnType ADC_IsConversionDone(const adc_cfg_t *_adc, uint8 *conversion_status);
Std_ReturnType ADC_GetConversionResult(const adc_cfg_t *_adc, uint16 *conversion_result);
Std_ReturnType ADC_GetConversion_Blocking(const adc_cfg_t *_adc, adc_channel_select_t channel, uint16 *conversion_result);
Std_ReturnType ADC_StartConversion_Interrupt(const adc_cfg_t *_adc, adc_channel_select_t channel);
#endif	/* HAL_ADC_H */

