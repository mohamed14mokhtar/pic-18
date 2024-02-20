/* 
 * File:   hal_timer2.c
 * Author: mokhtar
 *
 * Created on February 4, 2024, 5:05 PM
 */

#include"hal_timer2.h"

static void (* TIMER2_Interrupthandler)(void);
static uint8 Timer2_preload;

Std_ReturnType Timer2_init (const Timer2_t *Timer2){
    Std_ReturnType ret = E_not_ok;
    if (NULL == Timer2){
        ret =E_not_ok;
    }
    else
    {
        TIMER2_DISABLE();
        TIMER2_prescaler_div_by(Timer2->timer2_prescaler_cfg);
        TIMER2_postscaler_div_by(Timer2->timer2_postscaler_cfg);
        TMR2 = Timer2->timer1_preload_value;
        Timer2_preload = Timer2->timer1_preload_value;
#if TIMER2_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
        TIMER2_INTERRUPT_ENABLE();
        TIMER2_INTERRUPT_FLAGE_CLEAR();
        TIMER2_Interrupthandler = Timer2->Timer2_handler;
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
        
        INTERRUPT_prioritylevelenable();
        if(Timer2->INTERRUPT_PRIORITY == INTERRUPT_HUGH_PRIORITY){
            INTERRUPT_globalinterrupthighenable();
            TIMER2_INTERRUPT_high_priority_set();
        }
        else if(Timer2->INTERRUPT_PRIORITY == INTERRUPT_LOW_PRIORITY){
            INTERRUPT_globalinterruptlowenable();
            TIMER2_INTERRUPT_low_priority_set();
        }
        else{ /*nothing*/ }
#else 
        INTERRUPT_globalinterruptenable();
        INTERRUPT_peripheralinterruptenable();
       
#endif        
#endif   
        TIMER2_ENABLE();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer2_deinit (const Timer2_t *Timer2){
    Std_ReturnType ret = E_not_ok;
    if (NULL == Timer2){
        ret =E_not_ok;
    }
    else
    {
         TIMER2_DISABLE();
#if TIMER2_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
        TIMER2_INTERRUPT_disABLE();
#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer2_write_value (const Timer2_t *Timer2,uint8 value){
    Std_ReturnType ret = E_not_ok;
    if (NULL == Timer2){
        ret =E_not_ok;
    }
    else
    {
        TMR2 = value;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer2_read_value (const Timer2_t *Timer2,uint8 *value){
    Std_ReturnType ret = E_not_ok;
    if ((NULL == Timer2) || (NULL == value)){
        ret =E_not_ok;
    }
    else
    {
        *value = TMR2;
        ret = E_OK;
    }
    return ret;
}

void TIMER2_ISR (void){
    /* clear flag */
    TIMER2_INTERRUPT_FLAGE_CLEAR();
    /* any code */
    TMR2 = Timer2_preload;
    /* callback function */
    if(TIMER2_Interrupthandler){
        TIMER2_Interrupthandler();
    }
}