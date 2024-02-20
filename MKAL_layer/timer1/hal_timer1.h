/* 
 * File:   hal_timer1.h
 * Author: mokhtar
 *
 * Created on February 3, 2024, 6:40 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/*section : includes */
#include"hal_timer1_cfg.h"
#include"../mkal_std_types.h"
#include"../pic18_chip_select.h"
#include"../Interrupt/mcal_internal_interrupt.h"
#include"../gpio/pro_gpio.h"
/*section : macro declarations  */
#define TIMER1_enable  1
#define TIMER1_disable 0

#define TIMER1_source_external  1
#define TIMER1_source_internal  0

#define TIMER1_Asynchronize_clock_input  1
#define TIMER1_synchronize_clock_input   0

#define TIMER1_oscillator_enable    1
#define TIMER1_oscillator_disable   0

#define Main_system_clockis_derived_from_Timer1_oscillator 1
#define Main_system_clockis_derived_from_another_source    0

#define TIMER1_8bit_cfg  0
#define TIMER1_16bit_cfg 1

#define prescale_value_timer1_div_by_1 0
#define prescale_value_timer1_div_by_2 1
#define prescale_value_timer1_div_by_4 2
#define prescale_value_timer1_div_by_8 3
/*section : macro declaration functions  */
#define TIMER1_ENABLE()  (T1CONbits.TMR1ON =1)
#define TIMER1_DISABLE() (T1CONbits.TMR1ON =0)

#define TIMER1_SOURCE_EXTERNAL_CFG() (T1CONbits.TMR1CS =1)
#define TIMER1_SOURCE_INTERNAL_CFG() (T1CONbits.TMR1CS =0)

#define TIMER1_ASYNCH_clock_input_CFG() (T1CONbits.nT1SYNC =1)
#define TIMER1_SYNCH_clock_input_CFG()  (T1CONbits.nT1SYNC =0)

#define TIMER1_OSCILLATOR_ENABLE()  (T1CONbits.T1OSCEN =1)
#define TIMER1_OSCILLATOR_DISABLE() (T1CONbits.T1OSCEN =0)

#define TIMER1_prescaler_div_by(_value_) (T1CONbits.T1CKPS = _value_);

#define Main_system_Clockis_Derived_From_Timer1_Oscillator()  (T1CONbits.T1RUN =1)
#define Main_System_Clockis_Derived_From_Another_Source()     (T1CONbits.T1RUN =0)

#define TIMER1_8BIT_CFG()  (T1CONbits.RD16 =0)
#define TIMER1_16BIT_CFG() (T1CONbits.RD16 =1)


/*section : data type declarations  */


typedef struct {
#if TIMER1_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
    void (* Timer1_handler)(void);
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
    INTERRUPT_PRIORITY_t INTERRUPT_PRIORITY;
#endif
#endif
    uint16 timer1_preload_value ;
    uint8 timer1_prescaler_cfg :2;
    uint8 timer1_mode          :1;
    uint8 timer1_counter_mode  :1; /*Asynch / synch */
    uint8 timer1_osc_cfg       :1;
    uint8 timer1_wr__reg_cfg   :1;
    uint8 timer1_reserved      :2;
    
}Timer1_t;
/*section : functions declarations  */
Std_ReturnType Timer1_init   (const Timer1_t *Timer1);
Std_ReturnType Timer1_deinit (const Timer1_t *Timer1);
Std_ReturnType Timer1_write_value (const Timer1_t *Timer1,uint16 value);
Std_ReturnType Timer1_read_value (const Timer1_t *Timer1,uint16 *value);

#endif	/* HAL_TIMER1_H */

