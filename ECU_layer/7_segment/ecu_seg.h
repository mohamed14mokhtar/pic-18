/* 
 * File:   ecu_seg.h
 * Author: mokhtar
 *
 * Created on November 8, 2023, 7:56 AM
 */

#ifndef ECU_SEG_H
#define	ECU_SEG_H
/*section : includes */
#include"../../MKAL_layer/gpio/pro_gpio.h"
#include"ecu_seg_cfg.h"
/*section : macro declarations  */


/*section : macro declaration functions  */


/*section : data type declarations  */
typedef enum {
    seg_common_anode,
    seg_common_cathod
}seg_status_t;
typedef enum {
    segment_intialize_0 ,
    segment_intialize_1 ,
    segment_intialize_2 ,
    segment_intialize_3
}segment_number;

typedef struct {
    pin_config_t seg_pins[4];
    seg_status_t seg_status; 
}segment_t;
/*section : functions declarations  */
Std_ReturnType segment_intialized(const segment_t *segment);
Std_ReturnType segment_wright_logic(const segment_t *segment , uint8 number);
#endif	/* ECU_SEG_H */

