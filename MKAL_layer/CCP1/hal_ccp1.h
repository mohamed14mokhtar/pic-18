/* 
 * File:   hal_ccp1.h
 * Author: mokhtar
 *
 * Created on February 7, 2024, 9:26 AM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/*section : includes */
#include"hal_ccp1_cfg.h"
#include"../mkal_std_types.h"
#include"../pic18_chip_select.h"
#include"../Interrupt/mcal_internal_interrupt.h"
#include"../gpio/pro_gpio.h"
/*section : macro declarations  */
/* mode variant */
#define ccp1_module_disabled                             0
#define ccp1_Capture_mode_every_falling_edge             4
#define ccp1_Capture_mode_every_rising_edge              5
#define ccp1_Capture_mode_every_4th_rising_edge          6
#define ccp1_Capture_mode_every_16th_rising_edge         7
#define ccp1_Compare_mode_toggle_output_on_match         2
#define ccp1_Compare_mode_initialize_pin_low             8
#define ccp1_Compare_mode_initialize_pin_high            9
#define ccp1_Compare_mode_initialize_interrupt           10
#define ccp1_Compare_mode_initialize_even                11
#define ccp1_pwm_initialize                              0x0E

#define ccp1_capture_mode_ready     1
#define ccp1_capture_mode_not_ready 0

#define ccp1_compare_mode_ready     1
#define ccp1_compare_mode_not_ready 0


#define ccp1_Postscale_div_by_1     1
#define ccp1_Postscale_div_by_2     2
#define ccp1_Postscale_div_by_3     3
#define ccp1_Postscale_div_by_4     4
#define ccp1_Postscale_div_by_5     5
#define ccp1_Postscale_div_by_6     6
#define ccp1_Postscale_div_by_7     7
#define ccp1_Postscale_div_by_8     8
#define ccp1_Postscale_div_by_9     9
#define ccp1_Postscale_div_by_10    10
#define ccp1_Postscale_div_by_11    11
#define ccp1_Postscale_div_by_12    12
#define ccp1_Postscale_div_by_13    13
#define ccp1_Postscale_div_by_14    14
#define ccp1_Postscale_div_by_15    15
#define ccp1_Postscale_div_by_16    16



#define ccp1_prescale_div_by_1     1
#define ccp1_prescale_div_by_4     4
#define ccp1_prescale_div_by_16    16

/*section : macro declaration functions  */
#define CCP1_select_statues(_value) (CCP1CONbits.CCP1M =_value)
/*section : data type declarations  */
typedef union{
    struct{
        uint8 ccpr1_l;
        uint8 ccpr1_h;
    };
    struct{
        uint16 ccp1_16bit;
    };
}ccp1_register_t;

typedef enum{
   ccp1_capture_mode_select,
   ccp1_compare_mode_select,
   ccp1_pwm_mode_select       
}ccp1_mode_t;

typedef enum {
    ccp1_ccp2_use_timer1,
    ccp1_use_timer1_ccp2_use_timer3,
    ccp1_ccp2_use_timer3
}timer_selector_t;
typedef struct{
#if CCP1_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
    void (* CCP1_handler)(void);
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
    INTERRUPT_PRIORITY_t INTERRUPT_PRIORITY;
#endif
#endif
    ccp1_mode_t ccp1_mode;
    uint8 ccp1_mode_variant;
    pin_config_t pin_config;
#if ((ccp1_cfg_mode_select == ccp1_cfg_capture_mode_select) || (ccp1_cfg_mode_select == ccp1_cfg_compare_mode_select))
    timer_selector_t select_timer_use ;
#endif
#if ccp1_cfg_mode_select == ccp1_cfg_pwm_mode_select
    uint32 pwm_frequence ;
    uint8 timer2_postscaler_cfg :4;
    uint8 timer2_prescaler_cfg  :2;
#endif
}ccp1_t;
/*section : functions declarations  */



Std_ReturnType ccp1_init   (const ccp1_t *ccp1_);
Std_ReturnType ccp1_deinit   (const ccp1_t *ccp1_);




#if ccp1_cfg_mode_select == ccp1_cfg_pwm_mode_select
Std_ReturnType ccp1_pwm_set_duty (const uint8 duty);
Std_ReturnType ccp1_pwm_start    (void);
Std_ReturnType ccp1_pwm_set_stop (void);

#endif

#if ccp1_cfg_mode_select == ccp1_cfg_compare_mode_select
Std_ReturnType ccp1_compare_data_ready (uint8 *compare_statues);
Std_ReturnType ccp1_compare_write_data (uint16 compare_value);
#endif

#if ccp1_cfg_mode_select == ccp1_cfg_capture_mode_select
Std_ReturnType ccp1_capture_data_ready (uint8 *capture_statues);
Std_ReturnType ccp1_capture_read_data  (uint16 *capture_value);
#endif



#endif	/* HAL_CCP1_H */
 

/* capture mode
 
 volatile uint8 l_counter_ccp;
volatile uint32 timer3_over_flow =0 ;
volatile uint32 time_with_us =0 ;
volatile uint32 frequence_with_HZ =0 ;
uint16 reg_ccp_value=0;
volatile uint8 counter_ccp=0;
volatile uint8 counter_timer3_flag=0;
 * 
 * if(counter_ccp == 2){
            time_with_us = (uint32)((counter_timer3_flag*65336) + reg_ccp_value);
            frequence_with_HZ = (uint32)(1 / (time_with_us / 1000000.0));
            counter_ccp=0;
        }
 * 
 * void timer3_callback (void){
    counter_timer3_flag++;
}

void ccp1_callback (void){
    
    l_counter_ccp++;
    counter_ccp++;
    if(l_counter_ccp == 1){
        ret = Timer3_write_value(&Timer3_1,0);
    }
 
 
 
 
 
 */