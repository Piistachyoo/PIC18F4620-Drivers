/* 
 * File:   ecu_button.h
 * Author: omarm
 *
 * Created on March 7, 2023, 7:38 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section : Includes */
#include "ecu_button_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
typedef enum{
    BUTTON_PRESSED=0,
    BUTTON_RELEASED
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_HIGH=0,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct{
    pin_config_t    button_pin; /* @ref pin_config_t */
    button_state_t  button_state; /* @ref button_state_t */
    button_active_t button_connection; /* @ref button_active_t */
}button_t;

/* Section : Function Declarations */

/**
 * @brief initialize the button
 * @param btn pointer to button module configuration
 * @return Status of the function
 *          (E_OK): The function is done successfully
 *          (E_NOT_OK): There was an issue executing the function
 */
Std_ReturnType button_initialize(const button_t *btn);

/**
 * 
 * @param btn pointer to button module configuration
 * @param btn_state pointer to return the button state
 * @return Status of the function
 *          (E_OK): The function is done successfully
 *          (E_NOT_OK): There was an issue executing the function
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);

#endif	/* ECU_BUTTON_H */

