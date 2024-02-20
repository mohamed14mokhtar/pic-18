/* 
 * File:   ecu_dc_motor.h
 * Author: mokhtar
 *
 * Created on October 31, 2023, 11:26 AM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/*section : includes */
#include"ecu_dc_motor_cfg.h"
#include"../../MKAL_layer/gpio/pro_gpio.h"
/*section : macro declarations  */


/*section : macro declaration functions  */


/*section : data type declarations  */
typedef enum {
    motor_turn_on,
    motor_turn_off
}motor_status_t;

typedef struct {
    pin_config_t motor_pin_config[2];
}motor_t;
/*section : functions declarations  */
Std_ReturnType motor_intialize (const motor_t *motor_pin);
Std_ReturnType morot_turn_right (const motor_t *motor_pin);
Std_ReturnType morot_turn_left (const motor_t *motor_pin);
Std_ReturnType morot_stop (const motor_t *motor_pin);
#endif	/* ECU_DC_MOTOR_H */

