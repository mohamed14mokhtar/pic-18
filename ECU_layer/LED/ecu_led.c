/* 
 * File:   ecu_led.c
 * Author: mokhtar
 *
 * Created on October 15, 2023, 7:11 AM
 */
#include"ecu_led.h"
#if LED_CONFIG == CONFIG_ENABLE
Std_ReturnType led_intialize(const led_t *led)
{
    Std_ReturnType ret =E_OK;
    pin_config_t pin_config ={.port = led->port_name ,
                              .pin = led->pin , 
                              .direction =GPIO_OUTPUT ,
                              .logic =led->led_sta };
    if(NULL == led)
    {
        ret =E_not_ok;
    }
    else
    {
        ret = GPIO_pIN_INTIALIZE(&pin_config);
    }
    return ret;
}
#endif

#if LED_CONFIG == CONFIG_ENABLE
Std_ReturnType led_turn_on(const led_t *led)
{
    Std_ReturnType ret =E_OK;
    pin_config_t pin_config ={.port = led->port_name ,
                              .pin = led->pin , 
                              .direction =GPIO_OUTPUT ,
                              .logic =led->led_sta };
    if(NULL == led)
    {
        ret =E_not_ok;
    }
    else
    {
       ret = GPIO_pIN_WRITE_LOGIC(&pin_config,GPIO_HIGH);
    }
    return ret;
}
#endif 

#if LED_CONFIG == CONFIG_ENABLE
Std_ReturnType led_turn_off(const led_t *led)
{
    Std_ReturnType ret =E_OK;
    pin_config_t pin_config ={.port = led->port_name ,
                              .pin = led->pin , 
                              .direction =GPIO_OUTPUT ,
                              .logic =led->led_sta };
    if(NULL == led)
    {
        ret =E_not_ok;
    }
    else
    {
        ret = GPIO_pIN_WRITE_LOGIC(&pin_config,GPIO_LOW);
    }
    return ret;
}
#endif 

#if LED_CONFIG == CONFIG_ENABLE
Std_ReturnType led_toggle(const led_t *led)
{
    Std_ReturnType ret =E_OK;
    pin_config_t pin_config ={.port = led->port_name ,
                              .pin = led->pin , 
                              .direction =GPIO_OUTPUT ,
                              .logic =led->led_sta };
    if(NULL == led)
    {
        ret =E_not_ok;
    }
    else
    {
        ret = GPIO_pIN_TOGGLE_LOGIC(&pin_config);
    }
    return ret;
}
#endif 