/* 
 * File:   hal_timer0.c
 * Author: mokhtar
 *
 * Created on February 3, 2024, 12:38 AM
 */

#include"hal_timer0.h"

static void (* TIMER0_Interrupthandler)(void);
static void timer0_prescaler_cfg(const Timer0_t *Timer0);
static void timer0_mode (const Timer0_t *Timer0);
static void timer0_register_size(const Timer0_t *Timer0);

void TIMER0_ISR (void);

static uint16 Timer0_preload;

Std_ReturnType Timer0_init (const Timer0_t *Timer0){
    Std_ReturnType ret = E_not_ok;
    if (NULL == Timer0){
        ret =E_not_ok;
    }
    else
    {
        /* disable timer */
        TIMER0_DISABLE();
        /* pre scaler cfg */
        timer0_prescaler_cfg(Timer0);
        /* timer mode */
        timer0_mode(Timer0);
        /* register size */
        timer0_register_size(Timer0);
        /* write value at the start */
        TMR0H = ((Timer0->timer_preload_value) >> 8);
        TMR0L = (uint8)(Timer0->timer_preload_value);  
        /* return value that start at */
        Timer0_preload = Timer0->timer_preload_value;
        /* interrupt if want */
#if TIMER0_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
        INTERRUPT_prioritylevelenable();
        if(Timer0->INTERRUPT_PRIORITY == INTERRUPT_HUGH_PRIORITY){
            INTERRUPT_globalinterrupthighenable();
            TIMER0_INTERRUPT_high_priority_set();
            INTERRUPT_globalinterruptlowenable();
        }
        else if(Timer0->INTERRUPT_PRIORITY == INTERRUPT_LOW_PRIORITY){
            INTERRUPT_globalinterruptlowenable();
            TIMER0_INTERRUPT_low_priority_set();
             INTERRUPT_globalinterrupthighenable();
        }
        else{ /*nothing*/ }
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_INTERRUPT_FLAGE_CLEAR();
        TIMER0_Interrupthandler = Timer0->Timer0_handler;
#else 
        INTERRUPT_globalinterruptenable();
        INTERRUPT_peripheralinterruptenable();
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_INTERRUPT_FLAGE_CLEAR();
        TIMER0_Interrupthandler = Timer0->Timer0_handler;
#endif        
#endif   
        /* enable timer */
        TIMER0_ENABLE();
        
        ret =E_OK;
    }
    return ret;
}

Std_ReturnType Timer0_deinit (const Timer0_t *Timer0){
    Std_ReturnType ret = E_not_ok;
    if (NULL == Timer0){
        ret =E_not_ok;
    }
    else
    {
        TIMER0_DISABLE();
#if TIMER0_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
        TIMER0_INTERRUPT_disABLE();
#endif
        ret =E_OK;
    }
    return ret;
}

Std_ReturnType Timer0_write_value (const Timer0_t *Timer0,uint16 value){
    Std_ReturnType ret = E_not_ok;
    if (NULL == Timer0){
        ret =E_not_ok;
    }
    else
    {
        TMR0H = (value >> 8);
        TMR0L = (uint8)(value);  
        ret =E_OK;
    }
    return ret;
}

Std_ReturnType Timer0_read_value (const Timer0_t *Timer0,uint16 *value){
        Std_ReturnType ret = E_not_ok;
        uint8 l_tmr0_l =0 ,l_tmr0_h=0;
    if ((NULL == Timer0) || (NULL == value)){
        ret =E_not_ok;
    }
    else
    {
        l_tmr0_l= TMR0L;
        l_tmr0_h= TMR0H;
        *value = (uint16)((l_tmr0_h << 8) + (l_tmr0_l));
        ret =E_OK;
    }
    return ret;
}

static void timer0_prescaler_cfg(const Timer0_t *Timer0){
    if(Timer0->prescaler_enable == TIMER0_prescalering_enable){
        TIMER0_PRESCALERING_ENABLE();
        T0CONbits.T0PS = Timer0->Prescaler_Select;
    }
    else if(Timer0->prescaler_enable == TIMER0_prescalering_disable){
        TIMER0_PRESCALERING_DISABLE();
    }
    else{}
}

static void timer0_mode (const Timer0_t *Timer0){
    if(Timer0->timer0_mode == TIMER0_source_external){
        TIMER0_SOURCE_EXTERNAL();
        if(Timer0->timer0_counter_edge == TIMER0_falling_edge){
            TIMER0_FALLING_EDGE();
        }
        else if(Timer0->timer0_counter_edge == TIMER0_rising_edge){
            TIMER0_RISING_EDGE();
        }
        else{}
    }
    else if(Timer0->timer0_mode == TIMER0_source_internal){
        TIMER0_SOURCE_INTERNAL();
    }
    else{}
}

static void timer0_register_size(const Timer0_t *Timer0){
    if(Timer0->timer0_register_size == TIMER0_8bit_cfg){
        TIMER0_8BIT_CFG();
    }
    else if(Timer0->timer0_register_size == TIMER0_16bit_cfg){
        TIMER0_16BIT_CFG();
    }
    else{}
}

void TIMER0_ISR (void){
    /* clear flag */
    TIMER0_INTERRUPT_FLAGE_CLEAR();
    /* any code */
    TMR0H = (Timer0_preload >> 8);
    TMR0L = (uint8)(Timer0_preload);
    /* callback function */
    if(TIMER0_Interrupthandler){
        TIMER0_Interrupthandler();
    }
}