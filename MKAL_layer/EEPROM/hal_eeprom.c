/* 
 * File:   hal_eeprom.C
 * Author: mokhtar
 *
 * Created on January 28, 2024, 10:39 AM
 */

#include <pic18f4620.h>

#include"hal_eeprom.h"

Std_ReturnType DATE_EEPROM_WRITE_BYTE (uint16 badd ,uint8 Bdata){
    Std_ReturnType ret = E_OK;
    uint8 interrupt_status = 0;
    /* reed the interrupt status (enable or disable) */
    #if INTERRUPT_PRIORITY_LEVEL_ENABLE  ==  INTERRUPT_FATURE_ENABLE
        interrupt_status = INTCONbits.GIEH ;
    #else
        interrupt_status = INTCONbits.GIE ;
    #endif
    /* update the address register */
    EEADRH = ((badd >> 8) & 0x03);
    EEADR  = ((badd >> 0) & 0xFF);
    /* update the date register */
     EEDATA = Bdata ; 
    /* select address date EEPROM memory */
    EECON1bits.EEPGD = ACCESS_EEPROM_MEMORY;
    /* update the date register */
    EECON1bits.CFGS  = Access_Flash_program_or_data_EEPROM_memory;
    /* allow write cycle to flash/EEPROM */
    EECON1bits.WREN = ALLOW_WRITEN_CYCLE_FLASH_EEPROM;
    /* disable all interrupt "general interrupt" */
    #if INTERRUPT_PRIORITY_LEVEL_ENABLE     == INTERRUPT_FATURE_ENABLE
        INTERRUPT_globalinterrupthighdisable() ;
    #else
        INTERRUPT_globalinterruptdisable() ;
    #endif
    /* write the require sequence (0x55 >> 0xAA) */
        EECON2 = 0x55;
        EECON2 = 0xAA;
    /* initialize a date EEPROM eras / write cycle */
    EECON1bits.WR = INITIALISE_DATA_EEPROM_ESEAR;
    /* wait for write to complete (while) */
    while (EECON1bits.WR);
    /* inhibits write cycle */
    EECON1bits.WREN = INHIBT_WRITEN_CYCLE_FLASH_EEPROM;
    /* restored the interrupt status */
     #if INTERRUPT_PRIORITY_LEVEL_ENABLE    ==  INTERRUPT_FATURE_ENABLE
        INTCONbits.GIEH = interrupt_status ;
    #else
        INTCONbits.GIE =  interrupt_status;
    #endif
    return ret ;
}

Std_ReturnType DATE_EEPROM_REED_BYTE (uint16 badd ,uint8 *Bdata){
    Std_ReturnType ret = E_not_ok;
    if (NULL == Bdata){
        ret =E_not_ok;
    }
    else
    {
        /* update the address register */
        EEADRH = ((badd >> 8) & 0x03);
        EEADR  = ((badd >> 0) & 0xFF);
        /* update the date register */
        EECON1bits.EEPGD = ACCESS_EEPROM_MEMORY;
        EECON1bits.CFGS  = Access_Flash_program_or_data_EEPROM_memory;
        /* initialize a date EEPROM eras / read cycle */
        EECON1bits.RD = INITIALIZE_DATA_EEPROM_READ;
        NOP();
        NOP();
        /* return data  */
        *Bdata =EEDATA;
    }
    return ret ;
}