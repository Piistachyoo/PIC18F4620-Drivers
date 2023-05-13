/* 
 * File:   ecu_temp_sensor.h
 * Author: omarm
 *
 * Created on May 10, 2023, 10:21 PM
 */

#ifndef ECU_TEMP_SENSOR_H
#define	ECU_TEMP_SENSOR_H

/* Section : Includes */
#include "../../MCAL_Layer/ADC/hal_adc.h"
#include "../../MCAL_Layer/mcal_std_types.h"

/* Section : Macro Declarations */
#define VREF_VALUE      5000.0
#define ADC_RESOLUTION  1024.0
/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
typedef struct{
    adc_cfg_t SENSOR_ADC;
}temp_sensor_t;

/* Section : Function Declarations */
Std_ReturnType TEMP_SENSOR_INIT(const temp_sensor_t *sensor_obj);
Std_ReturnType TEMP_SENSOR_GET_READING(const temp_sensor_t *sensor_obj, uint8 *_result);

#endif	/* ECU_TEMP_SENSOR_H */

