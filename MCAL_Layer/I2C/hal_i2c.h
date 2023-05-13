/* 
 * File:   hal_i2c.h
 * Author: omarm
 *
 * Created on May 1, 2023, 12:54 PM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

/* Section : Includes */
#include <xc.h>
#include "../device_config.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "../mcal_std_types.h"

/* Section : Macro Declarations */
#define I2C_SLEW_RATE_ENABLE    0
#define I2C_SLEW_RATE_DISABLE   1

#define I2C_SMBus_ENABLE        1
#define I2C_SMBus_DISABLE       0

#define I2C_LAST_BYTE_DATA      1
#define I2C_LAST_BYTE_ADDRESS   0

#define START_BIT_DETECTED      1
#define START_BIT_NOT_DETECTED  0

#define STOP_BIT_DETECTED      1
#define STOP_BIT_NOT_DETECTED  0

#define I2C_SLAVE_MODE_7BIT_ADDRESS         0x06U
#define I2C_SLAVE_MODE_10BIT_ADDRESS        0x07U
#define I2C_SLAVE_MODE_7BIT_SS_INT_ENABLE   0x0EU
#define I2C_SLAVE_MODE_10BIT_SS_INT_ENABLE  0x0FU
#define I2C_MASTER_MODE_DEFINE_CLOCK        0x08U
#define I2C_MASTER_MODE_FIRMWARE_CONTROLLER 0x0BU

#define I2C_GENERAL_CALL_ENABLE         1
#define I2C_GENERAL_CALL_DISABLE        0

#define I2C_MASTER_RECEIVE_ENABLE       1
#define I2C_MASTER_RECEIVE_DISABLE      0

#define I2C_MSSP_MASTER_MODE            1
#define I2C_MSSP_SLAVE_MODE             0

#define I2C_ACK_REC_FROM_SLAVE          0
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE 1

#define I2C_MASTER_SEND_ACK             0
#define I2C_MASTER_SEND_NACK            1

/* Section : Macro Functions Declarations */
#define I2C_SLEW_RATE_DISABLE_CFG()         (SSPSTATbits.SMP = 1)
#define I2C_SLEW_RATE_ENABLE_CFG()          (SSPSTATbits.SMP = 0)
#define I2C_SMBus_DISABLE_CFG()             (SSPSTATbits.CKE = 0)
#define I2C_SMBus_ENABLE_CFG()              (SSPSTATbits.CKE = 1)
#define I2C_GENERAL_CALL_DISABLE_CFG()      (SSPCON2bits.GCEN = 0)
#define I2C_GENERAL_CALL_ENABLE_CFG()       (SSPCON2bits.GCEN = 1)
#define I2C_MASTER_RECEIVE_DISABLE_CFG()    (SSPCON2bits.RCEN = 0)
#define I2C_MASTER_RECEIVE_ENABLE_CFG()     (SSPCON2bits.RCEN = 1)
#define MSSP_MODULE_ENABLE_CFG()            (SSPCON1bits.SSPEN = 1)
#define MSSP_MODULE_DISABLE_CFG()           (SSPCON1bits.SSPEN = 0)

/* Section : Data Type Declarations */
typedef struct{
    uint8 i2c_mode_cfg;             // Master synchronous serial port mode select
    uint8 i2c_slave_address;        // I2C Slave Address
    uint8 i2c_mode              :1; // I2C Master/Slave mode
    uint8 i2c_slew_rate         :1; // Slew rate enable/disable
    uint8 i2c_SMBus_control     :1; // SMBus enable/disable
    uint8 i2c_general_call      :1; // General call enable/disable
    uint8 i2c_master_rec_mode   :1; // Master receive mode enable/disable
    uint8 i2c_reserved          :3; 
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg mssp_i2c_priority;
    interrupt_priority_cfg mssp_i2c_bc_priority;
#endif
}I2C_cfg_t;

typedef struct{
    uint32 i2c_clock; // Master clock frequency
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*I2C_Report_Write_Collision)(void); // Write collision indicator
    void (*I2C_DefaultInterruptHandler)(void); // Default interrupt handler
#endif
    void (*I2C_Report_Receive_Overflow)(void); // Receive overflow indicator
    I2C_cfg_t i2c_cfg;  // I2C Configurations 
}MSSP_I2C_t;

/* Section : Function Declarations */
Std_ReturnType MSSP_I2C_Init(const MSSP_I2C_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Start(const MSSP_I2C_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const MSSP_I2C_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Stop(const MSSP_I2C_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Write_Blocking(const MSSP_I2C_t *i2c_obj, uint8 i2c_data, uint8 *_ack);
Std_ReturnType MSSP_I2C_Master_Read_Blocking(const MSSP_I2C_t *i2c_obj, uint8 ack, uint8 *i2c_data);

#endif	/* HAL_I2C_H */

