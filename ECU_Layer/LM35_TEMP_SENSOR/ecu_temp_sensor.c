/* 
 * File:   ecu_temp_sensor.h
 * Author: omarm
 *
 * Created on May 10, 2023, 10:21 PM
 */

#include "ecu_temp_sensor.h"

Std_ReturnType TEMP_SENSOR_INIT(const temp_sensor_t *sensor_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(sensor_obj != NULL){
        ret = ADC_Init(&(sensor_obj->SENSOR_ADC));
    }
    return ret;
}

Std_ReturnType TEMP_SENSOR_GET_READING(const temp_sensor_t *sensor_obj, uint8 *_result){
    Std_ReturnType ret = E_NOT_OK;
    uint16 local_adc_reading;
    uint16 local_tempreature_value;
    if(sensor_obj != NULL){
        ret = ADC_GetConversion_Blocking(&(sensor_obj->SENSOR_ADC), sensor_obj->SENSOR_ADC.adc_channel, &local_adc_reading);
        local_tempreature_value = (uint16)((local_adc_reading * VREF_VALUE) / ADC_RESOLUTION);
        *_result = (uint8)(local_tempreature_value/10);
    }
    return ret;
}
