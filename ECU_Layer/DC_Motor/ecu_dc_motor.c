
#include "ecu_dc_motor.h"

Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_NOT_OK;
    if(_dc_motor == NULL){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_initialize(&(_dc_motor->dc_motor_pin[0]));
        gpio_pin_initialize(&(_dc_motor->dc_motor_pin[1]));
    }
    return ret;
}

Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_NOT_OK;
    if(_dc_motor == NULL){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]), GPIO_HIGH);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]), GPIO_LOW);
    }
    return ret;
}

Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_NOT_OK;
    if(_dc_motor == NULL){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]), GPIO_HIGH);
    }
    return ret;
}

Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_NOT_OK;
    if(_dc_motor == NULL){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]), GPIO_LOW);
    }
    return ret;
}

