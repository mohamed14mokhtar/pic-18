/* 
 * File:   ecu_layer_init.c
 * Author: mokhtar
 *
 * Created on December 2, 2023, 6:03 PM
 */
#include"ecu_layer_init.h"




button_t button_1 ={
    .button_active=button_active_high,
    .button_state=button_relesed,
    .button_bin.direction=GPIO_INPUT,
    .button_bin.pin=pin2,
    .button_bin.port=PORTC_INDEX,
    .button_bin.logic=GPIO_LOW
};

button_t button_2 ={
    .button_active=button_active_high,
    .button_state=button_relesed,
    .button_bin.direction=GPIO_INPUT,
    .button_bin.pin=pin6,
    .button_bin.port=PORTC_INDEX,
    .button_bin.logic=GPIO_LOW
};

led_t led_1 ={
    .led_sta=led_off,
    .pin=pin1,
    .port_name=PORTC_INDEX
};

led_t led_2 ={
    .led_sta=led_off,
    .pin=pin4,
    .port_name=PORTC_INDEX
};

relay_t relay_1 ={
    .pin = pin0,
    .port = PORTC_INDEX,
    .relay_status = relay_state_off
};

relay_t relay_2 ={
    .pin = pin3,
    .port = PORTC_INDEX,
    .relay_status = relay_state_off
};


matrix_keypad_t matrix_keypad_1 ={
    .keymap_rows_pins[0].port=PORTD_INDEX,
    .keymap_rows_pins[0].pin=pin0,
    .keymap_rows_pins[0].direction=GPIO_OUTPUT,
    .keymap_rows_pins[0].logic=GPIO_LOW,
    .keymap_rows_pins[1].port=PORTD_INDEX,
    .keymap_rows_pins[1].pin=pin1,
    .keymap_rows_pins[1].direction=GPIO_OUTPUT,
    .keymap_rows_pins[1].logic=GPIO_LOW,
    .keymap_rows_pins[2].port=PORTD_INDEX,
    .keymap_rows_pins[2].pin=pin2,
    .keymap_rows_pins[2].direction=GPIO_OUTPUT,
    .keymap_rows_pins[2].logic=GPIO_LOW,
    .keymap_rows_pins[3].port=PORTD_INDEX,
    .keymap_rows_pins[3].pin=pin3,
    .keymap_rows_pins[3].direction=GPIO_OUTPUT,
    .keymap_rows_pins[3].logic=GPIO_LOW,
    .keymap_colums_pins[0].port=PORTD_INDEX,
    .keymap_colums_pins[0].pin=pin4,
    .keymap_colums_pins[0].direction=GPIO_INPUT,
    .keymap_colums_pins[0].logic=GPIO_LOW,
    .keymap_colums_pins[1].port=PORTD_INDEX,
    .keymap_colums_pins[1].pin=pin5,
    .keymap_colums_pins[1].direction=GPIO_INPUT,
    .keymap_colums_pins[1].logic=GPIO_LOW,
    .keymap_colums_pins[2].port=PORTD_INDEX,
    .keymap_colums_pins[2].pin=pin6,
    .keymap_colums_pins[2].direction=GPIO_INPUT,
    .keymap_colums_pins[2].logic=GPIO_LOW,
    .keymap_colums_pins[3].port=PORTD_INDEX,
    .keymap_colums_pins[3].pin=pin7,
    .keymap_colums_pins[3].direction=GPIO_INPUT,
    .keymap_colums_pins[3].logic=GPIO_LOW,
};


/*chr_lcd_8bit_t lcd_2 ={  
    .lcd_rs.port =PORTC_INDEX,
    .lcd_rs.pin =pin6,
    .lcd_rs.direction=GPIO_OUTPUT,
    .lcd_rs.logic=GPIO_LOW,
    .lcd_en.port =PORTC_INDEX,
    .lcd_en.pin =pin7,
    .lcd_en.direction=GPIO_OUTPUT,
    .lcd_en.logic=GPIO_LOW,
    .lcd_data[0].port =PORTD_INDEX,
    .lcd_data[0].pin =pin0,
    .lcd_data[0].direction=GPIO_OUTPUT,
    .lcd_data[0].logic=GPIO_LOW,
    .lcd_data[1].port =PORTD_INDEX,
    .lcd_data[1].pin =pin1,
    .lcd_data[1].direction=GPIO_OUTPUT,
    .lcd_data[1].logic=GPIO_LOW,
    .lcd_data[2].port =PORTD_INDEX,
    .lcd_data[2].pin =pin2,
    .lcd_data[2].direction=GPIO_OUTPUT,
    .lcd_data[2].logic=GPIO_LOW,
    .lcd_data[3].port =PORTD_INDEX,
    .lcd_data[3].pin =pin3,
    .lcd_data[3].direction=GPIO_OUTPUT,
    .lcd_data[3].logic=GPIO_LOW,
    .lcd_data[4].port =PORTD_INDEX,
    .lcd_data[4].pin =pin4,
    .lcd_data[4].direction=GPIO_OUTPUT,
    .lcd_data[4].logic=GPIO_LOW,
    .lcd_data[5].port =PORTD_INDEX,
    .lcd_data[5].pin =pin5,
    .lcd_data[5].direction=GPIO_OUTPUT,
    .lcd_data[5].logic=GPIO_LOW,
    .lcd_data[6].port =PORTD_INDEX,
    .lcd_data[6].pin =pin6,
    .lcd_data[6].direction=GPIO_OUTPUT,
    .lcd_data[6].logic=GPIO_LOW,
    .lcd_data[7].port =PORTD_INDEX,
    .lcd_data[7].pin =pin7,
    .lcd_data[7].direction=GPIO_OUTPUT,
    .lcd_data[7].logic=GPIO_LOW
};*/