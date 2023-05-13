
#include "ecu_chr_lcd.h"

static Std_ReturnType lcd_4bit_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command);
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column);
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column);

Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for(int i=0;i<4;i++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[i]));
        }
        __delay_ms(15);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, 0x80);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret = lcd_4bit_send_4bits(lcd, command >> 4);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_4bit_send_4bits(lcd, command);
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        ret = lcd_4bit_send_4bits(lcd, data >> 4);
        ret = lcd_4bit_send_enable_signal(lcd);
        ret = lcd_4bit_send_4bits(lcd, data);
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_char_data(lcd, data);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_NOT_OK;
    if((lcd == NULL) || (str == NULL)){
        ret = E_NOT_OK;
    }
    else{
        uint8 string_index;
        for(string_index = 0 ; str[string_index]!='\0' ; string_index++){
            lcd_4bit_send_char_data(lcd, str[string_index]);
        }
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret = E_NOT_OK;
    if((lcd == NULL) || (str == NULL)){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_string(lcd, str);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, const uint8 _chr[], uint8 mem_pos){
    Std_ReturnType ret = E_NOT_OK;
    uint8 lcd_counter;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos*8)));
        for(lcd_counter = 0;lcd_counter<8;lcd_counter++){
            ret = lcd_4bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}

Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for(int i=0;i<8;i++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[i]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret = gpio_port_write_logic((lcd->lcd_data->port), command);
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        ret = gpio_port_write_logic(lcd->lcd_data->port, data);
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_char_data(lcd, data);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_NOT_OK;
    if((lcd == NULL) || (str == NULL)){
        ret = E_NOT_OK;
    }
    else{
        uint8 string_index;
        for(string_index = 0 ; str[string_index]!='\0' ; string_index++){
            lcd_8bit_send_char_data(lcd, str[string_index]);
        }
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret = E_NOT_OK;
    if((lcd == NULL) || (str == NULL)){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_string(lcd, str);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, const uint8 _chr[], uint8 mem_pos){
    Std_ReturnType ret = E_NOT_OK;
    uint8 lcd_counter;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos*8)));
        for(lcd_counter = 0;lcd_counter<8;lcd_counter++){
            ret = lcd_8bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}

Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str, uint8 str_len){
    Std_ReturnType ret = E_NOT_OK;
    if(str == NULL){
        ret = E_NOT_OK;
    }
    else{
        memset(str, '\0', str_len);
        sprintf((char*)str, "%i", value);
    }
    return ret;
}

Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str, uint8 str_len){
    Std_ReturnType ret = E_NOT_OK;
    if(str == NULL){
        ret = E_NOT_OK;
    }
    else{
        memset(str, '\0', str_len);
        sprintf((char*)str, "%i", value);
    }
    return ret;
}

Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str, uint8 str_len){
    Std_ReturnType ret = E_NOT_OK;
    if(str == NULL){
        ret = E_NOT_OK;
    }
    else{
        memset(str, '\0', str_len);
        sprintf((char*)str, "%lu", value);
    }
    return ret;
}

static Std_ReturnType lcd_4bit_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command){
    Std_ReturnType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_data[0]), ((_data_command >> 0) & 0x01));
        ret = gpio_pin_write_logic(&(lcd->lcd_data[1]), ((_data_command >> 1) & 0x01));
        ret = gpio_pin_write_logic(&(lcd->lcd_data[2]), ((_data_command >> 2) & 0x01));
        ret = gpio_pin_write_logic(&(lcd->lcd_data[3]), ((_data_command >> 3) & 0x01));
    }
    return ret;
}

static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column){
    Std_ReturnType ret = E_NOT_OK;
    column--;
    switch(row){
        case ROW1: ret = lcd_4bit_send_command(lcd, (ROW1_Address + column)); break;
        case ROW2: ret = lcd_4bit_send_command(lcd, (ROW2_Address + column)); break;
        case ROW3: ret = lcd_4bit_send_command(lcd, (ROW3_Address + column)); break;
        case ROW4: ret = lcd_4bit_send_command(lcd, (ROW4_Address + column)); break;
        default: ret = E_NOT_OK; break;
    }
    return ret;
}

static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column){
    Std_ReturnType ret = E_NOT_OK;
    column--;
    switch(row){
        case ROW1: ret = lcd_8bit_send_command(lcd, (ROW1_Address + column)); break;
        case ROW2: ret = lcd_8bit_send_command(lcd, (ROW2_Address + column)); break;
        case ROW3: ret = lcd_8bit_send_command(lcd, (ROW3_Address + column)); break;
        case ROW4: ret = lcd_8bit_send_command(lcd, (ROW4_Address + column)); break;
        default: ret = E_NOT_OK; break;
    }
    return ret;
}
