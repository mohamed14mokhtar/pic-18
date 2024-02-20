/* 
 * File:   hal_timer2.h
 * Author: mokhtar
 *
 * Created on February 4, 2024, 5:05 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/*section : includes */
#include"hal_timer2_cfg.h"
#include"../mkal_std_types.h"
#include"../pic18_chip_select.h"
#include"../Interrupt/mcal_internal_interrupt.h"
#include"../gpio/pro_gpio.h"
/*section : macro declarations  */
#define TIMER2_enable  1
#define TIMER2_disable 0
/*section : macro declaration functions  */
#define TIMER2_ENABLE()  (T2CONbits.TMR2ON = 1)
#define TIMER2_DISABLE() (T2CONbits.TMR2ON = 0)

#define TIMER2_prescaler_div_by(_value_)  (T2CONbits.T2CKPS = _value_);
#define TIMER2_postscaler_div_by(_value_) (T2CONbits.TOUTPS = _value_);

/*section : data type declarations  */
typedef enum {
    Postscale_div_by_1,
    Postscale_div_by_2,
    Postscale_div_by_3,
    Postscale_div_by_4,
    Postscale_div_by_5,
    Postscale_div_by_6,
    Postscale_div_by_7,
    Postscale_div_by_8,
    Postscale_div_by_9,
    Postscale_div_by_10,
    Postscale_div_by_11,
    Postscale_div_by_12,
    Postscale_div_by_13,
    Postscale_div_by_14,
    Postscale_div_by_15,
    Postscale_div_by_16
}Postscale_select_t;

typedef enum {
    prescale_div_by_1,
    prescale_div_by_4,
    prescale_div_by_16
}prescale_select_t;

typedef struct {
    #if TIMER0_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
    void (* Timer2_handler)(void);
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
    INTERRUPT_PRIORITY_t INTERRUPT_PRIORITY;
#endif
#endif
    uint8 timer1_preload_value ;
    uint8 timer2_postscaler_cfg :4;
    uint8 timer2_prescaler_cfg  :2;
    uint8 timer2_reserved       :2;
    
}Timer2_t;
/*section : functions declarations  */
Std_ReturnType Timer2_init   (const Timer2_t *Timer2);
Std_ReturnType Timer2_deinit (const Timer2_t *Timer2);
Std_ReturnType Timer2_write_value (const Timer2_t *Timer2,uint8 value);
Std_ReturnType Timer2_read_value (const Timer2_t *Timer2,uint8 *value);


#endif	/* HAL_TIMER2_H */

