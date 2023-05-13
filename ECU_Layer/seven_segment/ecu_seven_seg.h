/* 
 * File:   ecu_seven_seg.h
 * Author: omarm
 *
 * Created on March 7, 2023, 8:09 PM
 */

#ifndef ECU_SEVEN_SEG_H
#define	ECU_SEVEN_SEG_H

/* Section : Includes */
#include "ecu_seven_seg_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section : Macro Declarations */
#define SEGMENT_PIN0    0
#define SEGMENT_PIN1    1
#define SEGMENT_PIN2    2
#define SEGMENT_PIN3    3
/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
typedef enum{
    SEGMENT_COMMON_ANODE=0,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;
/* Section : Function Declarations */

Std_ReturnType seven_segment_initialize(const segment_t *seg);
Std_ReturnType seven_segment_write_numb(const segment_t *seg, uint8 number);

#endif	/* ECU_SEVEN_SEG_H */

