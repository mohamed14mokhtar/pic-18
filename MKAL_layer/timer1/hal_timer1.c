/* 
 * File:   hal_timer1.c
 * Author: mokhtar
 *
 * Created on February 3, 2024, 6:40 PM
 */

#include"hal_timer1.h"

static void (* TIMER1_Interrupthandler)(void);
static void timer1_mode_cfg (const Timer1_t *Timer1);
static void timer1_reg_bit_cfg (const Timer1_t *Timer1);
static void timer1_osc_cfg (const Timer1_t *Timer1);

static uint16 Timer1_preload;

Std_ReturnType Timer1_init (const Timer1_t *Timer1){
    Std_ReturnType ret = E_not_ok;
    if (NULL == Timer1){
        ret =E_not_ok;
    }
    else
    {
        /* disable timer1 */
        TIMER1_DISABLE();
        /* prescaler */
        TIMER1_prescaler_div_by(Timer1->timer1_prescaler_cfg);
        /* timer1 mode timer or counter */
        timer1_mode_cfg(Timer1);
        /* cfg of bit  */
        timer1_reg_bit_cfg(Timer1);
        /* oscillator */
        timer1_osc_cfg(Timer1);
        /* write value */
         TMR1H = ((Timer1->timer1_preload_value) >> 8);
         TMR1L = (uint8)(Timer1->timer1_preload_value);
         /* return value of start */
         Timer1_preload = Timer1->timer1_preload_value;
        /* interrupt */
#if TIMER1_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_INTERRUPT_FLAGE_CLEAR();
        TIMER1_Interrupthandler = Timer1->Timer1_handler;
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
        
        INTERRUPT_prioritylevelenable();
        if(Timer1->INTERRUPT_PRIORITY == INTERRUPT_HUGH_PRIORITY){
            INTERRUPT_globalinterrupthighenable();
            TIMER1_INTERRUPT_high_priority_set();
        }
        else if(Timer1->INTERRUPT_PRIORITY == INTERRUPT_LOW_PRIORITY){
            INTERRUPT_globalinterruptlowenable();
            TIMER1_INTERRUPT_low_priority_set();
        }
        else{ /*nothing*/ }
#else 
        INTERRUPT_globalinterruptenable();
        INTERRUPT_peripheralinterruptenable();
       
#endif        
#endif   
        /* enable timer1 */
        TIMER1_ENABLE();
        ret =E_OK;
    }
    return ret;
}

Std_ReturnType Timer1_deinit (const Timer1_t *Timer1){
    Std_ReturnType ret = E_not_ok;
    if (NULL == Timer1){
        ret =E_not_ok;
    }
    else
    {
        TIMER1_DISABLE();
#if TIMER1_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
        TIMER1_INTERRUPT_disABLE();
#endif
        ret =E_OK;
    }
    return ret;
}

Std_ReturnType Timer1_write_value (const Timer1_t *Timer1,uint16 value){
    Std_ReturnType ret = E_not_ok;
    if (NULL == Timer1){
        ret =E_not_ok;
    }
    else
    {
        TMR1H = (value >> 8);
        TMR1L = (uint8)(value);  
        ret =E_OK;
    }
    return ret;
}

Std_ReturnType Timer1_read_value (const Timer1_t *Timer1,uint16 *value){
    Std_ReturnType ret = E_not_ok;
    volatile uint8 l_tmr1_l =1 ,l_tmr1_h=1;
    if ((NULL == Timer1) || (NULL == value)){
        ret =E_not_ok;
    }
    else
    {
        l_tmr1_l= TMR1L;
        l_tmr1_h= TMR1H;
        *value = (uint16)((l_tmr1_h << 8) + (l_tmr1_l));
        ret =E_OK;
    }
    return ret;
}


static void timer1_mode_cfg (const Timer1_t *Timer1){
    if(Timer1->timer1_mode == TIMER1_source_external){
         TIMER1_SOURCE_EXTERNAL_CFG();
        if(Timer1->timer1_counter_mode == TIMER1_Asynchronize_clock_input){
            TIMER1_ASYNCH_clock_input_CFG();
        }
        else  if(Timer1->timer1_counter_mode == TIMER1_synchronize_clock_input){
            TIMER1_SYNCH_clock_input_CFG();
        }
         else{ /*nothing*/ }
    }
    else if(Timer1->timer1_mode == TIMER1_source_internal){
       TIMER1_SOURCE_INTERNAL_CFG();
    }
    else{ /*nothing*/ }
}

static void timer1_reg_bit_cfg (const Timer1_t *Timer1){
    if(Timer1->timer1_wr__reg_cfg == TIMER1_8bit_cfg){
        TIMER1_8BIT_CFG();
    }
    else if(Timer1->timer1_wr__reg_cfg == TIMER1_16bit_cfg){
        TIMER1_16BIT_CFG();
    }
    else {/*nothing*/}
}

static void timer1_osc_cfg (const Timer1_t *Timer1){
    if(Timer1->timer1_osc_cfg == TIMER1_oscillator_enable){
        TIMER1_OSCILLATOR_ENABLE();
    }
    else if(Timer1->timer1_osc_cfg == TIMER1_oscillator_disable){
        TIMER1_OSCILLATOR_DISABLE();
    }
    else {/*nothing*/}
}

void TIMER1_ISR (void){
    /* clear flag */
    TIMER1_INTERRUPT_FLAGE_CLEAR();
    /* any code */
    TMR1H = (Timer1_preload >> 8);
    TMR1L = (uint8)(Timer1_preload);
    /* callback function */
    if(TIMER1_Interrupthandler){
        TIMER1_Interrupthandler();
    }
}