/* 
 * File:   ecu_keymap.c
 * Author: mokhtar
 *
 * Created on November 25, 2023, 6:25 PM
 */
#include"ecu_keymap.h"
#define _XTAL_FREQ 4000000UL
static const uint8 value_ret [KEYMAP_MATRIX_ROWS][KEYMAP_MATRIX_COLUMS] = {
                                                                           {'7','8','9','/'},
                                                                           {'4','5','6','*'},
                                                                           {'1','2','3','-'},
                                                                           {'#','0','=','+'}
                                                                           };
Std_ReturnType keypad_intialize (const matrix_keypad_t *matrix_keypad){
    Std_ReturnType ret =E_OK;
    uint8 l_row_counter =0 ,l_colum_counter=0;
    if (NULL == matrix_keypad){
        ret =E_not_ok;
    }
    else{
        for(l_row_counter=0 ;l_row_counter <KEYMAP_MATRIX_ROWS; l_row_counter++){
            ret = GPIO_pIN_INTIALIZE (&(matrix_keypad->keymap_rows_pins[l_row_counter]));
        }
        for(l_colum_counter=0 ;l_colum_counter <KEYMAP_MATRIX_COLUMS; l_colum_counter++){
            ret = GPIO_pIN_DIRECTION_INTIALIZE (&(matrix_keypad->keymap_colums_pins[l_colum_counter]));
        }
    }
    return ret;
}
Std_ReturnType keypad_get_value (const matrix_keypad_t *matrix_keypad ,uint8 *value){
     Std_ReturnType ret =E_OK;
      uint8 l_row_counter =0 ,l_colum_counter=0 ,l_counter =0, colum_logic=0; 
    if ((NULL == matrix_keypad) || (NULL == value)){
        ret =E_not_ok;
    }
    else{
        for(l_row_counter=0 ;l_row_counter <KEYMAP_MATRIX_ROWS; l_row_counter++){
            for(l_counter=0 ;l_counter <KEYMAP_MATRIX_ROWS; l_counter++){
            ret = GPIO_pIN_WRITE_LOGIC (&(matrix_keypad->keymap_rows_pins[l_counter]),GPIO_LOW);
        }
            ret = GPIO_pIN_WRITE_LOGIC (&(matrix_keypad->keymap_rows_pins[l_row_counter]),GPIO_HIGH);
            __delay_ms(50);
            for(l_colum_counter=0 ;l_colum_counter <KEYMAP_MATRIX_ROWS; l_colum_counter++){
            ret = GPIO_pIN_READ_LOGIC (&(matrix_keypad->keymap_colums_pins[l_colum_counter]),&colum_logic);
            if(GPIO_HIGH == colum_logic){
                *value=value_ret[l_row_counter][l_colum_counter];
            }
        }
        }
    }
    return ret;
}


/*
 matrix_keypad_t matrix_keypad ={
    .keymap_rows_pins[0].port=PORTC_INDEX,
    .keymap_rows_pins[0].direction=GPIO_OUTPUT,
    .keymap_rows_pins[0].logic=GPIO_LOW,
    .keymap_rows_pins[0].pin=pin0,
    .keymap_rows_pins[1].port=PORTC_INDEX,
    .keymap_rows_pins[1].direction=GPIO_OUTPUT,
    .keymap_rows_pins[1].logic=GPIO_LOW,
    .keymap_rows_pins[1].pin=pin1,
    .keymap_rows_pins[2].port=PORTC_INDEX,
    .keymap_rows_pins[2].direction=GPIO_OUTPUT,
    .keymap_rows_pins[2].logic=GPIO_LOW,
    .keymap_rows_pins[2].pin=pin2,
    .keymap_rows_pins[3].port=PORTC_INDEX,
    .keymap_rows_pins[3].direction=GPIO_OUTPUT,
    .keymap_rows_pins[3].logic=GPIO_LOW,
    .keymap_rows_pins[3].pin=pin3,
    .keymap_colums_pins[0].port=PORTC_INDEX,
    .keymap_colums_pins[0].direction=GPIO_INPUT,
    .keymap_colums_pins[0].logic=GPIO_LOW,
    .keymap_colums_pins[0].pin=pin4,
    .keymap_colums_pins[1].port=PORTC_INDEX,
    .keymap_colums_pins[1].direction=GPIO_INPUT,
    .keymap_colums_pins[1].logic=GPIO_LOW,
    .keymap_colums_pins[1].pin=pin5,
    .keymap_colums_pins[2].port=PORTC_INDEX,
    .keymap_colums_pins[2].direction=GPIO_INPUT,
    .keymap_colums_pins[2].logic=GPIO_LOW,
    .keymap_colums_pins[2].pin=pin6,
    .keymap_colums_pins[3].port=PORTC_INDEX,
    .keymap_colums_pins[3].direction=GPIO_INPUT,
    .keymap_colums_pins[3].logic=GPIO_LOW,
    .keymap_colums_pins[3].pin=pin7
};
 */