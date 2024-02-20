/* 
 * File:   pro_gpio.c
 * Author: mokhtar
 *
 * Created on October 15, 2023, 6:49 AM
 */
#include"pro_gpio.h"

volatile uint8 *tris_regisrers [] ={&TRISA ,&TRISB ,&TRISC ,&TRISD ,&TRISE};
volatile uint8 *port_regisrers [] ={&PORTA ,&PORTB ,&PORTC ,&PORTD ,&PORTE};
volatile uint8 *lat_regisrers  [] = {&LATA ,&LATB ,&LATC ,&LATD ,&LATE};

#if GPIO_PIN_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType GPIO_pIN_DIRECTION_INTIALIZE(const pin_config_t *config_pin)
{
    Std_ReturnType ret =E_OK;
    if ((NULL == config_pin) || (config_pin->pin > PIN_MAXSIZE-1)){
        ret =E_not_ok;
    }
    else{
        switch (config_pin->direction){
            case GPIO_OUTPUT :
                CLEAR_BIT(*tris_regisrers[config_pin->port] ,config_pin->pin);
                break;
            case GPIO_INPUT :
                SIT_BIT(*tris_regisrers[config_pin->port] ,config_pin->pin);
                break;
            default : ret =E_not_ok; 
        }
    }
    return ret;
}
#endif

#if GPIO_PIN_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType GPIO_pIN_DIRECTION_STATUS(const pin_config_t *config_pin ,direction_t *dirction)
{
    Std_ReturnType ret =E_OK;
    if ((NULL == config_pin) || (config_pin->pin > PIN_MAXSIZE-1) || (NULL == dirction)){
        ret =E_not_ok;
    }
    else{
        *dirction=READ_BIIT(*tris_regisrers[config_pin->port] ,config_pin->pin);
    }
    return ret;
}
#endif

#if GPIO_PIN_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType GPIO_pIN_WRITE_LOGIC(const pin_config_t *config_pin ,logic_t logic)
{
    Std_ReturnType ret =E_OK;
    if ((NULL == config_pin) || (config_pin->pin > PIN_MAXSIZE-1)){
        ret =E_not_ok;
    }
    else{
        switch (logic){
            case GPIO_LOW:
                CLEAR_BIT(*lat_regisrers[config_pin->port],config_pin->pin);
                break;
            case GPIO_HIGH :
                SIT_BIT(*lat_regisrers[config_pin->port],config_pin->pin);
                break;
            default :ret=E_not_ok;
        }
    }
    return ret;
}
#endif

#if GPIO_PIN_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType GPIO_pIN_INTIALIZE(const pin_config_t *config_pin)
{
     Std_ReturnType ret =E_OK;
    if ((NULL == config_pin) || (config_pin->pin > PIN_MAXSIZE-1)){
        ret =E_not_ok;
    }
    else{
        ret =GPIO_pIN_DIRECTION_INTIALIZE(config_pin);
        ret =GPIO_pIN_WRITE_LOGIC(config_pin,config_pin->logic);
    }
    return ret;
}
#endif

#if GPIO_PIN_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType GPIO_pIN_READ_LOGIC  (const pin_config_t *config_pin ,logic_t *logic)
{
    Std_ReturnType ret =E_OK;
    if ((NULL == config_pin) || (config_pin->pin > PIN_MAXSIZE-1) || (NULL == logic)){
        ret =E_not_ok;
    }
    else{
        *logic =READ_BIIT(*port_regisrers[config_pin->port] ,config_pin->pin);
    }
    return ret;
}
#endif

#if GPIO_PIN_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType GPIO_pIN_TOGGLE_LOGIC(const pin_config_t *config_pin)
{
    Std_ReturnType ret =E_OK;
    if ((NULL == config_pin) || (config_pin->pin > PIN_MAXSIZE-1)){
        ret =E_not_ok;
    }
    else{
        TOGGLE_BIT(*lat_regisrers[config_pin->port],config_pin->pin);
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType GPIO_PORT_DIRECTION_INTIALIZE(port_index_t port, uint8 direction)
{
    Std_ReturnType ret =E_OK;
    if(port > PORT_MAXSIZE-1){
        ret = E_not_ok;
    }
    else{
        *tris_regisrers[port] = direction;
    }

    return ret;
}
#endif

#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType GPIO_PORT_DIRECTION_STATUS(port_index_t port ,uint8 *dirction_status)
{
    Std_ReturnType ret =E_OK;
    if ((NULL == dirction_status) || (port > PORT_MAXSIZE-1)){
        ret =E_not_ok;
    }
    else{
        *dirction_status = *tris_regisrers[port];
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType GPIO_PORT_WRITE_LOGIC(port_index_t port ,uint8 logic)
{
    Std_ReturnType ret =E_OK;
    if(port > PORT_MAXSIZE-1){
        ret = E_not_ok;
    }
    else {
        *lat_regisrers[port] =logic ;
    }
   
    return ret;
}
#endif

#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType GPIO_PORT_READ_LOGIC(port_index_t port ,uint8 *logic)
{
    Std_ReturnType ret =E_OK;
     if ((NULL == logic) || (port > PORT_MAXSIZE-1)){
        ret =E_not_ok;
    }
    else{
        *tris_regisrers[port] = *logic;
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGRATION == CONFIG_ENABLE
Std_ReturnType GPIO_PORT_TOGGLE_LOGIC(port_index_t port)
{
    Std_ReturnType ret =E_OK;
    if(port > PORT_MAXSIZE-1)
    {
        ret =E_not_ok;
    }
    else
    {
        *lat_regisrers[port] ^= PORTC_MASK;
    }
    return ret;
}
#endif