/* 
 * File:   ecu_keymap.h
 * Author: mokhtar
 *
 * Created on November 25, 2023, 6:25 PM
 */

#ifndef ECU_KEYMAP_H
#define	ECU_KEYMAP_H
/*section : includes */
#include "ecu_keymap_cgf.h"
#include"../../MKAL_layer/gpio/pro_gpio.h"
/*section : macro declarations  */
#define KEYMAP_MATRIX_ROWS    4
#define KEYMAP_MATRIX_COLUMS  4

/*section : macro declaration functions  */


/*section : data type declarations  */
typedef struct {
    pin_config_t keymap_rows_pins[KEYMAP_MATRIX_ROWS];
    pin_config_t keymap_colums_pins[KEYMAP_MATRIX_COLUMS];
}matrix_keypad_t;
/*section : functions declarations  */
Std_ReturnType keypad_intialize (const matrix_keypad_t *matrix_keypad);
Std_ReturnType keypad_get_value (const matrix_keypad_t *matrix_keypad ,uint8 *value);

#endif	/* ECU_KEYMAP_H */

