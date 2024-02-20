/* 
 * File:   ecu_seg.c
 * Author: mokhtar
 *
 * Created on November 8, 2023, 7:56 AM
 */
#include"ecu_seg.h"

Std_ReturnType segment_intialized(const segment_t *segment){
    Std_ReturnType ret =E_OK;
    if (NULL == segment){
        ret =E_not_ok;
    }
    else{
        ret = GPIO_pIN_INTIALIZE(&(segment->seg_pins[segment_intialize_0]));
        ret = GPIO_pIN_INTIALIZE(&(segment->seg_pins[segment_intialize_1]));
        ret = GPIO_pIN_INTIALIZE(&(segment->seg_pins[segment_intialize_2]));
        ret = GPIO_pIN_INTIALIZE(&(segment->seg_pins[segment_intialize_3]));
    }
    return ret;
}
Std_ReturnType segment_wright_logic(const segment_t *segment , uint8 number){
    Std_ReturnType ret =E_OK;
    if (NULL == segment){
        ret =E_not_ok;
    }
    else{
        ret = GPIO_pIN_WRITE_LOGIC(&(segment->seg_pins[segment_intialize_0]),number & 0x01);
        ret = GPIO_pIN_WRITE_LOGIC(&(segment->seg_pins[segment_intialize_1]),(number>>1) & 0x01);
        ret = GPIO_pIN_WRITE_LOGIC(&(segment->seg_pins[segment_intialize_2]),(number>>2) & 0x01);
        ret = GPIO_pIN_WRITE_LOGIC(&(segment->seg_pins[segment_intialize_3]),(number>>3) & 0x01);
    }
    return ret;
}