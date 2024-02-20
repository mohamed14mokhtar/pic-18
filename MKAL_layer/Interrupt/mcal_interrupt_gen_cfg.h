/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: mokhtar
 *
 * Created on January 25, 2024, 6:58 AM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

/*section : includes */
#include"../gpio/pro_gpio.h"
/*section : macro declarations  */
#define INTERRUPT_FATURE_ENABLE     1
#define INTERRUPT_FATURE_DISABLE    0
#define INTERRUPT_FATURE_OCCURE     1
#define INTERRUPT_FATURE_DISOCCURE  0

//#define INTERRUPT_PRIORITY_LEVEL_ENABLE                 INTERRUPT_FATURE_ENABLE

#define EXTERNAL_INTERRUPT_INTx_ENABLE                  INTERRUPT_FATURE_ENABLE
#define EXTERNAL_INTERRUPT_interrupt_on_chang_ENABLE    INTERRUPT_FATURE_ENABLE

#define ADC_INTERRUPT_feature_ENABLE                    INTERRUPT_FATURE_ENABLE

#define TIMER0_INTERRUPT_feature_ENABLE                 INTERRUPT_FATURE_ENABLE
#define TIMER1_INTERRUPT_feature_ENABLE                 INTERRUPT_FATURE_ENABLE
#define TIMER2_INTERRUPT_feature_ENABLE                 INTERRUPT_FATURE_ENABLE
#define TIMER3_INTERRUPT_feature_ENABLE                 INTERRUPT_FATURE_ENABLE

#define CCP1_INTERRUPT_feature_ENABLE                   INTERRUPT_FATURE_ENABLE
#define CCP2_INTERRUPT_feature_ENABLE                   INTERRUPT_FATURE_ENABLE

#define USEAR_TX_INTERRUPT_feature_ENABLE               INTERRUPT_FATURE_ENABLE
#define USEAR_RX_INTERRUPT_feature_ENABLE               INTERRUPT_FATURE_ENABLE
/*section : macro declaration functions  */


/*section : data type declarations  */
typedef enum {
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HUGH_PRIORITY
}INTERRUPT_PRIORITY_t;
/*section : functions declarations  */


#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

