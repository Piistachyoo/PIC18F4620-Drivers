/* 
 * File:   ecu_keypad.h
 * Author: omarm
 *
 * Created on May 4, 2023, 1:07 PM
 */

#include "ecu_keypad.h"


static const uint8 btn_values [ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] = {
                                                            { '7', '8', '9', '/' },
                                                            { '4', '5', '6', 'x' },
                                                            { '1', '2', '3', '-' },
                                                            { '#', '0', '=', '+' }
                                                         };

Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj){
    Std_ReturnType ret = E_NOT_OK;
    uint8 row_counter, col_counter;
    if(_keypad_obj != NULL){
        for(row_counter=0;row_counter<ECU_KEYPAD_ROWS;row_counter++){
            gpio_pin_initialize(&(_keypad_obj->keypad_row_pins[row_counter]));
        }
        for(col_counter=0;col_counter<ECU_KEYPAD_COLUMNS;col_counter++){
            gpio_pin_direction_initialize(&(_keypad_obj->keypad_columns_pins[col_counter]));
        }
        ret = E_OK;
    }
    else{ /* Do Nothing */ }
    return ret;
}

Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value){
    Std_ReturnType ret = E_NOT_OK;
    uint8 row_counter, col_counter;
    logic_t pin_value;
    if((_keypad_obj != NULL) && (value != NULL)){
        for(row_counter=0;row_counter<ECU_KEYPAD_ROWS;row_counter++){
            ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[row_counter]), GPIO_HIGH);
            for(col_counter=0;col_counter<ECU_KEYPAD_COLUMNS;col_counter++){
                ret = gpio_pin_read_logic(&(_keypad_obj->keypad_columns_pins[col_counter]), &pin_value);
                if(pin_value == GPIO_HIGH){
                    *value = btn_values[row_counter][col_counter];
                }
            }
            ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[row_counter]), GPIO_LOW);
        }
        ret = E_OK;
    }
    else{ /* Do Nothing */ }
    return ret;
}
