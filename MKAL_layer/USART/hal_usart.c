/* 
 * File:   hal_usart.c
 * Author: mokhtar
 *
 * Created on February 13, 2024, 11:09 AM
 */

#include"hal_usart.h"

static void (* USART_TX_Interrupthandler)(void);
static void (* USART_RX_Interrupthandler)(void);
static void (* USART_FRAMERROR_Interrupthandler)(void);
static void (* USART_OVERRUN_Interrupthandler)(void);

static void baudrate_calculate(const usart_t *usart);
static void usart_async_tx_int(const usart_t *usart);
static void usart_async_rx_int(const usart_t *usart);

static uint8 data_return ;

Std_ReturnType usart_ASYNC_init (const usart_t *usart){
    Std_ReturnType ret = E_not_ok;
    if (NULL == usart){
        ret =E_not_ok;
    }
    else
    {
        /* disable usart */
        RCSTAbits.SPEN =USART__MODE_DISABLE;
        /* baud rate calculate */
        baudrate_calculate(usart);
        /* ASYNCHRONOUS TX AND RX INITIALIZE */
        TRISCbits.RC6 = GPIO_INPUT;
        TRISCbits.RC7 = GPIO_INPUT;
        usart_async_tx_int(usart);
        usart_async_rx_int(usart);
        /* enable usart */
        RCSTAbits.SPEN =USART__MODE_ENABLE;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType usart_ASYNC_deinit (const usart_t *usart){
    Std_ReturnType ret = E_not_ok;
    if (NULL == usart){
        ret =E_not_ok;
    }
    else
    {
        RCSTAbits.SPEN =USART__MODE_DISABLE;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType usart_ASYNC_read_byte_blocking (uint8 *data){
    Std_ReturnType ret = E_not_ok;
        while(!PIR1bits.RCIF){
        }
        *data = RCREG;
        ret = E_OK;
    return ret;
}

Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data){
    Std_ReturnType ret = E_not_ok;
    if(1 == PIR1bits.RCIF){
        *_data = RCREG;
        ret = E_OK;
    }
    else{
        ret = E_not_ok;
    }
    return ret;
}

Std_ReturnType usart_ASYNC_write_byte_blocking (uint8 data){
    Std_ReturnType ret = E_not_ok;
        while(!TXSTAbits.TRMT);
#if USEAR_TX_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
        usart_tx_INTERRUPT_ENABLE();
#endif
        TXREG = data;
        ret = E_OK;
    return ret;
}

Std_ReturnType usart_ASYNC_write_string_blocking (uint8 *data , uint16 str_lenght){
     Std_ReturnType ret = E_not_ok;
     uint16 l_counter =0 ;
    if (NULL == data){
        ret =E_not_ok;
    }
    else{
        for(l_counter = 0 ;l_counter < str_lenght ;l_counter++){
            ret = usart_ASYNC_write_byte_blocking(data[l_counter]);
        }
        ret =E_OK;
    }
     return ret;
}

static void baudrate_calculate(const usart_t *usart){
    float baud_rate =0;
    switch (usart->buadrate_gen){
        case BAUDRATE_ASY_8BIT_LOW_SPEED :
            /* synch mode */
            TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE;
            /* speed */
            TXSTAbits.BRGH = USART_ASYNCHRONOUS_LOW_SPEAD;
            /* register bits */
            BAUDCONbits.BRG16 = USART_ASYNCHRONOUS_08BIT;
            /* register value */
            baud_rate = (((_XTAL_FREQ/(float)usart->baudrate)/64)-1);
            break;
        case BAUDRATE_ASY_8BIT_HIGH_SPEED :
            /* synch mode */
            TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE;
            /* speed */
            TXSTAbits.BRGH = USART_ASYNCHRONOUS_HIGH_SPEAD;
            /* register bits */
            BAUDCONbits.BRG16 = USART_ASYNCHRONOUS_08BIT;
            /* register value */
            baud_rate = (((_XTAL_FREQ/(float)usart->baudrate)/16)-1);
            break;
        case BAUDRATE_ASY_16BIT_LOW_SPEED :
            /* synch mode */
            TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE;
            /* speed */
            TXSTAbits.BRGH = USART_ASYNCHRONOUS_LOW_SPEAD;
            /* register bits */
            BAUDCONbits.BRG16 = USART_ASYNCHRONOUS_16BIT;
            /* register value */
            baud_rate = (((_XTAL_FREQ/(float)usart->baudrate)/16)-1);
            break;
        case BAUDRATE_ASY_16BIT_HIGH_SPEED :
            /* synch mode */
            TXSTAbits.SYNC = USART_ASYNCHRONOUS_MODE;
            /* speed */
            TXSTAbits.BRGH = USART_ASYNCHRONOUS_HIGH_SPEAD;
            /* register bits */
            BAUDCONbits.BRG16 = USART_ASYNCHRONOUS_16BIT;
            /* register value */
            baud_rate = (((_XTAL_FREQ/(float)usart->baudrate)/4)-1);
            break;
        case BAUDRATE_SY_8BIT :
            /* synch mode */
            TXSTAbits.SYNC = USART_SYNCHRONOUS_MODE;
            /* speed */
            TXSTAbits.BRGH = USART_ASYNCHRONOUS_LOW_SPEAD;
            /* register value */
            baud_rate = (((_XTAL_FREQ/(float)usart->baudrate)/4)-1);
            break;
        case BAUDRATE_SY_16BIT :
            /* synch mode */
            TXSTAbits.SYNC = USART_SYNCHRONOUS_MODE;
            /* register bits */
            BAUDCONbits.BRG16 = USART_ASYNCHRONOUS_08BIT;
            /* register value */
            baud_rate = (((_XTAL_FREQ/(float)usart->baudrate)/4)-1);
            break;
    }
    SPBRG  =(uint8)((uint32)baud_rate);
    SPBRGH =(uint8)(((uint32)baud_rate) >> 8);
}

static void usart_async_tx_int(const usart_t *usart){
    if(usart->usart_tx.usart_tx_enable == USART_ASYNCHRONOUS_TX_ENABLE){
        TXSTAbits.TXEN =USART_ASYNCHRONOUS_TX_ENABLE;
        if(usart->usart_tx.usart_tx_interrupt_enable == USART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE){
            usart_tx_INTERRUPT_ENABLE();
            USART_TX_Interrupthandler = usart->USART_TX_INTERRUPT_HANDLER;
#if USEAR_TX_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE 
            usart_tx_INTERRUPT_ENABLE();
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
            INTERRUPT_prioritylevelenable();
        if(usart->usart_tx.INTERRUPT_PRIORITY_TX == INTERRUPT_HUGH_PRIORITY){
            INTERRUPT_globalinterrupthighenable();
            usart_tx_INTERRUPT_high_priority_set();
        }
        else if(usart->usart_tx.INTERRUPT_PRIORITY_TX == INTERRUPT_LOW_PRIORITY){
            INTERRUPT_globalinterruptlowenable();
            usart_tx_INTERRUPT_low_priority_set();
        }
        else{ /*nothing*/ }
#else 
        INTERRUPT_globalinterruptenable();
        INTERRUPT_peripheralinterruptenable();
      
#endif        
#endif
        }
        else if(usart->usart_tx.usart_tx_interrupt_enable == USART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE){
            usart_tx_INTERRUPT_disABLE();
        }
        else{ /* nothing */ }
        if(usart->usart_tx.usart_tx_9bits_enable == USART_ASYNCHRONOUS_9BITS_TX_ENABLE){
            TXSTAbits.TX9 = USART_ASYNCHRONOUS_9BITS_TX_ENABLE;
        }
        else if(usart->usart_tx.usart_tx_interrupt_enable == USART_ASYNCHRONOUS_9BITS_TX_DISABLE){
            TXSTAbits.TX9 = USART_ASYNCHRONOUS_9BITS_TX_DISABLE;
        }
        else{ /* nothing */ }
    }
    else if(usart->usart_tx.usart_tx_enable == USART_ASYNCHRONOUS_TX_ENABLE){
        TXSTAbits.TXEN =USART_ASYNCHRONOUS_TX_ENABLE;
    }
    else{ /* nothing */ }
}

static void usart_async_rx_int(const usart_t *usart){
    if(usart->usart_rx.usart_rx_enable == USART_ASYNCHRONOUS_RX_ENABLE){
        RCSTAbits.CREN =USART_ASYNCHRONOUS_RX_ENABLE;
        if(usart->usart_rx.usart_rx_interrupt_enable == USART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE){
            usart_rx_INTERRUPT_ENABLE();
#if USEAR_RX_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
            USART_RX_Interrupthandler = usart->USART_RX_INTERRUPT_HANDLER;
            USART_FRAMERROR_Interrupthandler = usart->USART_FRAMING_ERROR_INTERRUPT_HANDLER;
            USART_OVERRUN_Interrupthandler = usart->USART_OVERRUN_ERROR_INTERRUPT_HANDLER;
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
        INTERRUPT_prioritylevelenable();
        if(usart->usart_rx.INTERRUPT_PRIORITY_RX == INTERRUPT_HUGH_PRIORITY){
            INTERRUPT_globalinterrupthighenable();
            usart_rx_INTERRUPT_high_priority_set();
        }
        else if(usart->usart_rx.INTERRUPT_PRIORITY_RX == INTERRUPT_LOW_PRIORITY){
            INTERRUPT_globalinterruptlowenable();
            usart_rx_INTERRUPT_low_priority_set();
        }
        else{ /*nothing*/ }
#else 
        INTERRUPT_globalinterruptenable();
        INTERRUPT_peripheralinterruptenable();
       
#endif        
#endif
        }
        else if(usart->usart_rx.usart_rx_interrupt_enable == USART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE){
            usart_rx_INTERRUPT_disABLE();
        }
        else{ /* nothing */ }
        if(usart->usart_rx.usart_rx_9bits_enable == USART_ASYNCHRONOUS_9BITS_RX_ENABLE){
            RCSTAbits.RX9 = USART_ASYNCHRONOUS_9BITS_RX_ENABLE;
        }
        else if(usart->usart_rx.usart_rx_interrupt_enable == USART_ASYNCHRONOUS_9BITS_RX_DISABLE){
            RCSTAbits.RX9 = USART_ASYNCHRONOUS_9BITS_RX_DISABLE;
        }
        else{ /* nothing */ }
    }
    else if(usart->usart_rx.usart_rx_enable == USART_ASYNCHRONOUS_RX_ENABLE){
        RCSTAbits.CREN =USART_ASYNCHRONOUS_RX_ENABLE;
    }
    else{ /* nothing */ }
}


void USART_TX_ISR(void){
    usart_tx_INTERRUPT_disABLE();
    if(USART_TX_Interrupthandler){
        USART_TX_Interrupthandler();
    }
    else{}
}

void USART_RX_ISR(void){
    if(USART_RX_Interrupthandler){
        USART_RX_Interrupthandler();
    }else{}
}