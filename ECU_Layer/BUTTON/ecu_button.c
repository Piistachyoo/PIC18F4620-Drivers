
#include "ecu_button.h"

/**
 * @brief initialize the button
 * @param btn pointer to button module configuration
 * @return Status of the function
 *          (E_OK): The function is done successfully
 *          (E_NOT_OK): There was an issue executing the function
 */
Std_ReturnType button_initialize(const button_t *btn){
    Std_ReturnType ret = E_OK;
    if(btn == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_initialize(&(btn->button_pin));
    }
    return ret;
}

/**
 * 
 * @param btn pointer to button module configuration
 * @param btn_state pointer to return the button state
 * @return Status of the function
 *          (E_OK): The function is done successfully
 *          (E_NOT_OK): There was an issue executing the function
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state){
    Std_ReturnType ret = E_OK;
    logic_t pin_logic_status = GPIO_LOW;
    if( (btn == NULL) || (btn_state == NULL) ){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_read_logic(&(btn->button_pin), &pin_logic_status);
        if(btn->button_connection == BUTTON_ACTIVE_HIGH){
            if(pin_logic_status == GPIO_HIGH){
                *btn_state = BUTTON_PRESSED;
            }
            else{
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(btn->button_connection == BUTTON_ACTIVE_LOW){
            if(pin_logic_status == GPIO_HIGH){
                *btn_state = BUTTON_RELEASED;
            }
            else{
                *btn_state = BUTTON_PRESSED;
            }
        }
        else { /* Do Nothing */ }
    }
    return ret;
}