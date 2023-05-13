/* 
 * File:   hal_spi.h
 * Author: omarm
 *
 * Created on April 29, 2023, 2:47 PM
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H

/* Section : Includes */
#include <xc.h>
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../GPIO/hal_gpio.h"
#include "../mcal_std_types.h"

/* Section : Macro Declarations */

/* Receive Overflow Indicator */
#define SPI_SLAVE_RECEIVE_OVERFLOW_DETECTED      1
#define SPI_SLAVE_RECEIVE_OVERFLOW_NOT_DETECTED  0

/* Write Collision Detect */
#define SPI_WRITE_COLLISION_DETECTED             1
#define SPI_WRITE_COLLISION_NOT_DETECTED         0

/* Buffer Full Status bit (Receive mode only) */ 
#define SPI_BUFFER_FULL_RECEIVE_COMPLETE         1
#define SPI_BUFFER_FULL_RECEIVE_NOT_COMPLETE     0

/* Section : Macro Functions Declarations */
#define SPI_ENABLE_MODULE()     (SSPCON1bits.SSPEN = 1)
#define SPI_DISABLE_MODULE()    (SSPCON1bits.SSPEN = 0)

/* Section : Data Type Declarations */
typedef enum{
	SPI_MASTER_FOSC_DIV4,
    SPI_MASTER_FOSC_DIV16,
    SPI_MASTER_FOSC_DIV64,
    SPI_MASTER_FOSC_TMR2,
    SPI_SLAVE_SS_ENABLED,
    SPI_SLAVE_SS_DISABLED
}enu_SPI_CLOCK;


typedef enum{
	CLK_IDLE_LOW,
	CLK_IDLE_HIGH
}enu_SPI_ClockPolarity;

typedef enum{
	SAMPLE_MIDDLE,
    SAMPLE_END
}enu_SPI_Sampling;

typedef enum{
    SPI_TRANSMIT_ACTIVE_TO_IDLE,
    SPI_TRANSMIT_IDLE_TO_ACTIVE
}enu_SPI_TRANSMIT;

typedef struct{
	enu_SPI_CLOCK         Prescale;
	enu_SPI_ClockPolarity ClockPolarity;
	enu_SPI_Sampling	  Sampling;
    enu_SPI_TRANSMIT      TransmitMode;
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(*MSSP_SPI_IntHandler)(void);
    interrupt_priority_cfg INT_Prio;
#endif
}SPI_cfg_t;

/* Section : Function Declarations */
Std_ReturnType SPI_vInit(const SPI_cfg_t *SPI_obj);
void SPI_vDeInit();
Std_ReturnType SPI_vSendByte(uint8 Copy_u8Data);
Std_ReturnType SPI_u8ReceiveByte(uint8 *_Data);
Std_ReturnType SPI_vSendByte_NonBlocking(uint8 Copy_u8Data);
Std_ReturnType SPI_u8ReceiveByte_NonBlocking(uint8 *_Data);

#endif	/* HAL_SPI_H */

