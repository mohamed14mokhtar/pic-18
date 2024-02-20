/* 
 * File:   ecu_relay.h
 * Author: mokhtar
 *
 * Created on October 29, 2023, 7:57 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/*section : includes */
#include"../../MKAL_layer/gpio/pro_gpio.h"
#include"ecu_relay_cgf.h"
/*section : macro declarations  */


/*section : macro declaration functions  */


/*section : data type declarations  */
typedef enum {
    relay_state_off,
    relay_state_on
}relay_status_t;

typedef struct {
    uint8 port :4;
    uint8 pin  :3;
    uint8 relay_status :1;
}relay_t;
/*section : functions declarations  */
Std_ReturnType relay_intialize (const relay_t *relay);
Std_ReturnType relay_turn_on(const relay_t *relay);
Std_ReturnType relay_turn_off(const relay_t *relay);
Std_ReturnType relay_toggle(const relay_t *relay);

#endif	/* ECU_RELAY_H */

