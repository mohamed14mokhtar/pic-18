/* 
 * File:   mcal_interrupt_manager.c
 * Author: mokhtar
 *
 * Created on January 24, 2024, 9:00 PM
 */

#include"mcal_interrupt_manager.h"
#include"mcal_interrupt_config.h"

static uint8 flag1 = 1,flag2 = 1,flag3 = 1,flag4 = 1;

#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
    void __interrupt() interrupt_manger_high(void){
        if((INTERRUPT_FATURE_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.INT0IF)){
            INT0_ISR();
        }
        else{/* nothing */}
        //
        if((INTERRUPT_FATURE_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_FATURE_OCCURE == INTCON3bits.INT2IF)){
            INT2_ISR();
        }
        else{/* nothing */}
           /********************************** ADC FUNCTIONS ************************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE1bits.ADIE) && (INTERRUPT_FATURE_OCCURE == PIR1bits.ADIF)){
            ADC_handeler_funvtion();
        }
        else{/* nothing */}
        /********************************** RBX FUNCTIONS ************************************************/
        
        /********************************** TIMER1 FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_FATURE_OCCURE == PIR1bits.TMR1IF)){
            TIMER1_ISR();
        }
        else{/* nothing */}
        /********************************** TIMER2 FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_FATURE_OCCURE == PIR1bits.TMR2IF)){
            TIMER2_ISR();
        }
        else{/* nothing */}
          /********************************** TIMER3 FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_FATURE_OCCURE == PIR2bits.TMR3IF)){
            TIMER3_ISR();
        }
        else{/* nothing */}
          /********************************** USART TX FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE1bits.TXIE) && (INTERRUPT_FATURE_OCCURE == IPR1bits.TXIP)){
            USART_TX_ISR();
        }
        else{/* nothing */}
        /********************************** USART RX FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE1bits.RCIE) && (INTERRUPT_FATURE_OCCURE == IPR1bits.RCIP)){
            USART_RX_ISR();
        }
        else{/* nothing */}
    }
    
    void __interrupt(low_priority) interrupt_manger_low(void){
        if((INTERRUPT_FATURE_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_FATURE_OCCURE == INTCON3bits.INT1IF)){
            INT1_ISR();
        }
        else{/* nothing */}
        /********************************** RBX FUNCTIONS ************************************************/
        if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB4 == GPIO_HIGH) && (flag1 == 1)){
            flag1 = 0;
            RB4_ISR(0);
        }
        else{/* nothing */}
                if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB4 == GPIO_LOW) && (flag1 == 0)){
            flag1 = 1;
            RB4_ISR(1);
        }
        else{/* nothing */}
        //
        if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB6 == GPIO_HIGH) && (1 == flag3)){
            flag3 = 0;
            RB6_ISR(0);
        }
        else{/* nothing */}
        if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB6 == GPIO_LOW) && (0 == flag3)){
            flag3 = 1;
            RB6_ISR(1);
        }
        else{/* nothing */}
        //
         if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB7 == GPIO_HIGH) && (1 == flag4)){
            flag4 = 0;
            RB7_ISR(0);
        }
        else{/* nothing */}
        if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB7 == GPIO_LOW) && (0 == flag4)){
            flag4 = 1;
            RB7_ISR(1);
        }
        else{/* nothing */}
        //
        if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB5 == GPIO_HIGH) && (flag2 == 1)){
            flag2 = 0;
            RB5_ISR(0);
        }
        else{/* nothing */}
        if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB5 == GPIO_LOW)  && (flag2 == 0)){
            flag2 =1;
            RB5_ISR(1);
        }
        else{/* nothing */}
        /********************************** TIMER0 FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.TMR0IF)){
            TIMER0_ISR();
        }
        else{/* nothing */}
        /********************************** CCP1 FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_FATURE_OCCURE == PIR1bits.CCP1IF)){
            CCP1_ISR();
        }
        else{/* nothing */}
        /********************************** CCP2 FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_FATURE_OCCURE == PIR2bits.CCP2IF)){
            CCP2_ISR();
        }
        else{/* nothing */}
        /********************************** USART TX FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE1bits.TXIE) && (INTERRUPT_FATURE_OCCURE == PIR1bits.TXIF)){
            USART_TX_ISR();
        }
        else{/* nothing */}
        /********************************** USART RX FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE1bits.RCIE) && (INTERRUPT_FATURE_OCCURE == PIR1bits.RCIF)){
            USART_RX_ISR();
        }
        else{/* nothing */}
  
    }
#else
    void __interrupt() interrupt_manager(void){
        /************************************* INTX FUNCTIONS **********************************************/
        if((INTERRUPT_FATURE_ENABLE == INTCONbits.INT0IF) && (INTERRUPT_FATURE_OCCURE == INTCONbits.INT0IF)){
            INT0_ISR();
        }
        else{/* nothing */}
        if((INTERRUPT_FATURE_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_FATURE_OCCURE == INTCON3bits.INT1IF)){
            INT1_ISR();
        }
        else{/* nothing */}
        if((INTERRUPT_FATURE_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_FATURE_OCCURE == INTCON3bits.INT2IF)){
            INT2_ISR();
        }
        else{/* nothing */}
        /********************************** RBX FUNCTIONS ************************************************/
        if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB4 == GPIO_HIGH) && (flag1 == 1)){
            flag1 = 0;
            RB4_ISR(0);
        }
        else{/* nothing */}
        if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB4 == GPIO_LOW) && (flag1 == 0)){
            flag1 = 1;
            RB4_ISR(1);
        }
        else{/* nothing */}
         if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB5 == GPIO_HIGH) && (flag2 == 1)){
            flag2 = 0;
            RB5_ISR(0);
        }
        else{/* nothing */}
        if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB5 == GPIO_LOW)  && (flag2 == 0)){
            flag2 =1;
            RB5_ISR(1);
        }
        else{/* nothing */}
         if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB6 == GPIO_HIGH) && (1 == flag3)){
            flag3 = 0;
            RB6_ISR(0);
        }
        else{/* nothing */}
        if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB6 == GPIO_LOW) && (0 == flag3)){
            flag3 = 1;
            RB6_ISR(1);
        }
        else{/* nothing */}
         if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB7 == GPIO_HIGH) && (1 == flag4)){
            flag4 = 0;
            RB7_ISR(0);
        }
        else{/* nothing */}
        if((INTERRUPT_FATURE_ENABLE == INTCONbits.RBIE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.RBIF) 
            && (PORTBbits.RB7 == GPIO_LOW) && (0 == flag4)){
            flag4 = 1;
            RB7_ISR(1);
        }
        else{/* nothing */}
        /********************************** ADC FUNCTIONS ************************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE1bits.ADIE) && (INTERRUPT_FATURE_OCCURE == PIR1bits.ADIF)){
            ADC_handeler_funvtion();
        }
        else{/* nothing */}
        /********************************** TIMER0 FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_FATURE_OCCURE == INTCONbits.TMR0IF)){
            TIMER0_ISR();
        }
        else{/* nothing */}
        /********************************** TIMER1 FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_FATURE_OCCURE == PIR1bits.TMR1IF)){
            TIMER1_ISR();
        }
        else{/* nothing */}
        /********************************** TIMER2 FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_FATURE_OCCURE == PIR1bits.TMR2IF)){
            TIMER2_ISR();
        }
        else{/* nothing */}
        /********************************** TIMER3 FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_FATURE_OCCURE == PIR2bits.TMR3IF)){
            TIMER3_ISR();
        }
        else{/* nothing */}
        /********************************** CCP1 FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_FATURE_OCCURE == PIR1bits.CCP1IF)){
            CCP1_ISR();
        }
        else{/* nothing */}
        /********************************** CCP2 FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_FATURE_OCCURE == PIR2bits.CCP2IF)){
            CCP2_ISR();
        }
        else{/* nothing */}
        /********************************** USART TX FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE1bits.TXIE) && (INTERRUPT_FATURE_OCCURE == PIR1bits.TXIF)){
            USART_TX_ISR();
        }
        else{/* nothing */}
        /********************************** USART RX FUNCTIONS *********************************************/
        if((INTERRUPT_FATURE_ENABLE == PIE1bits.RCIE) && (INTERRUPT_FATURE_OCCURE == PIR1bits.RCIF)){
            USART_RX_ISR();
        }
        else{/* nothing */}
        
    }
       
#endif