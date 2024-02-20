/* 
 * File:   hal_usart.h
 * Author: mokhtar
 *
 * Created on February 13, 2024, 11:09 AM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/*section : includes */
#include"hal_usart_cfg.h"
#include"../mkal_std_types.h"
#include"../pic18_chip_select.h"
#include"../Interrupt/mcal_internal_interrupt.h"
#include"../gpio/pro_gpio.h"
/*section : macro declarations  */
/* usart mode enable */
#define USART__MODE_ENABLE    1
#define USART__MODE_DISABLE   0
/* select usear mode TXSTAbits.SYNC */
#define USART_ASYNCHRONOUS_MODE  0
#define USART_SYNCHRONOUS_MODE   1
/* asynchronous baud rate mode TXSTAbits.BRGH */
#define USART_ASYNCHRONOUS_HIGH_SPEAD    1
#define USART_ASYNCHRONOUS_LOW_SPEAD     0
/* baud rate size register */
#define USART_ASYNCHRONOUS_08BIT     0
#define USART_ASYNCHRONOUS_16BIT     1

/* usart transmit enable */
#define USART_ASYNCHRONOUS_TX_ENABLE      1
#define USART_ASYNCHRONOUS_TX_DISABLE     0
/* usart transmit enterrupt enable */
#define USART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE      1
#define USART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE     0
/* usart transmit 9_bits enable */
#define USART_ASYNCHRONOUS_9BITS_TX_ENABLE      1
#define USART_ASYNCHRONOUS_9BITS_TX_DISABLE     0

/* usart receiver enable */
#define USART_ASYNCHRONOUS_RX_ENABLE      1
#define USART_ASYNCHRONOUS_RX_DISABLE     0
/* usart transimatter enterrupt enable */
#define USART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE      1
#define USART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE     0
/* usart transimatter 9_bits enable */
#define USART_ASYNCHRONOUS_9BITS_RX_ENABLE      1
#define USART_ASYNCHRONOUS_9BITS_RX_DISABLE     0

/* usart framing error */
#define USART_FRAMING_DETECTED    1
#define USART_FRAMING_CLEAR       0
/* usart overrun error */
#define USART_OVERRUN_DETECTED    1
#define USART_OVERRUN_CLEAR       0

/*section : macro declaration functions  */

/*section : data type declarations  */
typedef enum {
    BAUDRATE_ASY_8BIT_LOW_SPEED,
    BAUDRATE_ASY_8BIT_HIGH_SPEED,
    BAUDRATE_ASY_16BIT_LOW_SPEED,
    BAUDRATE_ASY_16BIT_HIGH_SPEED,
    BAUDRATE_SY_8BIT,
    BAUDRATE_SY_16BIT,
}buadrate_gen_t;

typedef struct {
    uint8 usaret_tx_reserved        :5;
    uint8 usart_tx_enable           :1;
    uint8 usart_tx_interrupt_enable :1;
    uint8 usart_tx_9bits_enable     :1;   
    INTERRUPT_PRIORITY_t INTERRUPT_PRIORITY_TX;
}usart_tx_t;
typedef struct {
    uint8 usaret_rx_reserved        :5;
    uint8 usart_rx_enable           :1;
    uint8 usart_rx_interrupt_enable :1;
    uint8 usart_rx_9bits_enable     :1;  
    INTERRUPT_PRIORITY_t INTERRUPT_PRIORITY_RX;
}usart_rx_t;

typedef union {
    struct{
        uint8 usaret_reserved        :6;
        uint8 usart_ferr             :1;
        uint8 usart_oerr             :1;      
    };
}ueasrt_error_t;

typedef struct {
    uint32 baudrate ;
    buadrate_gen_t buadrate_gen;
    usart_tx_t usart_tx;
    usart_rx_t usart_rx;
    ueasrt_error_t ueasrt_error;
    void (* USART_TX_INTERRUPT_HANDLER)(void);
    void (* USART_RX_INTERRUPT_HANDLER)(void);
    void (* USART_FRAMING_ERROR_INTERRUPT_HANDLER)(void);
    void (* USART_OVERRUN_ERROR_INTERRUPT_HANDLER)(void);
}usart_t;
/*section : functions declarations  */
Std_ReturnType usart_ASYNC_init (const usart_t *usart);
Std_ReturnType usart_ASYNC_deinit (const usart_t *usart);
Std_ReturnType usart_ASYNC_read_byte_blocking (uint8 *data);
Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(uint8 *_data);
Std_ReturnType usart_ASYNC_write_byte_blocking (uint8 data);
Std_ReturnType usart_ASYNC_write_string_blocking (uint8 *data , uint16 str_lenght);
#endif	/* HAL_USART_H */

// callback function for rx should contains function @usart_ASYNC_read_byte_blocking

/*
 
 void interrupt_usart_rx(void){
    volatile uint8 data 
    usart_ASYNC_read_byte_blocking(&data);
    any code i wanne 
}
 */


/*
 
 void interrupt_usart_tx(void);
void interrupt_usart_rx(void);

usart_t usart_1 ={
   .baudrate= 2404,.buadrate_gen=BAUDRATE_ASY_8BIT_LOW_SPEED ,.usart_tx.usart_tx_enable=USART_ASYNCHRONOUS_TX_ENABLE,
   .usart_tx.usart_tx_interrupt_enable=USART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE,
   .usart_tx.usart_tx_9bits_enable=USART_ASYNCHRONOUS_9BITS_TX_DISABLE,.usart_rx.usart_rx_enable=USART_ASYNCHRONOUS_RX_ENABLE,
   .usart_rx.usart_rx_interrupt_enable=USART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE,
   .usart_rx.usart_rx_9bits_enable=USART_ASYNCHRONOUS_9BITS_RX_DISABLE,.USART_RX_INTERRUPT_HANDLER=interrupt_usart_rx
};
 
 
 void interrupt_usart_tx(void){
    
}

void interrupt_usart_rx(void){
    volatile uint8 ret_data = 0;
    ret = usart_ASYNC_read_byte_blocking (&data);
        if(data == 'c'){
            ret = led_turn_on(&led_1);
            ret = usart_ASYNC_write_byte_blocking('w');
        }
}
 

 
 */