/* 
 * File:   mcal_interrupt_config.h
 * Author: mokhtar
 *
 * Created on January 24, 2024, 8:58 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/*section : includes */
#include"../pic18_chip_select.h"
#include"../mkal_std_types.h"
#include"mcal_interrupt_gen_cfg.h"

/*section : macro declaration functions  */

#define INTERRUPT_ENABLE            1
#define INTERRUPT_DISABLE           0
#define INTERRUPT_OCCURE            1
#define INTERRUPT_NOT_OCCURE        0
#define INTERRUPT_PRIORITY_ENABLE   1
#define INTERRUPT_PRIORITY_DISABLE  0

/*section : data type declarations  */

#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FATURE_ENABLE
/* this function will enable all high priority global interrupt */
#define INTERRUPT_globalinterrupthighenable() (INTCONbits.GIEH =1)
/* this function will disable all high priority global interrupt */
#define INTERRUPT_globalinterrupthighdisable() (INTCONbits.GIEH =0)
/* this function will enable all low priority global interrupt */
#define INTERRUPT_globalinterruptlowenable() (INTCONbits.GIEL =1)
/* this function will disable all low priority global interrupt */
#define INTERRUPT_globalinterruptlowdisable() (INTCONbits.GIEL =0)
/* this function will enable priority levels on interrupt */
#define INTERRUPT_prioritylevelenable() (RCONbits.IPEN = 1)
/* his function will disable priority levels on interrupt */
#define INTERRUPT_prioritylevelDISable() (RCONbits.IPEN = 0)

#else 
/* this function will enable all global interrupt */
#define INTERRUPT_globalinterruptenable() (INTCONbits.GIE =1)
/* this function will disable all global interrupt */
#define INTERRUPT_globalinterruptdisable() (INTCONbits.GIE =0)
/* this function will enable peripheral interrupt */
#define INTERRUPT_peripheralinterruptenable() (INTCONbits.PEIE =1)
/* this function will disable peripheral interrupt */
#define INTERRUPT_peripheralinterruptdisable() (INTCONbits.PEIE =0)
#endif
/*section : functions declarations  */


#endif	/* MCAL_INTERRUPT_CONFIG_H */

