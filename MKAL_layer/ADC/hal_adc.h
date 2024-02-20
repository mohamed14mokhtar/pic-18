/* 
 * File:   hal_adc.h
 * Author: mokhtar
 *
 * Created on January 30, 2024, 4:50 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/*section : includes */
#include"hal_adc_cfg.h"
#include"../pic18_chip_select.h"
#include"../mkal_std_types.h"
#include"../gpio/pro_gpio.h"
#include"../Interrupt/mcal_internal_interrupt.h"
/*section : macro declarations  */
#define ADC_AN0_ANALOG_FUNCTION  0X0E
#define ADC_AN1_ANALOG_FUNCTION  0X0D
#define ADC_AN2_ANALOG_FUNCTION  0X0C
#define ADC_AN3_ANALOG_FUNCTION  0X0B
#define ADC_AN4_ANALOG_FUNCTION  0X0A
#define ADC_AN5_ANALOG_FUNCTION  0X09
#define ADC_AN6_ANALOG_FUNCTION  0X08
#define ADC_AN7_ANALOG_FUNCTION  0X07
#define ADC_AN8_ANALOG_FUNCTION  0X06
#define ADC_AN9_ANALOG_FUNCTION  0X05
#define ADC_AN10_ANALOG_FUNCTION 0X04
#define ADC_AN11_ANALOG_FUNCTION 0X03
#define ADC_AN12_ANALOG_FUNCTION 0X02
#define ADC_ALL_ANALOG_FUNCTION  0X00
#define ADC_ALL_DIGITAL_FUNCTION 0X0F




#define ADC_result_right 1
#define ADC_result_left  0

#define voltage_ref_enable  1
#define voltage_ref_disable 0

/*section : macro declaration functions  */

/* if ADC_Conversion_Status enable = doing_function / disable = finshed_function */
#define ADC_Conversion_Status()        (ADCON0bits.GO_nDONE)
#define ADC_START_CONVERTION() (ADCON0bits.GODONE =1)
/* enable or disable ADC */
#define ADC_CONVERTER_ENABLE()  (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE() (ADCON0bits.ADON = 0)

/* voltage reference select source */
#define ADC_ENABLE_VOLTAGE_FERERENCE_1()  (ADCON1bits.VCFG0 = 1)
#define ADC_ENABLE_VOLTAGE_FERERENCE_2()  (ADCON1bits.VCFG1 = 1)
#define ADC_DISABLE_VOLTAGE_FERERENCE_1()  (ADCON1bits.VCFG0 = 0)
#define ADC_DISABLE_VOLTAGE_FERERENCE_2()  (ADCON1bits.VCFG0 = 0)  

/* select format */
#define ADC_CONVERTER_RIGHT_justified() (ADCON2bits.ADFM = 1) 
#define ADC_CONVERTER_LEFT_justified()  (ADCON2bits.ADFM = 0)  

/* port configure  */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_port) (ADCON1bits.PCFG = _port)

/*section : data type declarations  */
typedef enum {
    ADC_CHANNEL_AN0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
}ADC_CHANNAL_SELECT_t;

typedef enum {
    ADC_0_TAD,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD,
}Acquisition_time_t;

typedef enum {
    FOSC_div_2,
    FOSC_div_8,
    FOSC_div_32,
    FRC,
    FOSC_div_4,
    FOSC_div_16,
    FOSC_div_64
}Conversion_Clock_t;


typedef struct {
#if    ADC_INTERRUPT_feature_ENABLE    == INTERRUPT_FATURE_ENABLE
    void (* ADC_interruptHandler) (void);
#if    INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
    INTERRUPT_PRIORITY_t INTERRUPT_PRIORITY;
#endif
#endif
    ADC_CHANNAL_SELECT_t ADC_CHANNAL_SELECT;
    Acquisition_time_t Acquisition_time;
    Conversion_Clock_t Conversion_Clock;
    uint8 voltage_ref     :1;
    uint8 result_format   :1;
    uint8 ADC_reserved    :6;
}ADC_conf_t;

typedef uint16 adc_result_t;
/*section : functions declarations  */
Std_ReturnType ADC_inti(const ADC_conf_t *ADC_conf);
Std_ReturnType ADC_deinti(const ADC_conf_t *ADC_conf);
Std_ReturnType ADC_select_channal(const ADC_conf_t *ADC_conf,const ADC_CHANNAL_SELECT_t ADC_CHANNAL_SELECT);
Std_ReturnType ADC_start_conversion(const ADC_conf_t *ADC_conf);
Std_ReturnType ADC_ISconversion_done(const ADC_conf_t *ADC_conf , uint8 *conversion_status);
Std_ReturnType ADC_ISconversion_result(const ADC_conf_t *ADC_conf , adc_result_t *conversion_result);
Std_ReturnType ADC_get_conversion_blocking(const ADC_conf_t *ADC_conf , ADC_CHANNAL_SELECT_t ADC_CHANNAL_SELECT 
                                  ,adc_result_t *conversion_status);
Std_ReturnType ADC_start_conversion_interrupt(const ADC_conf_t *ADC_conf , ADC_CHANNAL_SELECT_t ADC_CHANNAL_SELECT );
#endif	/* HAL_ADC_H */




/* whit out interrupt future  */
/*
 ADC_conf_t ACD_1 = {.Acquisition_time =ADC_12_TAD,.Conversion_Clock =FOSC_div_16,
                    .ADC_CHANNAL_SELECT=ADC_CHANNEL_AN0,.result_format =ADC_result_right,.voltage_ref=voltage_ref_disable};

 */

/* whit interrupt future  */
/*
 ADC_conf_t ACD_1 = {.ADC_interruptHandler = ADC_callback,.Acquisition_time =ADC_12_TAD,
                    .Conversion_Clock =FOSC_div_16,.ADC_CHANNAL_SELECT=ADC_CHANNEL_AN0,
                    .result_format =ADC_result_right,.voltage_ref=voltage_ref_disable};
 */