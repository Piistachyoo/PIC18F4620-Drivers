/* 
 * File:   ecu_led.h
 * Author: omarm
 *
 * Created on March 6, 2023, 2:40 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
typedef enum{
    LED_OFF=0,
    LED_ON
}led_status;

typedef struct{
    uint8 port_name :4; /* @ref port_index_t */
    uint8 pin       :3; /* @ref pin_index_t */
    uint8 led_status:1; /* @ref led_status */
}led_t;

/* Section : Function Declarations */
/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the led off
 * @param led pointer to the led module configuration
 * @return Status of the function
 *          (E_OK): The function is done successfully
 *          (E_NOT_OK): There was an issue executing the function
 */
Std_ReturnType led_initialize(const led_t *led);

/**
 * @brief Turn the led on
 * @param led pointer to the led module configuration
 * @return Status of the function
 *          (E_OK): The function is done successfully
 *          (E_NOT_OK): There was an issue executing the function
 */
Std_ReturnType led_turn_on(const led_t *led);

/**
 * @brief Turn the led off
 * @param led pointer to the led module configuration
 * @return Status of the function
 *          (E_OK): The function is done successfully
 *          (E_NOT_OK): There was an issue executing the function
 */
Std_ReturnType led_turn_off(const led_t *led);

/**
 * @brief Toggle the led
 * @param led pointer to the led module configuration
 * @return Status of the function
 *          (E_OK): The function is done successfully
 *          (E_NOT_OK): There was an issue executing the function
 */
Std_ReturnType led_turn_toggle(const led_t *led);
#endif	/* ECU_LED_H */

