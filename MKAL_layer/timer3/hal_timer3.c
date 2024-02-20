/* 
 * File:   hal_timer3.c
 * Author: mokhtar
 *
 * Created on February 4, 2024, 5:06 PM
 */

#include"hal_timer3.h"
static void timer3_mode_cfg(const Timer3_t *Timer3);
static void timer3_reg_bit_cfg (const Timer3_t *Timer3);
static void (* TIMER3_Interrupthandler)(void);
static uint16 Timer3_preload;

Std_ReturnType Timer3_init   (const Timer3_t *Timer3){
     Std_ReturnType ret = E_not_ok;
    if (NULL == Timer3){
        ret =E_not_ok;
    }
    else
    {
        TIMER3_DISABLE();
        TIMER3_prescaler_div_by(Timer3->timer3_prescaler_cfg);
        timer3_mode_cfg(Timer3);
        timer3_reg_bit_cfg(Timer3);
        TMR3H = ((Timer3->timer3_preload_value) >> 8);
        TMR3L = (uint8)(Timer3->timer3_preload_value);
        Timer3_preload = Timer3->timer3_preload_value;
#if TIMER3_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
        TIMER3_INTERRUPT_ENABLE();
        TIMER3_INTERRUPT_FLAGE_CLEAR();
        TIMER3_Interrupthandler = Timer3->Timer3_handler;
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
        
        INTERRUPT_prioritylevelenable();
        if(Timer3->INTERRUPT_PRIORITY == INTERRUPT_HUGH_PRIORITY){
            INTERRUPT_globalinterrupthighenable();
            TIMER3_INTERRUPT_high_priority_set();
        }
        else if(Timer3->INTERRUPT_PRIORITY == INTERRUPT_LOW_PRIORITY){
            INTERRUPT_globalinterruptlowenable();
            TIMER3_INTERRUPT_low_priority_set();
        }
        else{ /*nothing*/ }
#else 
        INTERRUPT_globalinterruptenable();
        INTERRUPT_peripheralinterruptenable();
       
#endif        
#endif   
        TIMER3_ENABLE();
        ret =E_OK;
    }
    return ret;
}

Std_ReturnType Timer3_deinit (const Timer3_t *Timer3){
    Std_ReturnType ret = E_not_ok;
    if (NULL == Timer3){
        ret =E_not_ok;
    }
    else
    {
            TIMER3_DISABLE();
#if TIMER3_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
        TIMER3_INTERRUPT_disABLE();
#endif
        ret =E_OK;
    }
    return ret;
}

Std_ReturnType Timer3_write_value (const Timer3_t *Timer3,uint16 value){
     Std_ReturnType ret = E_not_ok;
    if (NULL == Timer3){
        ret =E_not_ok;
    }
    else
    {
        TMR3H = (value >> 8);
        TMR3L = (uint8)(value);  
        ret =E_OK;
    }
    return ret;
}

Std_ReturnType Timer3_read_value (const Timer3_t *Timer3,uint16 *value){
     Std_ReturnType ret = E_not_ok;
    uint8 l_tmr3_l =1 ,l_tmr3_h=1;
    if ((NULL == Timer3) || (NULL == value)){
        ret =E_not_ok;
    }
    else
    {
        l_tmr3_l= TMR3L;
        l_tmr3_h= TMR3H;
        *value = (uint16)((l_tmr3_h << 8) + (l_tmr3_l));
        ret =E_OK;
    }
    return ret;
}

static void timer3_mode_cfg(const Timer3_t *Timer3){
    if(Timer3->timer3_mode == TIMER3_source_internal){
        TIMER3_SOURCE_INTERNAL_CFG();
    }
    else if(Timer3->timer3_mode == TIMER3_source_external){
        TIMER3_SOURCE_EXTERNAL_CFG();
        if(Timer3->timer3_counter_mode == TIMER3_Asynchronize_clock_input){
            TIMER1_ASYNCH_clock_input_CFG();
        }
        else if(Timer3->timer3_counter_mode == TIMER3_synchronize_clock_input){
            TIMER1_SYNCH_clock_input_CFG();
        } 
        else{ /*nothing*/ }
    }
    else{ /*nothing*/ }
}

static void timer3_reg_bit_cfg (const Timer3_t *Timer3){
    if(Timer3->timer3_wr__reg_cfg == TIMER3_8bit_cfg){
        TIMER3_8BIT_CFG();
    }
    else if(Timer3->timer3_wr__reg_cfg == TIMER3_16bit_cfg){
        TIMER3_16BIT_CFG();
    }
    else {/*nothing*/}
}

void TIMER3_ISR (void){
    /* clear flag */
    TIMER3_INTERRUPT_FLAGE_CLEAR();
    /* any code */
    TMR3H = (Timer3_preload >> 8);
    TMR3L = (uint8)(Timer3_preload);
    /* callback function */
    if(TIMER3_Interrupthandler){
        TIMER3_Interrupthandler();
    }
}