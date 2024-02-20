/* 
 * File:   pro_gpio.h
 * Author: mokhtar
 *
 * Created on October 15, 2023, 6:49 AM
 */

#ifndef PRO_GPIO_H
#define	PRO_GPIO_H

/*section : includes */
//#include"../pic18_chip_select.h"
#include"../mkal_std_types.h"
#include"../device_config.h"
/*section : includes */

/*section : macro declarations  */
#define BIT_MASK (uint8)1

#define PIN_MAXSIZE     8
#define PORT_MAXSIZE    5

#define GPIO_PIN_CONFIGRATION CONFIG_ENABLE
#define GPIO_PORT_CONFIGRATION CONFIG_ENABLE

#define PORTC_MASK 0xFF
#define _XTAL_FREQ 8000000UL
/*section : macro declaration functions  */
#define HWREG8(adres)        (*((volatile uint8 *)(adres)))

#define SIT_BIT(reg ,bit_pos)          (reg |=  (BIT_MASK << bit_pos))
#define TOGGLE_BIT(reg ,bit_pos)       (reg ^=  (BIT_MASK << bit_pos))
#define CLEAR_BIT(reg ,bit_pos)        (reg &= ~(BIT_MASK << bit_pos))
#define READ_BIIT(reg ,bit_pos)        ((reg >> bit_pos) & BIT_MASK)
/*section : data type declarations  */
typedef enum {
    GPIO_LOW=0,
    GPIO_HIGH
}logic_t;
typedef enum{
    GPIO_OUTPUT=0,
    GPIO_INPUT
}direction_t;
typedef enum {
    pin0=0,
    pin1,
    pin2,
    pin3,
    pin4,
    pin5,
    pin6,
    pin7
}pin_index_t;
typedef enum {
    PORTA_INDEX=0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;
typedef struct {
    uint8 port       :3 ; /* @ref port_index_t */
    uint8 pin        :3 ; /* @ref pin_index_t  */
    uint8 direction  :1 ; /* @ref direction_t  */
    uint8 logic      :1 ; /* @ref logic_t      */
}pin_config_t;

/*section : functions declarations  */
/**
 * 
 * @param config_pin
 * @return 
 */
Std_ReturnType GPIO_pIN_INTIALIZE(const pin_config_t *config_pin);
Std_ReturnType GPIO_pIN_DIRECTION_INTIALIZE(const pin_config_t *config_pin);
Std_ReturnType GPIO_pIN_DIRECTION_STATUS(const pin_config_t *config_pin ,direction_t *dirction);
Std_ReturnType GPIO_pIN_WRITE_LOGIC(const pin_config_t *config_pin ,logic_t logic);
Std_ReturnType GPIO_pIN_READ_LOGIC  (const pin_config_t *config_pin ,logic_t *logic);
Std_ReturnType GPIO_pIN_TOGGLE_LOGIC(const pin_config_t *config_pin);

Std_ReturnType GPIO_PORT_DIRECTION_INTIALIZE(port_index_t port, uint8 direction);
Std_ReturnType GPIO_PORT_DIRECTION_STATUS(port_index_t port ,uint8 *dirction_status);
Std_ReturnType GPIO_PORT_WRITE_LOGIC(port_index_t port ,uint8 logic);
Std_ReturnType GPIO_PORT_READ_LOGIC(port_index_t port ,uint8 *logic);
Std_ReturnType GPIO_PORT_TOGGLE_LOGIC(port_index_t port);

#endif	/* PRO_GPIO_H */

