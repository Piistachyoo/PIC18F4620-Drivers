/* 
 * File:   ecu_dc_motor.h
 * Author: omarm
 *
 * Created on March 9, 2023, 9:30 AM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* Section : Includes */
#include "ecu_dc_motor_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section : Macro Declarations */
#define dc_motor_on     0x01U
#define dc_motor_off    0x00U

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

typedef struct{
    pin_config_t dc_motor_pin[2];
}dc_motor_t;

/* Section : Function Declarations */
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor);

#endif	/* ECU_DC_MOTOR_H */

