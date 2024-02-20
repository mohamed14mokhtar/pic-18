/* 
 * File:   hal_ccp1.c
 * Author: mokhtar
 *
 * Created on February 7, 2024, 9:26 AM
 */

#include"hal_ccp1.h"
static void (* CCP1_Interrupthandler)(void);
void select_timer (const ccp1_t *ccp1_);

Std_ReturnType ccp1_init   (const ccp1_t *ccp1_){
    Std_ReturnType ret = E_not_ok;
    if (NULL == ccp1_){
        ret =E_not_ok;
    }
    else
    {
        CCP1_select_statues(ccp1_module_disabled);
        if(ccp1_->ccp1_mode == ccp1_capture_mode_select)
        {
            #if ccp1_cfg_mode_select == ccp1_cfg_capture_mode_select
            switch(ccp1_->ccp1_mode_variant){
                case ccp1_Capture_mode_every_falling_edge    : CCP1_select_statues(ccp1_Capture_mode_every_falling_edge);
                break;
                case ccp1_Capture_mode_every_rising_edge     : CCP1_select_statues(ccp1_Capture_mode_every_rising_edge);
                break;
                case ccp1_Capture_mode_every_4th_rising_edge : CCP1_select_statues(ccp1_Capture_mode_every_4th_rising_edge);
                break;
                case ccp1_Capture_mode_every_16th_rising_edge : CCP1_select_statues(ccp1_Capture_mode_every_16th_rising_edge);
                break;
                default : ret = E_not_ok; break;
            }
            select_timer(ccp1_);
            #endif 
        }
        else if(ccp1_->ccp1_mode == ccp1_compare_mode_select)
        {
            #if ccp1_cfg_mode_select == ccp1_cfg_compare_mode_select
            switch(ccp1_->ccp1_mode_variant){
                case ccp1_Compare_mode_toggle_output_on_match : CCP1_select_statues(ccp1_Compare_mode_toggle_output_on_match);
                break;
                case ccp1_Compare_mode_initialize_pin_low : CCP1_select_statues(ccp1_Compare_mode_initialize_pin_low);
                break;
                case ccp1_Compare_mode_initialize_pin_high : CCP1_select_statues(ccp1_Compare_mode_initialize_pin_high);
                break;
                case ccp1_Compare_mode_initialize_interrupt : CCP1_select_statues(ccp1_Compare_mode_initialize_interrupt);
                break;
                case ccp1_Compare_mode_initialize_even : CCP1_select_statues(ccp1_Compare_mode_initialize_even);
                break;
                default : ret = E_not_ok; break;
            }
            select_timer(ccp1_);
            #endif
        }
        else if(ccp1_->ccp1_mode == ccp1_cfg_pwm_mode_select)
        {
            if(ccp1_->ccp1_mode_variant == ccp1_pwm_initialize){
                CCP1_select_statues(ccp1_pwm_initialize);
            }
            else{ /*nothing*/ }
            #if ccp1_cfg_mode_select == ccp1_cfg_pwm_mode_select
                PR2 = (uint8)((_XTAL_FREQ/(4*ccp1_->timer2_postscaler_cfg *ccp1_->timer2_prescaler_cfg * ccp1_->pwm_frequence))-1);
            #endif
        }
        else{ /*nothing*/ }
        /*pin initialize */
        ret = GPIO_pIN_INTIALIZE(&(ccp1_->pin_config));
        
        
        
        /* interrupt */
#if CCP1_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
        CCP1_INTERRUPT_ENABLE();
        CCP1_INTERRUPT_FLAGE_CLEAR();
        CCP1_Interrupthandler = ccp1_->CCP1_handler;
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
        
        INTERRUPT_prioritylevelenable();
        if(ccp1_->INTERRUPT_PRIORITY == INTERRUPT_HUGH_PRIORITY){
            INTERRUPT_globalinterrupthighenable();
            CCP1_INTERRUPT_high_priority_set();
        }
        else if(ccp1_->INTERRUPT_PRIORITY == INTERRUPT_LOW_PRIORITY){
            INTERRUPT_globalinterruptlowenable();
            CCP1_INTERRUPT_low_priority_set();
        }
        else{ /*nothing*/ }
#else 
        INTERRUPT_globalinterruptenable();
        INTERRUPT_peripheralinterruptenable();
       
#endif        
#endif   
        ret =E_OK;
    }
    return ret;
}

Std_ReturnType ccp1_deinit   (const ccp1_t *ccp1_){
    Std_ReturnType ret = E_not_ok;
    if (NULL == ccp1_){
        ret =E_not_ok;
    }
    else
    {
        CCP1_select_statues(ccp1_module_disabled);
#if CCP1_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
        CCP1_INTERRUPT_disABLE();
#endif
        ret =E_OK;
    }
    return ret;
}


#if ccp1_cfg_mode_select == ccp1_cfg_pwm_mode_select
Std_ReturnType ccp1_pwm_set_duty (const uint8 duty){
    Std_ReturnType ret = E_not_ok;
    uint8 duty_ =100 - duty;
    uint16 l_duty_temp =0;
    l_duty_temp = (uint16)((float)4 * ((float)PR2 + 1.0) * (float)((float)duty_ / 100.0));
    CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003);
    CCPR1L = (uint8)(l_duty_temp >> 2);
    ret =E_OK;
    return ret;
}

Std_ReturnType ccp1_pwm_start    (void){
    Std_ReturnType ret = E_not_ok;
    
    CCP1_select_statues(ccp1_pwm_initialize);
    ret =E_OK;
    return ret;
}

Std_ReturnType ccp1_pwm_set_stop (void){
    Std_ReturnType ret = E_not_ok;
    
    CCP1_select_statues(ccp1_module_disabled);
    ret =E_OK;
    return ret;
}

#endif

#if ccp1_cfg_mode_select == ccp1_cfg_compare_mode_select
Std_ReturnType ccp1_compare_data_ready (uint8 *compare_statues){
    Std_ReturnType ret = E_not_ok;
    if (NULL == compare_statues){
        ret =E_not_ok;
    }
    else
    {
        if(ccp1_compare_mode_ready == PIR1bits.CCP1IF){
            *compare_statues = ccp1_compare_mode_ready;
        }
        else{
            *compare_statues = ccp1_compare_mode_not_ready;
        }
        ret =E_OK;
    }
    return ret;
}

Std_ReturnType ccp1_compare_write_data (uint16 compare_value){
    Std_ReturnType ret = E_not_ok;
    ccp1_register_t ccp1_register ={.ccp1_16bit=0,.ccpr1_l=0,.ccpr1_h=0};
    
    ccp1_register.ccp1_16bit = compare_value;
    
    CCPR1L =ccp1_register.ccpr1_l;
    CCPR1H =ccp1_register.ccpr1_h;
    ret =E_OK;
    return ret;
}

#endif

#if ccp1_cfg_mode_select == ccp1_cfg_capture_mode_select
Std_ReturnType ccp1_capture_data_ready (uint8 *capture_statues){
    Std_ReturnType ret = E_not_ok;
    if (NULL == capture_statues){
        ret =E_not_ok;
    }
    else
    {
        if(ccp1_capture_mode_ready == PIR1bits.CCP1IF){
            *capture_statues = ccp1_capture_mode_ready;
        }
        else{
            *capture_statues = ccp1_capture_mode_not_ready;
        }
        ret =E_OK;
    }
    return ret;
}

Std_ReturnType ccp1_capture_read_data  (uint16 *capture_value){
    Std_ReturnType ret = E_not_ok;
    ccp1_register_t ccp1_register ={.ccpr1_l=0,.ccpr1_h=0};
    if (NULL == capture_value){
        ret =E_not_ok;
    }
    else
    {
       ccp1_register.ccpr1_l = CCPR1L;
       ccp1_register.ccpr1_h =CCPR1H;
       *capture_value = ccp1_register.ccp1_16bit;
       ret =E_OK; 
    }
    
    return ret;
}

#endif

void CCP1_ISR (void){
    CCP1_INTERRUPT_FLAGE_CLEAR();
    if(CCP1_Interrupthandler){
        CCP1_Interrupthandler();
    }
    else{ /*nothing*/ }
}
#if ((ccp1_cfg_mode_select == ccp1_cfg_capture_mode_select) || (ccp1_cfg_mode_select == ccp1_cfg_compare_mode_select))
void select_timer (const ccp1_t *ccp1_){
    if(ccp1_->select_timer_use == ccp1_ccp2_use_timer1){
        T3CONbits.T3CCP1 = 0 ;
        T3CONbits.T3CCP2 = 0 ;
    }
    else if(ccp1_->select_timer_use == ccp1_use_timer1_ccp2_use_timer3){
        T3CONbits.T3CCP1 = 1 ;
        T3CONbits.T3CCP2 = 0 ;
    }
    else if(ccp1_->select_timer_use == ccp1_ccp2_use_timer3){
        T3CONbits.T3CCP1 = 1 ;
        T3CONbits.T3CCP2 = 1 ;
    }
    else{}
}
#endif