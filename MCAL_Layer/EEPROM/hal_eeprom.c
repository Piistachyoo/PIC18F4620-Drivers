
#include "hal_eeprom.h"


Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData){
    Std_ReturnType ret = E_NOT_OK;
    if(bAdd <= 0x3FF){
        /* Read the interrupt status (Enable/Disabled) */
        uint8 GlobalInterruptStatus = INTCONbits.GIE;
        /* Update the address registers */
        EEADRH = (uint8)((bAdd>>8) & 0x03);
        EEADR = (uint8)(bAdd & 0xFF);
        /* Update the data register */
        EEDATA = bData;
        /* Select access data EEPROM memory */
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACESS_FLASH_EEPROM_MEMORY;
        /* Allows write cycles to flash program/data EEPROM*/
        EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
        /* Disable all interrupts "General Interrupt */
        //INTERRUPT_GlobalInterruptDisable();
        /* Write the required sequence : 0x55 -> 0xAA */
        EECON2 = 0x55;
        EECON2 = 0xAA;
        /* Initiates a data EEPROM erase/write cycle */
        EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
        /* Wait for write to complete */
        while(EECON1bits.WR);
        /* Inhibits write cycles to flash program/data EEPROM */
        EECON1bits.WREN = INHIBIT_WRITE_CYCLES_FLASH_EEPROM;
        /* Restore the interrupt status (Enable/Disable) */
        INTCONbits.GIE = GlobalInterruptStatus;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData){
    Std_ReturnType ret = E_NOT_OK;
    if((bAdd <= 0x3FF) && (bData != NULL)){
        /* Update the address registers */
        EEADRH = (uint8)((bAdd>>8) & 0x03);
        EEADR = (uint8)(bAdd & 0xFF);
        /* Select access data EEPROM memory */
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACESS_FLASH_EEPROM_MEMORY;
        /* Initiates a data EEPROM read cycle */
        EECON1bits.RD = INITIATE_DATA_EEPROM_WRITE_ERASE;
        NOP();
        NOP();
        /* Return data */
        *bData = EEDATA;
        
        ret = E_OK;
    }
    return ret;
}
