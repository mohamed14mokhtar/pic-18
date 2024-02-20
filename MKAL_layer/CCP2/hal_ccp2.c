/* 
 * File:   hal_ccp2.c
 * Author: mokhtar
 *
 * Created on February 9, 2024, 9:42 AM
 */

#include"hal_ccp2.h"
static void (* CCP2_Interrupthandler)(void);
void ccp2_select_timer (const ccp2_t *ccp2_);

Std_ReturnType ccp2_init   (const ccp2_t *ccp2_){
    Std_ReturnType ret = E_not_ok;
    if (NULL == ccp2_){
        ret =E_not_ok;
    }
    else
    {
        CCP2_select_statues(ccp2_module_disabled);
        if(ccp2_->ccp2_mode == ccp2_capture_mode_select)
        {
            #if ccp2_cfg_mode_select == ccp2_cfg_capture_mode_select
            switch(ccp2_->ccp2_mode_variant){
                case ccp2_Capture_mode_every_falling_edge    : CCP2_select_statues(ccp2_Capture_mode_every_falling_edge);
                break;
                case ccp2_Capture_mode_every_rising_edge     : CCP2_select_statues(ccp2_Capture_mode_every_rising_edge);
                break;
                case ccp2_Capture_mode_every_4th_rising_edge : CCP2_select_statues(ccp2_Capture_mode_every_4th_rising_edge);
                break;
                case ccp2_Capture_mode_every_16th_rising_edge: CCP2_select_statues(ccp2_Capture_mode_every_16th_rising_edge);
                break;
                default : ret = E_not_ok; break;
            }
            ccp2_select_timer(ccp2_);
            #endif 
        }
        else if(ccp2_->ccp2_mode == ccp2_compare_mode_select)
        {
            #if ccp2_cfg_mode_select == ccp2_cfg_compare_mode_select
            switch(ccp2_->ccp2_mode_variant){
                case ccp2_Compare_mode_toggle_output_on_match : CCP2_select_statues(ccp2_Compare_mode_toggle_output_on_match);
                break;
                case ccp2_Compare_mode_initialize_pin_low : CCP2_select_statues(ccp2_Compare_mode_initialize_pin_low);
                break;
                case ccp2_Compare_mode_initialize_pin_high : CCP2_select_statues(ccp2_Compare_mode_initialize_pin_high);
                break;
                case ccp2_Compare_mode_initialize_interrupt : CCP2_select_statues(ccp2_Compare_mode_initialize_interrupt);
                break;
                case ccp2_Compare_mode_initialize_even : CCP2_select_statues(ccp2_Compare_mode_initialize_even);
                break;
                default : ret = E_not_ok; break;
            }
            ccp2_select_timer(ccp2_);
            #endif
        }
        else if(ccp2_->ccp2_mode == ccp2_pwm_mode_select)
        {
            if(ccp2_->ccp2_mode_variant == ccp2_pwm_initialize){
                CCP2_select_statues(ccp2_pwm_initialize);
            }
            else{ /*nothing*/ }
            #if ccp2_cfg_mode_select == ccp2_cfg_pwm_mode_select
                PR2 = (uint8)((_XTAL_FREQ/(4 *ccp2_->ccp2_timer2_postscaler_cfg *ccp2_->ccp2_timer2_prescaler_cfg * ccp2_->ccp2_pwm_frequence))-1);
            #endif
        }
        else{ /*nothing*/ }
        /*pin initialize */
        ret = GPIO_pIN_INTIALIZE(&(ccp2_->pin_config));
        
        
        
        /* interrupt */
#if CCP2_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
        CCP2_INTERRUPT_ENABLE();
        CCP2_INTERRUPT_FLAGE_CLEAR();
        CCP2_Interrupthandler = ccp2_->CCP2_handler;
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
        
        INTERRUPT_prioritylevelenable();
        if(ccp2_->INTERRUPT_PRIORITY == INTERRUPT_HUGH_PRIORITY){
            INTERRUPT_globalinterrupthighenable();
            CCP2_INTERRUPT_high_priority_set();
        }
        else if(ccp2_->INTERRUPT_PRIORITY == INTERRUPT_LOW_PRIORITY){
            INTERRUPT_globalinterruptlowenable();
            CCP2_INTERRUPT_low_priority_set();
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

Std_ReturnType ccp2_deinit   (const ccp2_t *ccp2_){
    Std_ReturnType ret = E_not_ok;
    if (NULL == ccp2_){
        ret =E_not_ok;
    }
    else
    {
        CCP2_select_statues(ccp2_module_disabled);
#if CCP1_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
        CCP1_INTERRUPT_disABLE();
#endif
        ret =E_OK;
    }
    return ret;
}


#if ccp2_cfg_mode_select == ccp2_cfg_pwm_mode_select
Std_ReturnType ccp2_pwm_set_duty (const uint8 duty){
    Std_ReturnType ret = E_not_ok;
    uint8 duty_ =100 - duty;
    uint16 l_duty_temp =0;
    l_duty_temp = (uint16)((float)4 * ((float)PR2 + 1.0) * (float)((float)duty_ / 100.0));
    CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003);
    CCPR2L = (uint8)(l_duty_temp >> 2);
    ret =E_OK;
    return ret;
}

Std_ReturnType ccp2_pwm_start    (void){
    Std_ReturnType ret = E_not_ok;
    
    CCP2_select_statues(ccp2_pwm_initialize);
    ret =E_OK;
    return ret;
}

Std_ReturnType ccp2_pwm_set_stop (void){
    Std_ReturnType ret = E_not_ok;
    
    CCP2_select_statues(ccp2_module_disabled);
    ret =E_OK;
    return ret;
}

#endif

#if ccp2_cfg_mode_select == ccp2_cfg_compare_mode_select
Std_ReturnType ccp2_compare_data_ready (uint8 *compare_statues){
    Std_ReturnType ret = E_not_ok;
    if (NULL == compare_statues){
        ret =E_not_ok;
    }
    else
    {
        if(ccp2_compare_mode_ready == PIR2bits.CCP2IF){
            *compare_statues = ccp2_compare_mode_ready;
        }
        else{
            *compare_statues = ccp2_compare_mode_not_ready;
        }
        ret =E_OK;
    }
    return ret;
}

Std_ReturnType ccp2_compare_write_data (uint16 compare_value){
    Std_ReturnType ret = E_not_ok;
    ccp2_register_t ccp2_register ={.ccp2_16bit=0,.ccpr2_l=0,.ccpr2_h=0};
    
    ccp2_register.ccp2_16bit = compare_value;
    
    CCPR2L =ccp2_register.ccpr2_l;
    CCPR2H =ccp2_register.ccpr2_h;
    ret =E_OK;
    return ret;
}

#endif

#if ccp2_cfg_mode_select == ccp2_cfg_capture_mode_select
Std_ReturnType ccp2_capture_data_ready (uint8 *capture_statues){
    Std_ReturnType ret = E_not_ok;
    if (NULL == capture_statues){
        ret =E_not_ok;
    }
    else
    {
        if(ccp2_capture_mode_ready == PIR2bits.CCP2IF){
            *capture_statues = ccp2_capture_mode_ready;
        }
        else{
            *capture_statues = ccp2_capture_mode_not_ready;
        }
        ret =E_OK;
    }
    return ret;
}

Std_ReturnType ccp2_capture_read_data  (uint16 *capture_value){
    Std_ReturnType ret = E_not_ok;
    ccp2_register_t ccp2_register ={.ccpr2_l=0,.ccpr2_h=0};
    if (NULL == capture_value){
        ret =E_not_ok;
    }
    else
    {
       ccp2_register.ccpr2_l = CCPR2L;
       ccp2_register.ccpr2_h =CCPR2H;
       *capture_value = ccp2_register.ccp2_16bit;
       ret =E_OK; 
    }
    
    return ret;
}

#endif

void CCP2_ISR (void){
    CCP2_INTERRUPT_FLAGE_CLEAR();
    if(CCP2_Interrupthandler){
        CCP2_Interrupthandler();
    }
    else{ /*nothing*/ }
}
#if ((ccp2_cfg_mode_select == ccp2_cfg_capture_mode_select) || (ccp2_cfg_mode_select == ccp2_cfg_compare_mode_select))
void ccp2_select_timer (const ccp2_t *ccp2_){
    if(ccp2_->select_timer_use == _ccp1_ccp2_use_timer1){
        T3CONbits.T3CCP1 = 0 ;
        T3CONbits.T3CCP2 = 0 ;
    }
    else if(ccp2_->select_timer_use == _ccp1_use_timer1_ccp2_use_timer3){
        T3CONbits.T3CCP1 = 1 ;
        T3CONbits.T3CCP2 = 0 ;
    }
    else if(ccp2_->select_timer_use == _ccp1_ccp2_use_timer3){
        T3CONbits.T3CCP1 = 1 ;
        T3CONbits.T3CCP2 = 1 ;
    }
    else{}
}
#endif
