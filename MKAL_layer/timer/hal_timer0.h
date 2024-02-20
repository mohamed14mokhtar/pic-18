/* 
 * File:   hal_timer0.h
 * Author: mokhtar
 *
 * Created on February 3, 2024, 12:38 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H
/*section : includes */
#include"hal_timer0_cfg.h"
#include"../mkal_std_types.h"
#include"../pic18_chip_select.h"
#include"../Interrupt/mcal_internal_interrupt.h"
#include"../gpio/pro_gpio.h"
/*section : macro declarations  */
#define TIMER0_enable  1
#define TIMER0_disable 0

#define TIMER0_8bit_cfg  1
#define TIMER0_16bit_cfg 0

#define TIMER0_source_external 1
#define TIMER0_source_internal 0

#define TIMER0_falling_edge 1
#define TIMER0_rising_edge  0

#define TIMER0_prescalering_enable  0
#define TIMER0_prescalering_disable 1
/*section : macro declaration functions  */
#define TIMER0_ENABLE()  (T0CONbits.TMR0ON =1)
#define TIMER0_DISABLE() (T0CONbits.TMR0ON =0)

#define TIMER0_8BIT_CFG()  (T0CONbits.T08BIT =1)
#define TIMER0_16BIT_CFG() (T0CONbits.T08BIT =0)

#define TIMER0_SOURCE_EXTERNAL() (T0CONbits.T0CS =1)
#define TIMER0_SOURCE_INTERNAL() (T0CONbits.T0CS =0)

#define TIMER0_FALLING_EDGE() (T0CONbits.T0SE =1)
#define TIMER0_RISING_EDGE()  (T0CONbits.T0SE =0)

#define TIMER0_PRESCALERING_ENABLE()  (T0CONbits.PSA =0)
#define TIMER0_PRESCALERING_DISABLE() (T0CONbits.PSA =1)
/*section : data type declarations  */
typedef enum {
    prescale_value_div_by_2,
    prescale_value_div_by_4,
    prescale_value_div_by_8,
    prescale_value_div_by_16,
    prescale_value_div_by_32,
    prescale_value_div_by_64,
    prescale_value_div_by_128,
    prescale_value_div_by_256
}Prescaler_Select_t ;

typedef struct{
#if TIMER0_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
    void (* Timer0_handler)(void);
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
    INTERRUPT_PRIORITY_t INTERRUPT_PRIORITY;
#endif
#endif
    Prescaler_Select_t Prescaler_Select;
    uint16 timer_preload_value ;
    uint8 prescaler_enable     :1;
    uint8 timer0_counter_edge  :1;
    uint8 timer0_mode          :1;
    uint8 timer0_register_size :1;
    uint8 timer0_reserved      :4;
}Timer0_t;
/*section : functions declarations  */
Std_ReturnType Timer0_init   (const Timer0_t *Timer0);
Std_ReturnType Timer0_deinit (const Timer0_t *Timer0);
Std_ReturnType Timer0_write_value (const Timer0_t *Timer0,uint16 value);
Std_ReturnType Timer0_read_value (const Timer0_t *Timer0,uint16 *value);
#endif	/* HAL_TIMER0_H */

/* TIMER0 L/H = 2^n ? ((delay * Fosc) / (4 * Prescaler)) */


/*
 Timer0_t Timer0_1 ={ .Prescaler_Select=prescale_value_div_by_4,.Timer0_handler=ADC_callback,
                     .prescaler_enable=TIMER0_prescalering_enable,
                     .timer0_counter_edge=TIMER0_rising_edge,.timer0_mode=TIMER0_source_internal,
                     .timer0_register_size=TIMER0_16bit_cfg
                     ,.timer_preload_value=3036};


uint16 read_value=0,write_value=3036;
Timer0_t Timer0_2 ={.Prescaler_Select=prescale_value_div_by_4,.prescaler_enable=TIMER0_prescalering_enable,
                    .timer0_counter_edge=TIMER0_rising_edge,.timer0_mode=TIMER0_source_internal,
                     .timer0_register_size=TIMER0_16bit_cfg
                     ,.timer_preload_value=3036};
 
 */