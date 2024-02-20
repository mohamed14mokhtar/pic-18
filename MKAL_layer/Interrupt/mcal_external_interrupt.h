/* 
 * File:   mcal_external_interrupt.h
 * Author: mokhtar
 *
 * Created on January 24, 2024, 9:00 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/*section : includes */
#include"mcal_interrupt_config.h"

/*section : macro declarations  */


/*section : macro declaration functions  */
#if EXTERNAL_INTERRUPT_INTx_ENABLE == INTERRUPT_FATURE_ENABLE
/* routines to clear or set enable of INT 0 */
#define EXT_INT0_INTERRUPT_ENABLE()     (INTCONbits.INT0IE    = 1)
#define EXT_INT0_INTERRUPT_disABLE()    (INTCONbits.INT0IE    = 0)
/* routines to clear flag of INT 0 */
#define EXT_INT0_INTERRUPT_FLAGE_CLEAR() (INTCONbits.INT0IF = 0)
/* routines to RISING OR FALLING  of INT 0 */
#define EXT_INT0_INTERRUPT_RISING_EDGE()   (INTCON2bits.INTEDG0  = 1)
#define EXT_INT0_INTERRUPT_FALLING_EDGE()  (INTCON2bits.INTEDG0  = 0)

/* routines to clear or set enable of INT 1 */
#define EXT_INT1_INTERRUPT_ENABLE()     (INTCON3bits.INT1IE    = 1)
#define EXT_INT1_INTERRUPT_disABLE()    (INTCON3bits.INT1IE    = 0)
/* routines to clear flag of INT 1 */
#define EXT_INT1_INTERRUPT_FLAGE_CLEAR() (INTCON3bits.INT1IF = 0)
/* routines to RISING OR FALLING  of INT 1 */
#define EXT_INT1_INTERRUPT_RISING_EDGE()   (INTCON2bits.INTEDG1  = 1)
#define EXT_INT1_INTERRUPT_FALLING_EDGE()  (INTCON2bits.INTEDG1  = 0)

/* routines to clear or set enable of INT 2 */
#define EXT_INT2_INTERRUPT_ENABLE()     (INTCON3bits.INT2IE    = 1)
#define EXT_INT2_INTERRUPT_disABLE()    (INTCON3bits.INT2IE    = 0)
/* routines to clear flag of INT */
#define EXT_INT2_INTERRUPT_FLAGE_CLEAR() (INTCON3bits.INT2IF  = 0)
/* routines to RISING OR FALLING  of INT 2 */
#define EXT_INT2_INTERRUPT_RISING_EDGE()   (INTCON2bits.INTEDG2  = 1)
#define EXT_INT2_INTERRUPT_FALLING_EDGE()  (INTCON2bits.INTEDG2  = 0)

#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
/* set high or low priority of INT 1 */
#define INT1_INTERRUPT_high_priority_set() (INTCON3bits.INT1IP =1)
#define INT1_INTERRUPT_low_priority_set()  (INTCON3bits.INT1IP =0)
/* set high or low priority of INT 2 */
#define INT2_INTERRUPT_high_priority_set() (INTCON3bits.INT2IP =1)
#define INT2_INTERRUPT_low_priority_set()  (INTCON3bits.INT2IP =0)

#endif

#endif

#if EXTERNAL_INTERRUPT_interrupt_on_chang_ENABLE == INTERRUPT_FATURE_ENABLE
/* routines to clear or set enable of PBX */
#define EXT_PBX_INTERRUPT_ENABLE()     (INTCONbits.RBIE = 1)
#define EXT_PBX_INTERRUPT_DISABLE()    (INTCONbits.RBIE = 0)
/* routines to clear flag of PRX */
#define EXT_PBX_INTERRUPT_CLEAR_FLAG() (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
/* set high or low priority of PBX */
#define EXT_PBX_INTERRUPT_high_priority_set() (INTCON2bits.RBIP = 1)
#define EXT_PBX_INTERRUPT_low_priority_set()  (INTCON2bits.RBIP = 0)
#endif

#endif

/*section : data type declarations  */
typedef enum {
  INTERRUPT_FALLING_EDGE ,
  INTERRUPT_RISING_EDGE
}INTERRUPT_INTX_edge;

typedef enum {
   INTERRUPT_INT0,
   INTERRUPT_INT1,
   INTERRUPT_INT2
}INTERRUPT_INTX_src;
typedef struct {
    void (* EXT_INTERRUPTHANDLE) (void);
    pin_config_t pin_config;
    INTERRUPT_INTX_edge edge;
    INTERRUPT_INTX_src sorce;
    INTERRUPT_PRIORITY_t priority;
}INTERRUPT_INTX_t;

typedef struct {
    void (* EXT_INTERRUPTHANDLE_high) (void);
    void (* EXT_INTERRUPTHANDLE_low) (void);
    pin_config_t pin_config;
    INTERRUPT_PRIORITY_t priority;
}INTERRUPT_PBX_t;
/*section : functions declarations  */
Std_ReturnType Interrupt_Intx_Inti(const INTERRUPT_INTX_t *INTERRUPT_INTX);
Std_ReturnType Interrupt_Intx_Deinti(const INTERRUPT_INTX_t *INTERRUPT_INTX);
Std_ReturnType Interrupt_Pbx_Inti(const INTERRUPT_PBX_t *INTERRUPT_PBX);
Std_ReturnType Interrupt_Pbx_Deinti(const INTERRUPT_PBX_t *INTERRUPT_PBX);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */




/*
 void func1 (void);
void func2 (void);
void func3 (void);
void func4 (void);
void func5 (void);
void func6 (void);
void func7 (void);
void func8 (void);

led_t led_1 ={.port_name=PORTC_INDEX,.pin=pin0,.led_sta=led_off};
led_t led_2 ={.port_name=PORTC_INDEX,.pin=pin1,.led_sta=led_off};
led_t led_3 ={.port_name=PORTC_INDEX,.pin=pin2,.led_sta=led_off};
led_t led_4 ={.port_name=PORTC_INDEX,.pin=pin3,.led_sta=led_off};
INTERRUPT_PBX_t RB_4 ={.EXT_INTERRUPTHANDLE_high= func1,
                         .EXT_INTERRUPTHANDLE_low=func2,
                         .priority=INTERRUPT_HUGH_PRIORITY,
                         .pin_config.port=PORTB_INDEX,.pin_config.pin=pin4,
                         .pin_config.direction=GPIO_INPUT,.pin_config.logic=GPIO_LOW};


INTERRUPT_PBX_t RB_5 ={.EXT_INTERRUPTHANDLE_high=func3,
                         .EXT_INTERRUPTHANDLE_low=func4,
                         .priority=INTERRUPT_LOW_PRIORITY,
                         .pin_config.port=PORTB_INDEX,.pin_config.pin=pin5,
                         .pin_config.direction=GPIO_INPUT,.pin_config.logic=GPIO_LOW};



INTERRUPT_PBX_t RB_6 ={.EXT_INTERRUPTHANDLE_high=func5,
                         .EXT_INTERRUPTHANDLE_low=func6,
                         .priority=INTERRUPT_LOW_PRIORITY,
                         .pin_config.port=PORTB_INDEX,.pin_config.pin=pin6,
                         .pin_config.direction=GPIO_INPUT,.pin_config.logic=GPIO_LOW};


INTERRUPT_PBX_t RB_7 ={.EXT_INTERRUPTHANDLE_high=func7,
                         .EXT_INTERRUPTHANDLE_low=func8,
                         .priority=INTERRUPT_LOW_PRIORITY,
                         .pin_config.port=PORTB_INDEX,.pin_config.pin=pin7,
                         .pin_config.direction=GPIO_INPUT,.pin_config.logic=GPIO_LOW};
 * 
 * INTERRUPT_INTX_t INT_0 ={.EXT_INTERRUPTHANDLE =func3,.edge=INTERRUPT_FALLING_EDGE,.priority=INTERRUPT_HUGH_PRIORITY,
.sorce=INTERRUPT_INT0,.pin_config.pin=pin0,.pin_config.port=PORTB_INDEX,.pin_config.direction=GPIO_INPUT};

 * void func1 (void){
  Std_ReturnType ret =E_not_ok;
  ret = led_turn_on(&led_1);
  __delay_ms(250);
}
void func2 (void){
    Std_ReturnType ret =E_not_ok;
    ret = led_turn_on(&led_2);
    __delay_ms(250);
}
void func3 (void){
    Std_ReturnType ret =E_not_ok;
    ret = led_toggle (&led_1);
    __delay_ms(250);
}
void func4 (void){
    Std_ReturnType ret =E_not_ok;
    ret = led_toggle (&led_2);
    __delay_ms(250);
}
void func5 (void){
    Std_ReturnType ret =E_not_ok;
  ret = led_turn_on(&led_1);
  __delay_ms(250);
}
void func6 (void){
    Std_ReturnType ret =E_not_ok;
    ret = led_turn_on(&led_2);
    __delay_ms(250);
}
void func7 (void){
    Std_ReturnType ret =E_not_ok;
    ret = led_toggle (&led_1);
    __delay_ms(250);
}
void func8 (void){
     Std_ReturnType ret =E_not_ok;
  ret = led_toggle(&led_2);
  __delay_ms(250);
}
 * 
 */