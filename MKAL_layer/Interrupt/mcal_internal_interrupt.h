/* 
 * File:   mcal_internal_interrupt.h
 * Author: mokhtar
 *
 * Created on January 24, 2024, 8:59 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/*section : includes */
#include"mcal_interrupt_config.h"
/*section : macro declarations  */


/*section : macro declaration functions  */
/************************* ADC *******************************/
#if ADC_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
/* routines to clear or set enable of ADC 0 */
#define ADC_INTERRUPT_ENABLE()      (PIE1bits.ADIE    = 1)
#define ADC_INTERRUPT_disABLE()     (PIE1bits.ADIE    = 0)
/* routines to clear flag of ADC */
#define ADC_INTERRUPT_FLAGE_CLEAR() (PIR1bits.ADIF    = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
/* set high or low priority of ADC */
#define ADC_INTERRUPT_high_priority_set() (IPR1bits.ADIP = 1)
#define ADC_INTERRUPT_low_priority_set()  (IPR1bits.ADIP = 0)
#endif

#endif
/************************* timer0 *******************************/
#if TIMER0_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
/* routines to clear or set enable of TIMER0 */
#define TIMER0_INTERRUPT_ENABLE()      (INTCONbits.TMR0IE  = 1)
#define TIMER0_INTERRUPT_disABLE()     (INTCONbits.TMR0IE  = 0)
/* routines to clear flag of TIMER0 */
#define TIMER0_INTERRUPT_FLAGE_CLEAR() (INTCONbits.TMR0IF  = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
/* set high or low priority of TIMER0 */
#define TIMER0_INTERRUPT_high_priority_set() (INTCON2bits.TMR0IP = 1)
#define TIMER0_INTERRUPT_low_priority_set()  (INTCON2bits.TMR0IP = 0)
#endif

#endif
/************************* timer1 *******************************/

#if TIMER1_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
/* routines to clear or set enable of TIMER1 */
#define TIMER1_INTERRUPT_ENABLE()      (PIE1bits.TMR1IE  = 1)
#define TIMER1_INTERRUPT_disABLE()     (PIE1bits.TMR1IE  = 0)
/* routines to clear flag of TIMER1 */
#define TIMER1_INTERRUPT_FLAGE_CLEAR() (PIR1bits.TMR1IF  = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
/* set high or low priority of TIMER1 */
#define TIMER1_INTERRUPT_high_priority_set() (IPR1bits.TMR1IP = 1)
#define TIMER1_INTERRUPT_low_priority_set()  (IPR1bits.TMR1IP = 0)
#endif

#endif
/************************* timer2 *******************************/

#if TIMER2_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
/* routines to clear or set enable of TIMER2 */
#define TIMER2_INTERRUPT_ENABLE()      (PIE1bits.TMR2IE  = 1)
#define TIMER2_INTERRUPT_disABLE()     (PIE1bits.TMR2IE  = 0)
/* routines to clear flag of TIMER2 */
#define TIMER2_INTERRUPT_FLAGE_CLEAR() (PIR1bits.TMR2IF = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
/* set high or low priority of TIMER2 */
#define TIMER2_INTERRUPT_high_priority_set() (IPR1bits.TMR2IP = 1)
#define TIMER2_INTERRUPT_low_priority_set()  (IPR1bits.TMR2IP = 0)
#endif

#endif
/************************* timer3 *******************************/

#if TIMER3_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
/* routines to clear or set enable of TIMER3 */
#define TIMER3_INTERRUPT_ENABLE()      (PIE2bits.TMR3IE  = 1)
#define TIMER3_INTERRUPT_disABLE()     (PIE2bits.TMR3IE  = 0)
/* routines to clear flag of TIMER3 */
#define TIMER3_INTERRUPT_FLAGE_CLEAR() (PIR2bits.TMR3IF  = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
/* set high or low priority of TIMER3 */
#define TIMER3_INTERRUPT_high_priority_set() (IPR2bits.TMR3IP = 1)
#define TIMER3_INTERRUPT_low_priority_set()  (IPR2bits.TMR3IP = 0)
#endif

#endif
/************************* CCP1 *******************************/

#if CCP1_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
/* routines to clear or set enable of CCP1 */
#define CCP1_INTERRUPT_ENABLE()      (PIE1bits.CCP1IE  = 1)
#define CCP1_INTERRUPT_disABLE()     (PIE1bits.CCP1IE  = 0)
/* routines to clear flag of CCP1 */
#define CCP1_INTERRUPT_FLAGE_CLEAR() (PIR1bits.CCP1IF  = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
/* set high or low priority of CCP1 */
#define CCP1_INTERRUPT_high_priority_set() (IPR1bits.CCP1IP = 1)
#define CCP1_INTERRUPT_low_priority_set()  (IPR1bits.CCP1IP = 0)
#endif

#endif

/************************* CCP2 *******************************/

#if CCP2_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
/* routines to clear or set enable of CCP2 */
#define CCP2_INTERRUPT_ENABLE()      (PIE2bits.CCP2IE  = 1)
#define CCP2_INTERRUPT_disABLE()     (PIE2bits.CCP2IE  = 0)
/* routines to clear flag of CCP2 */
#define CCP2_INTERRUPT_FLAGE_CLEAR() (PIR2bits.CCP2IF  = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
/* set high or low priority of CCP2 */
#define CCP2_INTERRUPT_high_priority_set() (IPR2bits.CCP2IP = 1)
#define CCP2_INTERRUPT_low_priority_set()  (IPR2bits.CCP2IP = 0)
#endif
#endif
/************************* UEART TX *******************************/

#if USEAR_TX_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
/* routines to clear or set enable of UEART TX */
#define usart_tx_INTERRUPT_ENABLE()      (PIE1bits.TXIE  = 1)
#define usart_tx_INTERRUPT_disABLE()     (PIE1bits.TXIE  = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
/* set high or low priority of UEART TX */
#define usart_tx_INTERRUPT_high_priority_set() (IPR1bits.TXIP = 1)
#define usart_tx_INTERRUPT_low_priority_set()  (IPR1bits.TXIP = 0)
#endif
#endif
/************************* UEART RX *******************************/

#if USEAR_RX_INTERRUPT_feature_ENABLE == INTERRUPT_FATURE_ENABLE
/* routines to clear or set enable of UEART RX */
#define usart_rx_INTERRUPT_ENABLE()      (PIE1bits.RCIE  = 1)
#define usart_rx_INTERRUPT_disABLE()     (PIE1bits.RCIE  = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
/* set high or low priority of UEART RX */
#define usart_rx_INTERRUPT_high_priority_set() (IPR1bits.RCIP = 1)
#define usart_rx_INTERRUPT_low_priority_set()  (IPR1bits.RCIP = 0)
#endif
#endif
/*section : data type declarations  */

/*section : functions declarations  */


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

