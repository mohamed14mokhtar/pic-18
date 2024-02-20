/* 
 * File:   hal_adc.c
 * Author: mokhtar
 *
 * Created on January 30, 2024, 4:50 PM
 */

#include"hal_adc.h"
static void (* ADC_INTERRUPTHANDLER) (void);
void ADC_handeler_funvtion (void);
static inline void adc_channel_port_confige(const ADC_CHANNAL_SELECT_t ADC_CHANNAL_SELECT);
static inline void select_result_format(const ADC_conf_t *ADC_conf);
static inline void configure_voltage_ref(const ADC_conf_t *ADC_conf);

Std_ReturnType ADC_inti(const ADC_conf_t *ADC_conf){
    Std_ReturnType ret =E_not_ok;
    if (NULL == ADC_conf){
        ret =E_not_ok;
    }
    else{
        /* disable ADC */
        ADC_CONVERTER_DISABLE();
        /* configure the Acquisition time */
        ADCON2bits.ACQT = ADC_conf->Acquisition_time;
        /* configure the Conversion Clock */
        ADCON2bits.ADCS = ADC_conf->Conversion_Clock;
        /* configure the default channel  */
        ADCON0bits.CHS = ADC_conf->ADC_CHANNAL_SELECT;
        adc_channel_port_confige(ADC_conf->ADC_CHANNAL_SELECT);
        /* configure the interrupt */
#if     ADC_INTERRUPT_feature_ENABLE    == INTERRUPT_FATURE_ENABLE
#if     INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
         /* enable interrupt at all */
        INTERRUPT_prioritylevelenable();
        if(ADC_conf->INTERRUPT_PRIORITY == INTERRUPT_HUGH_PRIORITY){
            INTERRUPT_globalinterrupthighenable();
            ADC_INTERRUPT_high_priority_set();}
        else if(ADC_conf->INTERRUPT_PRIORITY == INTERRUPT_LOW_PRIORITY){
            INTERRUPT_globalinterruptlowenable();
            ADC_INTERRUPT_low_priority_set();}
        else{ /* nothing */ }
        /* enable interrupt at ADC */
        ADC_INTERRUPT_ENABLE();
        /* clear flag at ADC */
        ADC_INTERRUPT_FLAGE_CLEAR();
        /* callback function */
        ADC_INTERRUPTHANDLER = ADC_conf->ADC_interruptHandler;  
#else
        /* enable interrupt at all */
        INTERRUPT_globalinterruptenable();
        INTERRUPT_peripheralinterruptenable();
        /* enable interrupt at ADC */
        ADC_INTERRUPT_ENABLE();
        /* clear flag at ADC */
        ADC_INTERRUPT_FLAGE_CLEAR();
        /* callback function */
        ADC_INTERRUPTHANDLER = ADC_conf->ADC_interruptHandler;  
#endif       
#endif
        /* configure the result format */
        select_result_format(ADC_conf);
        /* configure the voltage reference  */
        configure_voltage_ref(ADC_conf);
        /* enable ADC */
        ADC_CONVERTER_ENABLE();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_deinti(const ADC_conf_t *ADC_conf){
    Std_ReturnType ret =E_not_ok;
    if (NULL == ADC_conf){
        ret =E_not_ok;
    }
    else{
        /* enable ADC */
        ADC_CONVERTER_DISABLE();
        /* disable interrupt */
        ADC_INTERRUPT_disABLE();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_select_channal(const ADC_conf_t *ADC_conf,const ADC_CHANNAL_SELECT_t ADC_CHANNAL_SELECT){
    Std_ReturnType ret =E_not_ok;
    if (NULL == ADC_conf){
        ret =E_not_ok;
    }
    else{
        ADCON0bits.CHS = ADC_CHANNAL_SELECT;
        adc_channel_port_confige(ADC_CHANNAL_SELECT);
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_start_conversion(const ADC_conf_t *ADC_conf){
    Std_ReturnType ret =E_not_ok;
    if (NULL == ADC_conf){
        ret =E_not_ok;
    }
    else{
        ADC_START_CONVERTION();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_ISconversion_done(const ADC_conf_t *ADC_conf , uint8 *conversion_status){
     Std_ReturnType ret =E_not_ok;
    if ((NULL == ADC_conf) || (NULL == conversion_status)){
        ret =E_not_ok;
    }
    else{
        *conversion_status = (uint8)(!(ADCON0bits.GO_nDONE));
        ret = E_OK;
    }
     return ret;
}

Std_ReturnType ADC_ISconversion_result(const ADC_conf_t *ADC_conf , adc_result_t *conversion_result){
     Std_ReturnType ret =E_not_ok;
    if ((NULL == ADC_conf) || (NULL == conversion_result)){
        ret =E_not_ok;
    }
    else{
        if(ADC_conf->result_format == ADC_result_right){
            *conversion_result = ((ADRESH << 8) + ADRESL);
        }else if(ADC_conf->result_format == ADC_result_left){
            *conversion_result = (((ADRESH << 8) + ADRESL) >> 6) ;
        }
        else
        {
            *conversion_result = ((ADRESH << 8) + ADRESL);
        }
        ret = E_OK;
    }
     return ret;
}

Std_ReturnType ADC_get_conversion_blocking(const ADC_conf_t *ADC_conf , ADC_CHANNAL_SELECT_t ADC_CHANNAL_SELECT 
                                  ,adc_result_t *conversion_status){
     Std_ReturnType ret =E_not_ok;
     uint8 l_conversion_status = 0;
    if ((NULL == ADC_conf) || (NULL == conversion_status)){
        ret =E_not_ok;
    }
    else{
        /* select ADC channel */
        ret = ADC_select_channal(ADC_conf,ADC_CHANNAL_SELECT);
        /* start conversion */
        ret = ADC_start_conversion(ADC_conf);
        /* check if conversion complete */
        ret = ADC_ISconversion_done(ADC_conf,&l_conversion_status);
        while(ADCON0bits.GO_nDONE);
        ret = ADC_ISconversion_result(ADC_conf,conversion_status);
        ret = E_OK;
    }
}

Std_ReturnType ADC_start_conversion_interrupt(const ADC_conf_t *ADC_conf , ADC_CHANNAL_SELECT_t ADC_CHANNAL_SELECT ){
     Std_ReturnType ret =E_not_ok;
    if (NULL == ADC_conf){
        ret =E_not_ok;
    }
    else{
        /* select ADC channel */
        ret = ADC_select_channal(ADC_conf,ADC_CHANNAL_SELECT);
        /* start conversion */
        ret = ADC_start_conversion(ADC_conf);
    }
}

static inline void adc_channel_port_confige(const ADC_CHANNAL_SELECT_t ADC_CHANNAL_SELECT)
{
    switch (ADC_CHANNAL_SELECT){
        case ADC_CHANNEL_AN0  : SIT_BIT(TRISA ,_TRISA_RA0_POSN);break;
        case ADC_CHANNEL_AN1  : SIT_BIT(TRISA ,_TRISA_RA1_POSN);break;
        case ADC_CHANNEL_AN2  : SIT_BIT(TRISA ,_TRISA_RA2_POSN);break;
        case ADC_CHANNEL_AN3  : SIT_BIT(TRISA ,_TRISA_RA3_POSN);break;
        case ADC_CHANNEL_AN4  : SIT_BIT(TRISA ,_TRISA_RA4_POSN);break;
        case ADC_CHANNEL_AN5  : SIT_BIT(TRISE ,_TRISE_RE0_POSN);break;
        case ADC_CHANNEL_AN6  : SIT_BIT(TRISE ,_TRISE_RE1_POSN);break;
        case ADC_CHANNEL_AN7  : SIT_BIT(TRISE ,_TRISE_RE2_POSN);break;
        case ADC_CHANNEL_AN8  : SIT_BIT(TRISB ,_TRISB_RB2_POSN);break;
        case ADC_CHANNEL_AN9  : SIT_BIT(TRISB ,_TRISB_RB3_POSN);break;
        case ADC_CHANNEL_AN10 : SIT_BIT(TRISB ,_TRISB_RB1_POSN);break;
        case ADC_CHANNEL_AN11 : SIT_BIT(TRISB ,_TRISB_RB4_POSN);break;
        case ADC_CHANNEL_AN12 : SIT_BIT(TRISB ,_TRISB_RB0_POSN);break;
    }
}

static inline void select_result_format(const ADC_conf_t *ADC_conf){
    if(ADC_conf->result_format == ADC_result_right){
        ADC_CONVERTER_RIGHT_justified();
    }else if(ADC_conf->result_format == ADC_result_left){
        ADC_CONVERTER_LEFT_justified() ;
    }
    else
    {
        ADC_CONVERTER_RIGHT_justified();
    }
}

static inline void configure_voltage_ref(const ADC_conf_t *ADC_conf){
      if(ADC_conf->result_format == voltage_ref_enable){
        ADC_DISABLE_VOLTAGE_FERERENCE_1();
        ADC_DISABLE_VOLTAGE_FERERENCE_2();
    }else if(ADC_conf->result_format == voltage_ref_disable){
        ADC_ENABLE_VOLTAGE_FERERENCE_1() ;
        ADC_ENABLE_VOLTAGE_FERERENCE_2() ;
    }
    else
    {
        ADC_DISABLE_VOLTAGE_FERERENCE_1();
        ADC_DISABLE_VOLTAGE_FERERENCE_2();
    }
}

void ADC_handeler_funvtion (void){
    /* clear flag */
    ADC_INTERRUPT_FLAGE_CLEAR();
    /* any code i want */
    
    /* callback function */
    if(ADC_INTERRUPTHANDLER){ADC_INTERRUPTHANDLER();}
    else{/* nothing */}
}