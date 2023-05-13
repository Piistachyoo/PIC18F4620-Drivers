
#include "ecu_seven_seg.h"

/**
 * @brief This interface to make the needed GPIO and seven segment initialization
 * @param seg pointer to the segment configurations
 * @return Status of the function
 *          (E_OK): The function is done successfully
 *          (E_NOT_OK): There was an issue executing the function
 */
Std_ReturnType seven_segment_initialize(const segment_t *seg){
    Std_ReturnType ret = E_OK;
    if(seg == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN0]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN1]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN2]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN3]));
    }
    return ret;
}

/**
 * @brief Write a number to the segment 0 ~ 9
 * @param seg pointer to the segment configurations
 * @param number the needed number to show
 * @return Status of the function
 *          (E_OK): The function is done successfully
 *          (E_NOT_OK): There was an issue executing the function
 */
Std_ReturnType seven_segment_write_numb(const segment_t *seg, uint8 number){
    Std_ReturnType ret = E_OK;
    if( (seg == NULL) || (number > 9) ){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN0]), number>>0 & BIT_MASK);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN1]), number>>1 & BIT_MASK);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN2]), number>>2 & BIT_MASK);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN3]), number>>3 & BIT_MASK);
    }
    return ret;
}
