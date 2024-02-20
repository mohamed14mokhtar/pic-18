/* 
 * File:   ecu_dc_motor.c
 * Author: mokhtar
 *
 * Created on October 31, 2023, 11:26 AM
 */#include "ecu_dc_motor.h"
Std_ReturnType motor_intialize (const motor_t *motor_pin) {
     Std_ReturnType ret =E_OK;
    if (NULL == motor_pin){
        ret =E_not_ok;
    }
    else
    {
        ret =GPIO_pIN_INTIALIZE(&(motor_pin->motor_pin_config[0]));
        ret =GPIO_pIN_INTIALIZE(&(motor_pin->motor_pin_config[1]));
    }
     return ret ;
}

Std_ReturnType morot_turn_right (const motor_t *motor_pin) {
     Std_ReturnType ret =E_OK;
    if (NULL == motor_pin){
        ret =E_not_ok;
    }
    else
    {
        ret =GPIO_pIN_WRITE_LOGIC(&(motor_pin->motor_pin_config[0]),GPIO_HIGH);
        ret =GPIO_pIN_WRITE_LOGIC(&(motor_pin->motor_pin_config[1]),GPIO_LOW);
    }
     return ret ;
}

Std_ReturnType morot_turn_left (const motor_t *motor_pin) {
    Std_ReturnType ret =E_OK;
    if (NULL == motor_pin){
        ret =E_not_ok;
    }
    else
    {
        ret =GPIO_pIN_WRITE_LOGIC(&(motor_pin->motor_pin_config[0]),GPIO_LOW);
        ret =GPIO_pIN_WRITE_LOGIC(&(motor_pin->motor_pin_config[1]),GPIO_HIGH);
    }
    return ret ;
}

Std_ReturnType morot_stop (const motor_t *motor_pin) {
    Std_ReturnType ret =E_OK;
    if (NULL == motor_pin){
        ret =E_not_ok;
    }
    else
    {
        ret =GPIO_pIN_WRITE_LOGIC(&(motor_pin->motor_pin_config[0]),GPIO_LOW);
        ret =GPIO_pIN_WRITE_LOGIC(&(motor_pin->motor_pin_config[1]),GPIO_LOW);
    }
    return ret ;
}
