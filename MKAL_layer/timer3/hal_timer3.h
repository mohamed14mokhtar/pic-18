/* 
 * File:   hal_timer3.h
 * Author: mokhtar
 *
 * Created on February 4, 2024, 5:06 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/*section : includes */
#include"hal_timer3_cfg.h"
#include"../mkal_std_types.h"
#include"../pic18_chip_select.h"
#include"../Interrupt/mcal_internal_interrupt.h"
#include"../gpio/pro_gpio.h"
/*section : macro declarations  */
#define TIMER3_enable  1
#define TIMER3_disable 0

#define TIMER3_source_external  1
#define TIMER3_source_internal  0

#define TIMER3_Asynchronize_clock_input  1
#define TIMER3_synchronize_clock_input   0

#define TIMER3_8bit_cfg  0
#define TIMER3_16bit_cfg 1
/*section : macro declaration functions  */
#define TIMER3_ENABLE()  (T3CONbits.TMR3ON =1)
#define TIMER3_DISABLE() (T3CONbits.TMR3ON =0)

#define TIMER3_SOURCE_EXTERNAL_CFG() (T3CONbits.TMR3CS =1)
#define TIMER3_SOURCE_INTERNAL_CFG() (T3CONbits.TMR3CS =0)

#define TIMER1_ASYNCH_clock_input_CFG() (T3CONbits.nT3SYNC =1)
#define TIMER1_SYNCH_clock_input_CFG()  (T3CONbits.nT3SYNC =0)

#define TIMER3_prescaler_div_by(_value_) (T3CONbits.T3CKPS = _value_);

#define TIMER3_8BIT_CFG()  (T3CONbits.RD16 =0)
#define TIMER3_16BIT_CFG() (T3CONbits.RD16 =1)
/*section : data type declarations  */
typedef enum {
    Prescale_value_div_1,
    Prescale_value_div_2,
    Prescale_value_div_4,
    Prescale_value_div_8
}timer3_prescaler_t;

typedef struct {
    #if TIMER3_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
    void (* Timer3_handler)(void);
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
    INTERRUPT_PRIORITY_t INTERRUPT_PRIORITY;
#endif
#endif
    uint16 timer3_preload_value ;
    uint8 timer3_prescaler_cfg :2;
    uint8 timer3_mode          :1;
    uint8 timer3_counter_mode  :1; /*Asynch / synch */
    uint8 timer3_wr__reg_cfg   :1;
    uint8 timer3_reserved      :3;
}Timer3_t;
/*section : functions declarations  */
Std_ReturnType Timer3_init   (const Timer3_t *Timer3);
Std_ReturnType Timer3_deinit (const Timer3_t *Timer3);
Std_ReturnType Timer3_write_value (const Timer3_t *Timer3,uint16 value);
Std_ReturnType Timer3_read_value (const Timer3_t *Timer3,uint16 *value);
#endif	/* HAL_TIMER3_H */



/*
void timer0_callback_1 (void);
void timer1_callback_1 (void);
void timer2_callback_1 (void);
void timer3_callback_1 (void);
Std_ReturnType ret =E_not_ok;

volatile uint16 counter_1=0,counter_2=0 ;
led_t led_1 ={.led_sta=led_off,.pin=pin0,.port_name=PORTD_INDEX};
led_t led_2 ={.led_sta=led_off,.pin=pin1,.port_name=PORTD_INDEX};
Timer0_t Timer0_1 ={ .Timer0_handler=timer0_callback_1,.prescaler_enable=TIMER0_prescalering_enable,
                     .timer0_counter_edge=TIMER0_rising_edge,.timer0_mode=TIMER0_source_internal,
                     .Prescaler_Select=prescale_value_div_by_4,.timer0_register_size=TIMER0_16bit_cfg,
                     .timer_preload_value=3036
                     };

Timer2_t Timer2_1 ={.Timer2_handler=timer2_callback_1,.INTERRUPT_PRIORITY=INTERRUPT_HUGH_PRIORITY,
                    .timer1_preload_value=249,.timer2_postscaler_cfg=Postscale_div_by_4,
                    .timer2_prescaler_cfg=prescale_div_by_1};

Timer3_t Timer3_1={.Timer3_handler=timer3_callback_1,.timer3_mode=TIMER3_source_internal,.timer3_preload_value=3036,
                   .timer3_prescaler_cfg=Prescale_value_div_8,.timer3_wr__reg_cfg=TIMER3_8bit_cfg};

Timer1_t Timer1_1 ={.Timer1_handler=timer1_callback_1,.timer1_mode=TIMER1_source_internal,
                    .timer1_osc_cfg=TIMER1_oscillator_disable,.timer1_preload_value=3036,
                    .timer1_prescaler_cfg=prescale_value_timer1_div_by_4,.timer1_wr__reg_cfg=TIMER1_8bit_cfg};

Timer3_t Timer3_2 ={.Timer3_handler=NULL,.timer3_counter_mode=TIMER3_Asynchronize_clock_input,
                    .timer3_mode=TIMER3_source_external,.timer3_preload_value=0,.timer3_prescaler_cfg=Prescale_value_div_1
                    ,.timer3_wr__reg_cfg=TIMER1_8bit_cfg};

    ret =Timer3_init(&Timer3_2);
    ret =Timer1_init(&Timer1_1);
    ret = led_intialize(&led_1);
    ret = led_intialize(&led_2);
 * 
 */