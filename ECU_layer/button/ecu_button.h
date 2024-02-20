/* 
 * File:   ecu_button.h
 * Author: mokhtar
 *
 * Created on October 27, 2023, 6:27 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H
/*section : includes */
#include"ecu_button_cfg.h"
#include"../../MKAL_layer/gpio/pro_gpio.h"
/*section : macro declarations  */


/*section : macro declaration functions  */


/*section : data type declarations  */
typedef enum {
    button_relesed,
    button_pressed
}button_state_t;

typedef enum{
    button_active_high,
    button_active_low   
}button_active_t;
typedef struct {
    pin_config_t button_bin;
    button_state_t button_state;
    button_active_t button_active;
}button_t;
/*section : functions declarations  */
Std_ReturnType button_intialize (const button_t *button);
Std_ReturnType button_read_state (const button_t *button ,button_state_t *button_state);


#endif	/* ECU_BUTTON_H */

