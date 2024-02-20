/* 
 * File:   ecu_button.c
 * Author: mokhtar
 *
 * Created on October 27, 2023, 6:27 PM
 */
#include "ecu_button.h"
/**
 * 
 * @param button
 * @return 
 */
Std_ReturnType button_intialize (const button_t *button){
    Std_ReturnType ret =E_OK;
    if (NULL == button){
        ret =E_not_ok;
    }
    else{
        ret = GPIO_pIN_DIRECTION_INTIALIZE(&(button->button_bin));
    }
}
/**
 * \
 * @param button
 * @param button_state
 * @return 
 */
Std_ReturnType button_read_state (const button_t *button ,button_state_t *button_state){
    Std_ReturnType ret =E_not_ok;
    logic_t logic_button =GPIO_LOW;
    if ((NULL == button) || (NULL == button_state)){
        ret =E_not_ok;
    }
    else{
       ret = GPIO_pIN_READ_LOGIC(&(button->button_bin) ,&logic_button);
       if(button->button_active == button_active_high){
           if(GPIO_HIGH == logic_button){
               *button_state =button_pressed;
           }
           else{
               *button_state =button_relesed;
           }
       }
       else if(button->button_active == button_active_low){
           if(GPIO_HIGH == logic_button){
               *button_state =button_relesed;
           }
           else{
               *button_state =button_pressed;
           }
       }
       else {
           /* no thing */
       }
       ret =E_OK;
    }
}