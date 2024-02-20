/* 
 * File:   ecu_led.h
 * Author: mokhtar
 *
 * Created on October 15, 2023, 7:11 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/*section : includes */
#include"../../MKAL_layer/gpio/pro_gpio.h"
#include "ecu_led_con.h"
/*section : macro declarations  */


/*section : macro declaration functions  */


/*section : data type declarations  */
typedef enum {
    led_off,
    led_on
}led_status;

typedef struct {
    uint8 port_name :4;
    uint8 pin :3;
    uint8 led_sta :1;
}led_t;
/*section : functions declarations  */
Std_ReturnType led_intialize(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_toggle(const led_t *led);
#endif	/* ECU_LED_H */

//led_t led_1 ={.port_name=PORTD_INDEX,.pin=pin0,.led_sta=led_off};