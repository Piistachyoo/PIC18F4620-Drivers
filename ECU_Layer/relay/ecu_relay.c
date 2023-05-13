
#include "ecu_relay.h"

/**
 * @brief Initializes the relay
 * @param _relay pointer to the relay configuration
 * @return Status of the function
 *          (E_OK) Function was executed successfully
 *          (E_NOT_OK) Function was not executed successfully
 */
Std_ReturnType relay_initialize(const relay_t *_relay){
    Std_ReturnType ret = E_NOT_OK;
    if(_relay == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t relay_config = { .direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->relay_status,
        .port = _relay->relay_port, .pin = _relay->relay_pin};
        gpio_pin_initialize(&relay_config);
    }
    return ret;
}

/**
 * @brief Turn on the relay
 * @param _relay
 * @return Status of the function
 *          (E_OK) Function was executed successfully
 *          (E_NOT_OK) Function was not executed successfully
 */
Std_ReturnType relay_turn_on(const relay_t *_relay){
    Std_ReturnType ret = E_NOT_OK;
    if(_relay == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t relay_config = { .direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->relay_status,
        .port = _relay->relay_port, .pin = _relay->relay_pin};
        gpio_pin_write_logic(&relay_config, GPIO_HIGH);
    }
    return ret;
}

/**
 * @brief Turn off the relay
 * @param relay
 * @return Status of the function
 *          (E_OK) Function was executed successfully
 *          (E_NOT_OK) Function was not executed successfully
 */
Std_ReturnType relay_turn_off(const relay_t *_relay){
    Std_ReturnType ret = E_NOT_OK;
    if(_relay == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t relay_config = { .direction = GPIO_DIRECTION_OUTPUT, .logic = _relay->relay_status,
        .port = _relay->relay_port, .pin = _relay->relay_pin};
        gpio_pin_write_logic(&relay_config, GPIO_LOW);
    }
    return ret;
}
