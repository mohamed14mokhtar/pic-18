/* 
 * File:   ecu_relay.c
 * Author: mokhtar
 *
 * Created on October 29, 2023, 7:57 AM
 */
#include"ecu_relay.h"
/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_intialize (const relay_t *relay){
    Std_ReturnType ret =E_OK;
    pin_config_t pin_config ={.port =relay->port ,.pin =relay->pin 
                              ,.direction=GPIO_OUTPUT ,.logic = relay->relay_status};
    if( NULL == relay){
        ret =ret = E_not_ok;
    }
    else
    {
        ret =GPIO_pIN_INTIALIZE(&pin_config);
    }
    return ret;
}
/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_turn_on(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    pin_config_t pin_config ={.port =relay->port ,.pin =relay->pin 
                              ,.direction=GPIO_OUTPUT ,.logic = relay->relay_status};
    if(NULL == relay){
        ret =ret = E_not_ok;
    }
    else
    {
        ret =GPIO_pIN_WRITE_LOGIC(&pin_config ,GPIO_HIGH);
    }
    return ret;
}
/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_turn_off(const relay_t *relay){
    Std_ReturnType ret =E_OK;
    pin_config_t pin_config ={.port =relay->port ,.pin =relay->pin 
                              ,.direction=GPIO_OUTPUT ,.logic = relay->relay_status};
    if(NULL == relay){
        ret =ret =E_not_ok;
    }
    else
    {
        ret =GPIO_pIN_WRITE_LOGIC(&pin_config ,GPIO_LOW);
    }
    return ret;
}
/**
 * 
 * @param relay
 * @return 
 */
Std_ReturnType relay_toggle(const relay_t *relay){
     Std_ReturnType ret = E_OK;
    pin_config_t pin_config ={.port =relay->port ,.pin =relay->pin 
                              ,.direction=GPIO_OUTPUT ,.logic = relay->relay_status};
    if( NULL == relay){
        ret =ret = E_not_ok;
    }
    else
    {
        ret =GPIO_pIN_TOGGLE_LOGIC(&pin_config);
    }
    return ret;
}