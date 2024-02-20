/* 
 * File:   hal_ccp2.h
 * Author: mokhtar
 *
 * Created on February 9, 2024, 9:42 AM
 */

#ifndef HAL_CCP2_H
#define	HAL_CCP2_H

/*section : includes */
#include"hal_ccp2_cfg.h"
#include"../mkal_std_types.h"
#include"../pic18_chip_select.h"
#include"../Interrupt/mcal_internal_interrupt.h"
#include"../gpio/pro_gpio.h"
/*section : macro declarations  */
/* mode variant */
#define ccp2_module_disabled                             0
#define ccp2_Capture_mode_every_falling_edge             4
#define ccp2_Capture_mode_every_rising_edge              5
#define ccp2_Capture_mode_every_4th_rising_edge          6
#define ccp2_Capture_mode_every_16th_rising_edge         7
#define ccp2_Compare_mode_toggle_output_on_match         2
#define ccp2_Compare_mode_initialize_pin_low             8
#define ccp2_Compare_mode_initialize_pin_high            9
#define ccp2_Compare_mode_initialize_interrupt           10
#define ccp2_Compare_mode_initialize_even                11
#define ccp2_pwm_initialize                              0x0E

#define ccp2_capture_mode_ready     1
#define ccp2_capture_mode_not_ready 0

#define ccp2_compare_mode_ready     1
#define ccp2_compare_mode_not_ready 0


#define ccp2_Postscale_div_by_1     1
#define ccp2_Postscale_div_by_2     2
#define ccp2_Postscale_div_by_3     3
#define ccp2_Postscale_div_by_4     4
#define ccp2_Postscale_div_by_5     5
#define ccp2_Postscale_div_by_6     6
#define ccp2_Postscale_div_by_7     7
#define ccp2_Postscale_div_by_8     8
#define ccp2_Postscale_div_by_9     9
#define ccp2_Postscale_div_by_10    10
#define ccp2_Postscale_div_by_11    11
#define ccp2_Postscale_div_by_12    12
#define ccp2_Postscale_div_by_13    13
#define ccp2_Postscale_div_by_14    14
#define ccp2_Postscale_div_by_15    15
#define ccp2_Postscale_div_by_16    16



#define ccp2_prescale_div_by_1     1
#define ccp2_prescale_div_by_4     4
#define ccp2_prescale_div_by_16    16

/*section : macro declaration functions  */
#define CCP2_select_statues(_value) (CCP2CONbits.CCP2M =_value)
/*section : data type declarations  */
typedef union{
    struct{
        uint8 ccpr2_l;
        uint8 ccpr2_h;
    };
    struct{
        uint16 ccp2_16bit;
    };
}ccp2_register_t;

typedef enum{
   ccp2_capture_mode_select,
   ccp2_compare_mode_select,
   ccp2_pwm_mode_select       
}ccp2_mode_t;

typedef enum {
    _ccp1_ccp2_use_timer1,
    _ccp1_use_timer1_ccp2_use_timer3,
    _ccp1_ccp2_use_timer3
}ccp2_timer_selector_t;
typedef struct{
#if CCP2_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
    void (* CCP2_handler)(void);
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
    INTERRUPT_PRIORITY_t INTERRUPT_PRIORITY;
#endif
#endif
    ccp2_mode_t ccp2_mode;
    uint8 ccp2_mode_variant;
    pin_config_t pin_config;
#if ((ccp2_cfg_mode_select == ccp2_cfg_capture_mode_select) || (ccp2_cfg_mode_select == ccp2_cfg_compare_mode_select))
    ccp2_timer_selector_t select_timer_use ;
#endif
#if ccp2_cfg_mode_select == ccp2_cfg_pwm_mode_select
    uint32 ccp2_pwm_frequence ;
    uint8 ccp2_timer2_postscaler_cfg :4;
    uint8 ccp2_timer2_prescaler_cfg  :2;
#endif
}ccp2_t;
/*section : functions declarations  */



Std_ReturnType ccp2_init   (const ccp2_t *ccp2_);
Std_ReturnType ccp2_deinit   (const ccp2_t *ccp2_);




#if ccp2_cfg_mode_select == ccp2_cfg_pwm_mode_select
Std_ReturnType ccp2_pwm_set_duty (const uint8 duty);
Std_ReturnType ccp2_pwm_start    (void);
Std_ReturnType ccp2_pwm_set_stop (void);

#endif

#if ccp2_cfg_mode_select == ccp2_cfg_compare_mode_select
Std_ReturnType ccp2_compare_data_ready (uint8 *compare_statues);
Std_ReturnType ccp2_compare_write_data (uint16 compare_value);
#endif

#if ccp2_cfg_mode_select == ccp2_cfg_capture_mode_select
Std_ReturnType ccp2_capture_data_ready (uint8 *capture_statues);
Std_ReturnType ccp2_capture_read_data  (uint16 *capture_value);
#endif



#endif	/* HAL_CCP2_H */

