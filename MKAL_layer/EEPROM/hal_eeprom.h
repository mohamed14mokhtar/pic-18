/* 
 * File:   hal_eeprom.h
 * Author: mokhtar
 *
 * Created on January 28, 2024, 10:39 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/*section : includes */
#include"../pic18_chip_select.h"
#include"../mkal_std_types.h"
#include"../Interrupt/mcal_internal_interrupt.h"
/*section : macro declarations  */
#define ACCESS_FLASH_MEMORY                         1
#define ACCESS_EEPROM_MEMORY                        0

#define ACCESS_Configuration_registers              1
#define Access_Flash_program_or_data_EEPROM_memory  0

#define ALLOW_WRITEN_CYCLE_FLASH_EEPROM             1
#define INHIBT_WRITEN_CYCLE_FLASH_EEPROM            0

#define INITIALISE_DATA_EEPROM_ESEAR                1
#define DATA_EEPROM_WRITEN_ESEAR_COMPLETED          0

#define INITIALIZE_DATA_EEPROM_READ                 1
/*section : macro declaration functions  */

/*section : data type declarations  */

/*section : software interrupt  */
Std_ReturnType DATE_EEPROM_WRITE_BYTE (uint16 badd ,uint8 Bdata);
Std_ReturnType DATE_EEPROM_REED_BYTE (uint16 badd ,uint8 *Bdata);

#endif	/* HAL_EEPROM_H */

