/* 
 * File:   ecu_led.c
 * Author: omarm
 *
 * Created on March 6, 2023, 2:40 AM
 */

#include "ecu_led.h"


/**
 * @brief Initalize the assigned pin to be OUTPUT and turn the led off
 * @param led pointer to the led module configuration
 * @return Status of the function
 *          (E_OK): The function is done successfully
 *          (E_NOT_OK): There was an issue executing the function
 */
Std_ReturnType led_initialize(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(led == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
            .direction = GPIO_DIRECTION_OUTPUT, 
            .logic = led->led_status, 
            .pin = led->pin, 
            .port = led->port_name
        };
        gpio_pin_initialize(&pin_obj);
    }
    return ret;
}

/**
 * @brief Turn the led on
 * @param led pointer to the led module configuration
 * @return Status of the function
 *          (E_OK): The function is done successfully
 *          (E_NOT_OK): There was an issue executing the function
 */
Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(led == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
            .direction = GPIO_DIRECTION_OUTPUT, 
            .logic = led->led_status, 
            .pin = led->pin, 
            .port = led->port_name
        };
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret;
}

/**
 * @brief Turn the led off
 * @param led pointer to the led module configuration
 * @return Status of the function
 *          (E_OK): The function is done successfully
 *          (E_NOT_OK): There was an issue executing the function
 */
Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(led == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
            .direction = GPIO_DIRECTION_OUTPUT, 
            .logic = led->led_status, 
            .pin = led->pin, 
            .port = led->port_name
        };
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret;
}

/**
 * @brief Toggle the led
 * @param led pointer to the led module configuration
 * @return Status of the function
 *          (E_OK): The function is done successfully
 *          (E_NOT_OK): There was an issue executing the function
 */
Std_ReturnType led_turn_toggle(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(led == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
            .direction = GPIO_DIRECTION_OUTPUT, 
            .logic = led->led_status, 
            .pin = led->pin, 
            .port = led->port_name
        };
        gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}