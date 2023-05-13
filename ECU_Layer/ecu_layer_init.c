
#include "ecu_layer_init.h"
#include "LCD/ecu_chr_lcd.h"

keypad_t KPD1 = {
    .keypad_row_pins[0].port = GPIO_PORTC_INDEX,
    .keypad_row_pins[0].pin = GPIO_PIN0,
    .keypad_row_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[0].logic = GPIO_LOW,
    .keypad_row_pins[1].port = GPIO_PORTC_INDEX,
    .keypad_row_pins[1].pin = GPIO_PIN1,
    .keypad_row_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[1].logic = GPIO_LOW,
    .keypad_row_pins[2].port = GPIO_PORTC_INDEX,
    .keypad_row_pins[2].pin = GPIO_PIN2,
    .keypad_row_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[2].logic = GPIO_LOW,
    .keypad_row_pins[3].port = GPIO_PORTC_INDEX,
    .keypad_row_pins[3].pin = GPIO_PIN3,
    .keypad_row_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[3].logic = GPIO_LOW,
    
    .keypad_columns_pins[0].port = GPIO_PORTC_INDEX,
    .keypad_columns_pins[0].pin = GPIO_PIN4,
    .keypad_columns_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[0].logic = GPIO_LOW,
    .keypad_columns_pins[1].port = GPIO_PORTC_INDEX,
    .keypad_columns_pins[1].pin = GPIO_PIN5,
    .keypad_columns_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[1].logic = GPIO_LOW,
    .keypad_columns_pins[2].port = GPIO_PORTC_INDEX,
    .keypad_columns_pins[2].pin = GPIO_PIN6,
    .keypad_columns_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[2].logic = GPIO_LOW,
    .keypad_columns_pins[3].port = GPIO_PORTC_INDEX,
    .keypad_columns_pins[3].pin = GPIO_PIN7,
    .keypad_columns_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[3].logic = GPIO_LOW,
};

chr_lcd_4bit_t LCD1 = {
    .lcd_rs.port = GPIO_PORTC_INDEX, .lcd_rs.pin = GPIO_PIN0, .lcd_rs.direction = GPIO_DIRECTION_OUTPUT, .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = GPIO_PORTC_INDEX, .lcd_en.pin = GPIO_PIN1, .lcd_en.direction = GPIO_DIRECTION_OUTPUT, .lcd_en.logic = GPIO_LOW,
    
    .lcd_data[0].port = GPIO_PORTC_INDEX, .lcd_data[0].pin = GPIO_PIN2, .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = GPIO_PORTC_INDEX, .lcd_data[1].pin = GPIO_PIN3, .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = GPIO_PORTC_INDEX, .lcd_data[2].pin = GPIO_PIN4, .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = GPIO_PORTC_INDEX, .lcd_data[3].pin = GPIO_PIN5, .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[3].logic = GPIO_LOW,
};

chr_lcd_8bit_t LCD2 = {
    .lcd_rs.port = GPIO_PORTC_INDEX, .lcd_rs.pin = GPIO_PIN6, .lcd_rs.direction = GPIO_DIRECTION_OUTPUT, .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = GPIO_PORTC_INDEX, .lcd_en.pin = GPIO_PIN7, .lcd_en.direction = GPIO_DIRECTION_OUTPUT, .lcd_en.logic = GPIO_LOW,
    
    .lcd_data[0].port = GPIO_PORTD_INDEX, .lcd_data[0].pin = GPIO_PIN0, .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = GPIO_PORTD_INDEX, .lcd_data[1].pin = GPIO_PIN1, .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = GPIO_PORTD_INDEX, .lcd_data[2].pin = GPIO_PIN2, .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = GPIO_PORTD_INDEX, .lcd_data[3].pin = GPIO_PIN3, .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[3].logic = GPIO_LOW,
    .lcd_data[4].port = GPIO_PORTD_INDEX, .lcd_data[4].pin = GPIO_PIN4, .lcd_data[4].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[4].logic = GPIO_LOW,
    .lcd_data[5].port = GPIO_PORTD_INDEX, .lcd_data[5].pin = GPIO_PIN5, .lcd_data[5].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[5].logic = GPIO_LOW,
    .lcd_data[6].port = GPIO_PORTD_INDEX, .lcd_data[6].pin = GPIO_PIN6, .lcd_data[6].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[6].logic = GPIO_LOW,
    .lcd_data[7].port = GPIO_PORTD_INDEX, .lcd_data[7].pin = GPIO_PIN7, .lcd_data[7].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[7].logic = GPIO_LOW
};

void ecu_layer_initialize(){
    lcd_4bit_initialize(&LCD1);
    //lcd_8bit_initialize(&LCD2);
}
