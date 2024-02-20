/* 
 * File:   mcal_external_interrupt.c
 * Author: mokhtar
 *
 * Created on January 24, 2024, 9:00 PM
 */

#include"mcal_interrupt_config.h"
#include"mcal_external_interrupt.h"

static void (* Int0_interrupthandler) (void) = NULL;
static void (* Int1_interrupthandler) (void) = NULL;
static void (* Int2_interrupthandler) (void) = NULL;

static void (* RB4_interrupthandler_high) (void) =NULL;
static void (* RB4_interrupthandler_low ) (void) =NULL;
static void (* RB5_interrupthandler_high) (void) =NULL;
static void (* RB5_interrupthandler_low ) (void) =NULL;
static void (* RB6_interrupthandler_high) (void) =NULL;
static void (* RB6_interrupthandler_low ) (void) =NULL;
static void (* RB7_interrupthandler_high) (void) =NULL;
static void (* RB7_interrupthandler_low ) (void) =NULL;

static Std_ReturnType interrupt_intx_enable(const INTERRUPT_INTX_t *INTERRUPT_INTX);
static Std_ReturnType interrupt_intx_disable(const INTERRUPT_INTX_t *INTERRUPT_INTX);
static Std_ReturnType interrupt_intx_edge_inti(const INTERRUPT_INTX_t *INTERRUPT_INTX);
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
static Std_ReturnType interrupt_intx_priority_inti(const INTERRUPT_INTX_t *INTERRUPT_INTX);
#endif
static Std_ReturnType interrupt_intx_pin_inti(const INTERRUPT_INTX_t *INTERRUPT_INTX);
static Std_ReturnType interrupt_intx_clear(const INTERRUPT_INTX_t *INTERRUPT_INTX);

static Std_ReturnType INT0_setinterrupthandler(void (* interrupthandler) (void));
static Std_ReturnType INT1_setinterrupthandler(void (* interrupthandler) (void));
static Std_ReturnType INT2_setinterrupthandler(void (* interrupthandler) (void));
static Std_ReturnType interrupt_intx_sethandler(const INTERRUPT_INTX_t *INTERRUPT_INTX);

/**
 * 
 * @param INTERRUPT_INTX
 * @return 
 */
Std_ReturnType Interrupt_Intx_Inti(const INTERRUPT_INTX_t *INTERRUPT_INTX){
    Std_ReturnType ret =E_not_ok;
    if(NULL == INTERRUPT_INTX){
        ret =E_not_ok;
    }
    else
    {
        /*first will do disable*/
        ret = interrupt_intx_disable(INTERRUPT_INTX);
        /* clear */
        ret = interrupt_intx_clear(INTERRUPT_INTX);
        /* edge */
        ret = interrupt_intx_edge_inti(INTERRUPT_INTX);
        /* priority check */
        #if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
        ret = interrupt_intx_priority_inti(INTERRUPT_INTX);
        #endif
        /* pin set */
        ret = interrupt_intx_pin_inti(INTERRUPT_INTX);
        /* callback function */
        ret = interrupt_intx_sethandler(INTERRUPT_INTX);
        /* enable */
        ret = interrupt_intx_enable(INTERRUPT_INTX);
    }
    
    return ret ;
}
/**
 * 
 * @param INTERRUPT_INTX
 * @return 
 */
Std_ReturnType Interrupt_Intx_Deinti(const INTERRUPT_INTX_t *INTERRUPT_INTX){
    Std_ReturnType ret =E_not_ok;
    if(NULL == INTERRUPT_INTX){
        ret =E_not_ok;
    }
    else
    {
       ret = interrupt_intx_disable(INTERRUPT_INTX); 
    }
    
    return ret ;
}
/**
 * 
 * @param INTERRUPT_INTX
 * @return 
 */
Std_ReturnType Interrupt_Pbx_Inti(const INTERRUPT_PBX_t *INTERRUPT_PBX){
    Std_ReturnType ret =E_not_ok;
    if(NULL == INTERRUPT_PBX){
        ret =E_not_ok;
    }
    else
    {
        /* disable */
        EXT_PBX_INTERRUPT_DISABLE();
        /* clear */
        EXT_PBX_INTERRUPT_CLEAR_FLAG();
        /* priority */
         #if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
                INTERRUPT_prioritylevelenable();
                if(INTERRUPT_LOW_PRIORITY == INTERRUPT_PBX->priority){
                    EXT_PBX_INTERRUPT_low_priority_set();
                    INTERRUPT_globalinterruptlowenable();
                    
                }
                else if(INTERRUPT_HUGH_PRIORITY == INTERRUPT_PBX->priority){
                    EXT_PBX_INTERRUPT_high_priority_set();
                    INTERRUPT_globalinterrupthighenable();
                    
                }
                else{/*nothing*/}
                #else
                INTERRUPT_globalinterruptenable();
                INTERRUPT_peripheralinterruptenable();
                #endif
        /*set pit */
        ret = GPIO_pIN_DIRECTION_INTIALIZE(&(INTERRUPT_PBX->pin_config));
        /* callback function */
        switch (INTERRUPT_PBX->pin_config.pin){
            case pin4 :
                RB4_interrupthandler_high = INTERRUPT_PBX->EXT_INTERRUPTHANDLE_high;
                RB4_interrupthandler_low = INTERRUPT_PBX->EXT_INTERRUPTHANDLE_low;
                break;
             case pin5 :
                RB5_interrupthandler_high = INTERRUPT_PBX->EXT_INTERRUPTHANDLE_high;
                RB5_interrupthandler_low = INTERRUPT_PBX->EXT_INTERRUPTHANDLE_low;
                break;
             case pin6 :
                RB6_interrupthandler_high = INTERRUPT_PBX->EXT_INTERRUPTHANDLE_high;
                RB6_interrupthandler_low = INTERRUPT_PBX->EXT_INTERRUPTHANDLE_low;
                break;
             case pin7 :
                RB7_interrupthandler_high = INTERRUPT_PBX->EXT_INTERRUPTHANDLE_high;
                RB7_interrupthandler_low = INTERRUPT_PBX->EXT_INTERRUPTHANDLE_low;
                break;
        }
        /* enable */
        EXT_PBX_INTERRUPT_ENABLE();
        ret =E_OK ;
    }
    
    return ret ;
}
/**
 * 
 * @param INTERRUPT_INTX
 * @return 
 */
Std_ReturnType Interrupt_Pbx_Deinti(const INTERRUPT_PBX_t *INTERRUPT_PBX){
    Std_ReturnType ret =E_not_ok;
    if(NULL == INTERRUPT_PBX){
        ret =E_not_ok;
    }
    else
    {
        
    }
    
    return ret ;
}
/***********************  helper function 1 *******************************/
/**
 * 
 * @param INTERRUPT_INTX
 * @return 
 */
static Std_ReturnType interrupt_intx_enable(const INTERRUPT_INTX_t *INTERRUPT_INTX){
    Std_ReturnType ret =E_not_ok;
    if(NULL == INTERRUPT_INTX){
        ret =E_not_ok;
    }
    else
    {
        switch (INTERRUPT_INTX->sorce){
            case INTERRUPT_INT0: 
                #if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
                INTERRUPT_globalinterrupthighenable();
                #else
                INTERRUPT_globalinterruptenable();
                INTERRUPT_peripheralinterruptenable();
                #endif
                EXT_INT0_INTERRUPT_ENABLE();
                ret =E_OK;
                break;
            case INTERRUPT_INT1:
                #if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
                INTERRUPT_prioritylevelenable();
                if(INTERRUPT_LOW_PRIORITY == INTERRUPT_INTX->priority){
                    INTERRUPT_globalinterruptlowenable();
                    
                }
                else if(INTERRUPT_HUGH_PRIORITY == INTERRUPT_INTX->priority){
                    INTERRUPT_globalinterrupthighenable();
                    
                }
                else{/*nothing*/}
                #else
                INTERRUPT_globalinterruptenable();
                INTERRUPT_peripheralinterruptenable();
                #endif
                EXT_INT1_INTERRUPT_ENABLE();
                ret =E_OK;
                break;
            case INTERRUPT_INT2: 
                #if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
                INTERRUPT_prioritylevelenable();
                if(INTERRUPT_LOW_PRIORITY == INTERRUPT_INTX->priority){
                    
                    INTERRUPT_globalinterruptlowenable();
                }
                else if(INTERRUPT_HUGH_PRIORITY == INTERRUPT_INTX->priority){
                    INTERRUPT_globalinterrupthighenable();
                    
                    
                }
                else{/*nothing*/}
                #else
                INTERRUPT_globalinterruptenable();
                INTERRUPT_peripheralinterruptenable();
                #endif
                EXT_INT2_INTERRUPT_ENABLE();
                ret =E_OK;
                break;
            default : ret =E_not_ok;
        }
    }
    
    return ret ;
}
/**
 * 
 * @param INTERRUPT_INTX
 * @return 
 */
static Std_ReturnType interrupt_intx_disable(const INTERRUPT_INTX_t *INTERRUPT_INTX){
    Std_ReturnType ret =E_not_ok;
    if(NULL == INTERRUPT_INTX){
        ret =E_not_ok;
    }
    else
    {
        switch (INTERRUPT_INTX->sorce){
            case INTERRUPT_INT0: 
                EXT_INT0_INTERRUPT_disABLE();
                ret =E_OK;
                break;
            case INTERRUPT_INT1: 
                EXT_INT1_INTERRUPT_disABLE();
                ret =E_OK;
                break;
            case INTERRUPT_INT2: 
                EXT_INT2_INTERRUPT_disABLE();
                ret =E_OK;
                break;
            default : ret =E_not_ok;
        }
    }
    
    return ret ;
    
}
/**
 * 
 * @param INTERRUPT_INTX
 * @return 
 */
static Std_ReturnType interrupt_intx_edge_inti(const INTERRUPT_INTX_t *INTERRUPT_INTX){
    Std_ReturnType ret =E_not_ok;
    if(NULL == INTERRUPT_INTX){
        ret =E_not_ok;
    }
    else
    {
        switch (INTERRUPT_INTX->sorce){
            case INTERRUPT_INT0: 
                if(INTERRUPT_FALLING_EDGE == INTERRUPT_INTX->edge){
                    EXT_INT0_INTERRUPT_FALLING_EDGE();
                }
                else if(INTERRUPT_RISING_EDGE == INTERRUPT_INTX->edge){
                    EXT_INT0_INTERRUPT_RISING_EDGE();
                }
                else{/*nothing*/}
                ret =E_OK;
                break;
            case INTERRUPT_INT1: 
                if(INTERRUPT_FALLING_EDGE == INTERRUPT_INTX->edge){
                    EXT_INT1_INTERRUPT_FALLING_EDGE();
                }
                else if(INTERRUPT_RISING_EDGE == INTERRUPT_INTX->edge){
                    EXT_INT1_INTERRUPT_RISING_EDGE();
                }
                else{/*nothing*/}
                ret =E_OK;
                break;
            case INTERRUPT_INT2: 
               if(INTERRUPT_FALLING_EDGE == INTERRUPT_INTX->edge){
                    EXT_INT2_INTERRUPT_FALLING_EDGE();
                }
                else if(INTERRUPT_RISING_EDGE == INTERRUPT_INTX->edge){
                    EXT_INT2_INTERRUPT_RISING_EDGE();
                }
                else{/*nothing*/}
                ret =E_OK;
                break;
            default : ret =E_not_ok;
        }
    }
    
    return ret ;

}
/**
 * 
 * @param INTERRUPT_INTX
 * @return 
 */
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
static Std_ReturnType interrupt_intx_priority_inti(const INTERRUPT_INTX_t *INTERRUPT_INTX){
    Std_ReturnType ret =E_not_ok;
    if(NULL == INTERRUPT_INTX){
        ret =E_not_ok;
    }
    else
    {
         switch (INTERRUPT_INTX->sorce){
            case INTERRUPT_INT0: 
                ret =E_OK;
                break;
            case INTERRUPT_INT1: 
                if(INTERRUPT_LOW_PRIORITY == INTERRUPT_INTX->priority){
                    INT1_INTERRUPT_low_priority_set();
                }
                else if(INTERRUPT_HUGH_PRIORITY == INTERRUPT_INTX->priority){
                    INT1_INTERRUPT_high_priority_set();
                }
                else{/*nothing*/}
                
                ret =E_OK;
                break;
            case INTERRUPT_INT2: 
               if(INTERRUPT_LOW_PRIORITY == INTERRUPT_INTX->priority){
                    INT2_INTERRUPT_low_priority_set();
                }
                else if(INTERRUPT_HUGH_PRIORITY == INTERRUPT_INTX->priority){
                    INT2_INTERRUPT_high_priority_set();
                }
                else{/*nothing*/}
                ret =E_OK;
                break;
            default : ret =E_not_ok;
        }
    }
    
    return ret ;
}
#endif
/**
 * 
 * @param INTERRUPT_INTX
 * @return 
 */
static Std_ReturnType interrupt_intx_pin_inti(const INTERRUPT_INTX_t *INTERRUPT_INTX){
    Std_ReturnType ret =E_not_ok;
    if(NULL == INTERRUPT_INTX){
        ret =E_not_ok;
    }
    else
    {
        ret =GPIO_pIN_INTIALIZE(&(INTERRUPT_INTX->pin_config));
    }
    
    return ret ;
}
/**
 * 
 * @param INTERRUPT_INTX
 * @return 
 */
static Std_ReturnType interrupt_intx_clear(const INTERRUPT_INTX_t *INTERRUPT_INTX){
    Std_ReturnType ret =E_not_ok;
    if(NULL == INTERRUPT_INTX){
        ret =E_not_ok;
    }
    else
    {
        switch (INTERRUPT_INTX->sorce){
            case INTERRUPT_INT0: 
                EXT_INT0_INTERRUPT_FLAGE_CLEAR();
                ret =E_OK;
                break;
            case INTERRUPT_INT1: 
                EXT_INT1_INTERRUPT_FLAGE_CLEAR();
                ret =E_OK;
                break;
            case INTERRUPT_INT2: 
                EXT_INT2_INTERRUPT_FLAGE_CLEAR();
                ret =E_OK;
                break;
            default : ret =E_not_ok;
        }
    }
    
    return ret ;
    
}

/***********************  helper function 1 *******************************/
/**
 * 
 * @param Int0_interrupthandler
 * @return 
 */
static Std_ReturnType INT0_setinterrupthandler(void (* interrupthandler) (void)){
    Std_ReturnType ret =E_not_ok;
    if(NULL == interrupthandler){
        ret =E_not_ok;
    }
    else{
        Int0_interrupthandler = interrupthandler;
    }
}
/**
 * 
 * @param Int1_interrupthandler
 * @return 
 */
static Std_ReturnType INT1_setinterrupthandler(void (* interrupthandler) (void)){
    Std_ReturnType ret =E_not_ok;
    if(NULL == interrupthandler){
        ret =E_not_ok;
    }
    else{
        Int1_interrupthandler = interrupthandler;
    }
}
/**
 * 
 * @param Int2_interrupthandler
 * @return 
 */
static Std_ReturnType INT2_setinterrupthandler(void (* interrupthandler) (void)){
    Std_ReturnType ret =E_not_ok;
    if(NULL == interrupthandler){
        ret =E_not_ok;
    }
    else{
        Int2_interrupthandler = interrupthandler;
    }
}
/**
 * 
 * @param INTERRUPT_INTX
 * @return 
 */
static Std_ReturnType interrupt_intx_sethandler(const INTERRUPT_INTX_t *INTERRUPT_INTX){
    Std_ReturnType ret =E_not_ok;
    if(NULL == INTERRUPT_INTX){
        ret =E_not_ok;
    }
    else
    {
        switch (INTERRUPT_INTX->sorce){
            case INTERRUPT_INT0: 
                INT0_setinterrupthandler(INTERRUPT_INTX->EXT_INTERRUPTHANDLE);
                break;
            case INTERRUPT_INT1: 
                ret =INT1_setinterrupthandler(INTERRUPT_INTX->EXT_INTERRUPTHANDLE);
                break;
            case INTERRUPT_INT2: 
                ret =INT2_setinterrupthandler(INTERRUPT_INTX->EXT_INTERRUPTHANDLE);;
                break;
            default : ret =E_not_ok;
        }
    }
    
    return ret ;
    
}
/********************* ending function ***********************/
void INT0_ISR (void){
    /* clear */
    EXT_INT0_INTERRUPT_FLAGE_CLEAR();
    /* any code I want*/
    
    /* callback function */
    if(Int0_interrupthandler){
        Int0_interrupthandler();
    }
    else{
        /* nothing */
    }
}
void INT1_ISR (void){
    /* clear */
    EXT_INT1_INTERRUPT_FLAGE_CLEAR();
    /* any code I want*/
    
    /* callback function */
    if(Int1_interrupthandler){
        Int1_interrupthandler();
    }
    else{
        /* nothing */
    }
}
void INT2_ISR (void){
    /* clear */
    EXT_INT2_INTERRUPT_FLAGE_CLEAR();
    /* any code I want*/
    
    /* callback function */
    if(Int2_interrupthandler){
        Int2_interrupthandler();
    }
    else{
        /* nothing */
    }
}

void RB4_ISR(uint8 value){
    /* clear */
    EXT_PBX_INTERRUPT_CLEAR_FLAG();
    /* any code i want */
    
    /*callback function */
    if(1 == value){
        if(RB4_interrupthandler_high){
            RB4_interrupthandler_high();
        }
        else{ /* nothing */ }
    }
    else if(0 == value){
          if(RB4_interrupthandler_low){
             RB4_interrupthandler_low();
        }
        else{ /* nothing */ }
    }
    else{ /* nothing */ }
}
void RB5_ISR(uint8 value){
     /* clear */
    EXT_PBX_INTERRUPT_CLEAR_FLAG();
    /* any code i want */
    
    /*callback function */
    if(1 == value){
        if(RB5_interrupthandler_high){
            RB5_interrupthandler_high();
        }
        else{ /* nothing */ }
    }
    else if(0 == value){
          if(RB5_interrupthandler_low){
             RB5_interrupthandler_low();
        }
        else{ /* nothing */ }
    }
    else{ /* nothing */ }
}
void RB6_ISR(uint8 value){
     /* clear */
    EXT_PBX_INTERRUPT_CLEAR_FLAG();
    /* any code i want */
    
    /*callback function */
    if(1 == value){
        if(RB6_interrupthandler_high){
            RB6_interrupthandler_high();
        }
        else{ /* nothing */ }
    }
    else if(0 == value){
          if(RB6_interrupthandler_low){
             RB6_interrupthandler_low();
        }
        else{ /* nothing */ }
    }
    else{ /* nothing */ }
}
void RB7_ISR(uint8 value){
     /* clear */
    EXT_PBX_INTERRUPT_CLEAR_FLAG();
    /* any code i want */
    
    /*callback function */
    if(1 == value){
        if(RB7_interrupthandler_high){
            RB7_interrupthandler_high();
        }
        else{ /* nothing */ }
    }
    else if(0 == value){
          if(RB7_interrupthandler_low){
             RB7_interrupthandler_low();
        }
        else{ /* nothing */ }
    }
    else{ /* nothing */ }
}