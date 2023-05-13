/* 
 * File:   hal_i2c.c
 * Author: Omar Yamany
 *
 * Created on May 1, 2023, 12:54 PM
 */

#include "hal_i2c.h"

void (*I2C_Report_Write_Collision) (void); // Write collision indicator
void (*I2C_Report_Receive_Overflow)(void); // Receive overflow indicator
void (*I2C_DefaultInterruptHandler)(void); // Default interrupt handler

static inline void I2C_Master_Mode_Clock_Configuration(const MSSP_I2C_t *i2c_obj);
static inline void I2C_Slave_Mode_Configuration(const MSSP_I2C_t *i2c_obj);
static inline void MSSP_I2C_MODE_GPIO_CFG();
static inline void MSSP_I2C_Interrupt_Configurations(const MSSP_I2C_t *i2c_obj);

Std_ReturnType MSSP_I2C_Init(const MSSP_I2C_t *i2c_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != i2c_obj){
        /* Disable MSSP I2C Module */
        MSSP_MODULE_DISABLE_CFG();
        /* MSSP I2C Select Mode */
        if(i2c_obj->i2c_cfg.i2c_mode == I2C_MSSP_MASTER_MODE){ /* MSSP I2C Master mode configurations */
            /* I2C Master Mode Clock Configuration */
            I2C_Master_Mode_Clock_Configuration(i2c_obj);
        }
        
        else if(i2c_obj->i2c_cfg.i2c_mode == I2C_MSSP_SLAVE_MODE){ /* MSSP I2C Slave mode configurations */
            /* I2C Slave Mode General Call Configuration */
            if(i2c_obj->i2c_cfg.i2c_general_call == I2C_GENERAL_CALL_ENABLE){
                I2C_GENERAL_CALL_ENABLE_CFG();
            }
            else if(i2c_obj->i2c_cfg.i2c_general_call == I2C_GENERAL_CALL_DISABLE){
                I2C_GENERAL_CALL_DISABLE_CFG();
            }
            else { /* Do Nothing */ }
            /* Clear the Write Collision Detect */
            SSPCON1bits.WCOL = 0;
            /* Clear the Receive Overflow Indicator */
            SSPCON1bits.SSPOV = 0;
            /* Release the Clock if clock is stretched */
            SSPCON1bits.CKP = 1;
            /* Assign the I2C Slave Address */
            SSPADD = i2c_obj->i2c_cfg.i2c_slave_address;
            /* Slave mode configuration */
            I2C_Slave_Mode_Configuration(i2c_obj);
        }
        else{ /* Do Nothing */ }
        
        /* I2C GPIO Configuration */
        MSSP_I2C_MODE_GPIO_CFG();
        
        /* MSSP I2C Slew Rate Control */
        if(i2c_obj->i2c_cfg.i2c_slew_rate == I2C_SLEW_RATE_ENABLE){
            I2C_SLEW_RATE_ENABLE_CFG();
        }
        else if(i2c_obj->i2c_cfg.i2c_slew_rate == I2C_SLEW_RATE_DISABLE){
            I2C_SLEW_RATE_DISABLE_CFG();
        }
        else{ /* Do Nothing */ }
        /* MSSP I2C SMBus Control */
        if(i2c_obj->i2c_cfg.i2c_SMBus_control == I2C_SMBus_ENABLE){
            I2C_SMBus_ENABLE_CFG();
        }
        else if(i2c_obj->i2c_cfg.i2c_SMBus_control == I2C_SMBus_DISABLE){
            I2C_SMBus_DISABLE_CFG();
        }
        else{ /* Do Nothing */ }
        /* Interrupt Configurations */
        MSSP_I2C_Interrupt_Configurations(i2c_obj);
        /* Enable MSSP I2C Module */
        MSSP_MODULE_ENABLE_CFG();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType MSSP_I2C_DeInit(const MSSP_I2C_t *i2c_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != i2c_obj){
        /* Disable MSSP I2C Module */
        MSSP_MODULE_DISABLE_CFG();
        /* Interrupt Configurations */
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_INTERRUPT_DISABLE();
        MSSP_I2C_BUS_COL_INTERRUPTDISABLE();
#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Start(const MSSP_I2C_t *i2c_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != i2c_obj){
        /* Initiates start condition on SDA and SCL pins */
        SSPCON2bits.SEN = 1;
        /* Wait for the completion of the start condition */
        while(SSPCON2bits.SEN);
        /* Clear the MSSP Interrupt Flag bit */
        PIR1bits.SSPIF = 0;
        /* Report the start condition detection */
        if(SSPSTATbits.S == START_BIT_DETECTED){
            ret = E_OK;
        }
        else{
            ret = E_NOT_OK;
        }
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const MSSP_I2C_t *i2c_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != i2c_obj){
        /* Initiates repeated start condition on SDA and SCL pins */
        SSPCON2bits.RSEN = 1;
        /* Wait for the completion of the repeated start condition */
        while(SSPCON2bits.RSEN);
        /* Clear the MSSP Interrupt Flag bit */
        PIR1bits.SSPIF = 0;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Stop(const MSSP_I2C_t *i2c_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != i2c_obj){
        /* Initiates stop condition on SDA and SCL pins */
        SSPCON2bits.PEN = 1;
        /* Wait for the completion of the stop condition */
        while(SSPCON2bits.PEN);
        /* Clear the MSSP Interrupt Flag bit */
        PIR1bits.SSPIF = 0;
        /* Report the stop condition detection */
        if(SSPSTATbits.P == STOP_BIT_DETECTED){
            ret = E_OK;
        }
        else{
            ret = E_NOT_OK;
        }
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Write_Blocking(const MSSP_I2C_t *i2c_obj, uint8 i2c_data, uint8 *_ack){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL != i2c_obj) && (_ack != NULL)){
        /* Write data to the data register */
        SSPBUF = i2c_data;
        /* Wait the transmission to be completed */
        while(SSPSTATbits.BF);
        /* Clear the MSSP interrupt flag bit -> SSPIF */
        PIR1bits.SSPIF = 0;
        /* Report the acknowledge received from the slave */
        if(SSPCON2bits.ACKSTAT == I2C_ACK_REC_FROM_SLAVE){
            *_ack = I2C_ACK_REC_FROM_SLAVE;
        }
        else{
            *_ack = I2C_ACK_NOT_RECEIVED_FROM_SLAVE;
        }
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Read_Blocking(const MSSP_I2C_t *i2c_obj, uint8 ack, uint8 *i2c_data){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL != i2c_obj) && (NULL != i2c_data)){
        /* Master mode receive enable */
        I2C_MASTER_RECEIVE_ENABLE_CFG();
        /* Wait for buffer full flag: A complete byte received */
        while(!SSPSTATbits.BF);
        /* Copy the data registers to buffer variable */
        *i2c_data = SSPBUF;
        /* Send ACK or NACK after read */
        if(ack == I2C_MASTER_SEND_ACK){
            SSPCON2bits.ACKDT = 0; // ACK
            SSPCON2bits.ACKEN = 1; // Send ACK
        }
        else if(ack == I2C_MASTER_SEND_NACK){
            SSPCON2bits.ACKDT = 1; // NACK
            SSPCON2bits.ACKEN = 1; // Send NACK
        }
        else { /* Do Nothing */ }
    }
    return ret;
}

void MSSP_I2C_ISR(void){
    #if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    MSSP_I2C_FLAG_CLEAR();
    I2C_DefaultInterruptHandler();
    #endif
}

void MSSP_I2C_BC_ISR(void){
    #if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    MSSP_I2C_BUS_COL_InterruptFlagClear();
    I2C_Report_Write_Collision();
    #endif
}


static inline void MSSP_I2C_MODE_GPIO_CFG(){
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
}

static inline void I2C_Master_Mode_Clock_Configuration(const MSSP_I2C_t *i2c_obj){
    SSPCON1bits.SSPM = I2C_MASTER_MODE_DEFINE_CLOCK;
    SSPADD = (uint8)(((_XTAL_FREQ / 4.0) / i2c_obj->i2c_clock) - 1);
}

static inline void MSSP_I2C_Interrupt_Configurations(const MSSP_I2C_t *i2c_obj){
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    MSSP_I2C_INTERRUPT_ENABLE();
    MSSP_I2C_BUS_COL_INTERRUPTENABLE();
    MSSP_I2C_FLAG_CLEAR();
    MSSP_I2C_BUS_COL_InterruptFlagClear();
    I2C_Report_Write_Collision = i2c_obj->I2C_Report_Write_Collision;
    I2C_Report_Receive_Overflow = i2c_obj->I2C_Report_Receive_Overflow;
    I2C_DefaultInterruptHandler = i2c_obj->I2C_DefaultInterruptHandler;
    /* Interrupt Priority Configurations */

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PRIORITY_LEVELS_ENABLE();
    if(i2c_obj->i2c_cfg.mssp_i2c_priority == INTERRUPT_HIGH_PRIORITY){
        MSSP_I2C_HighPrioritySet();
        INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(i2c_obj->i2c_cfg.mssp_i2c_priority == INTERRUPT_LOW_PRIORITY){
        MSSP_I2C_LowPrioritySet();
        INTERRUPT_GlobalInterruptLowEnable();
    }
    else{ /* Do Nothing */ }

    if(i2c_obj->i2c_cfg.mssp_i2c_bc_priority == INTERRUPT_HIGH_PRIORITY){
        INTERRUPT_GlobalInterruptHighEnable();
        MSSP_I2C_BUS_COL_HighPrioritySet();
    }
    else if(i2c_obj->i2c_cfg.mssp_i2c_bc_priority == INTERRUPT_LOW_PRIORITY){
        INTERRUPT_GlobalInterruptLowEnable();
        MSSP_I2C_BUS_COL_LowPrioritySet();
    }
    else{ /* Do Nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
}

static inline void I2C_Slave_Mode_Configuration(const MSSP_I2C_t *i2c_obj){
    SSPCON1bits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg;
}

