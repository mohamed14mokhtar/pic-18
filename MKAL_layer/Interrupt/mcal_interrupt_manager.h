/* 
 * File:   mcal_interrupt_manager.h
 * Author: mokhtar
 *
 * Created on January 24, 2024, 9:00 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/*section : includes */
#include"mcal_interrupt_config.h"

/*section : macro declarations  */


/*section : macro declaration functions  */


/*section : data type declarations  */

/*section : functions declarations  */
void INT0_ISR (void);
void INT1_ISR (void);
void INT2_ISR (void);
void RB4_ISR(uint8 value);
void RB5_ISR(uint8 value);
void RB6_ISR(uint8 value);
void RB7_ISR(uint8 value);
void ADC_handeler_funvtion (void);
void TIMER0_ISR (void);
void TIMER1_ISR (void);
void TIMER2_ISR (void);
void TIMER3_ISR (void);
void CCP1_ISR (void);
void CCP2_ISR (void);
void USART_TX_ISR(void);
void USART_RX_ISR(void);
#endif	/* MCAL_INTERRUPT_MANAGER_H */

