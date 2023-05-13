/* 
 * File:   hal_eeprom.h
 * Author: omarm
 *
 * Created on May 3, 2023, 1:36 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* Section : Includes */
#include <xc.h> 
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declarations */
#define ACCESS_FLASH_PROGRAM_MEMORY     1
#define ACCESS_EEPROM_PROGRAM_MEMORY    0

#define ACCESS_CONFIG_REGISTERS         1
#define ACESS_FLASH_EEPROM_MEMORY       0

#define ALLOW_WRITE_CYCLES_FLASH_EEPROM     1
#define INHIBIT_WRITE_CYCLES_FLASH_EEPROM   0

#define INITIATE_DATA_EEPROM_WRITE_ERASE    1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED   0

#define INITIATE_DATA_EEPROM_READ       1
#define DATA_EEPROM_READ_COMPLETED      0
/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

/* Section : Function Declarations */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData);
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData);

#endif	/* HAL_EEPROM_H */

