/* 
 * File:   hal_timr1.h
 * Author: omarm
 *
 * Created on May 8, 2023, 5:02 PM
 */

#ifndef HAL_TIMR1_H
#define	HAL_TIMR1_H

/* Section : Includes */
#include "../compiler.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declarations */
#define TIMER1_TIMER_MODE               0
#define TIMER1_COUNTER_MODE             1

#define TIMER1_SYNC_COUNTER_MODE        0
#define TIMER1_ASYNC_COUNTER_MODE       1

#define TIMER1_OSC_ENABLE               1
#define TIMER1_OSC_DISABLE              0

#define TIMER1_RW_REG_8BIT_MODE         0
#define TIMER1_RW_REG_16BIT_MODE        1

/* Section : Macro Functions Declarations */
#define TIMER1_MODULE_ENABLE()              (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()             (T1CONbits.TMR1ON = 0)

#define TIMER1_TIMER_MODE_ENABLE()          (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()        (T1CONbits.TMR1CS = 1)

#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()  (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()   (T1CONbits.T1SYNC = 0)

#define TIMER1_OSC_HW_ENABLE()              (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_HW_DISABLE()             (T1CONbits.T1OSCEN = 0)

#define TIMER1_SYSTEM_CLK_STATUS()          (T1CONbits.T1RUN)

#define TIMER1_RW_REG_8BIT_MODE_ENABLE()    (T1CONbits.RD16 = 0)
#define TIMER1_RW_REG_16BIT_MODE_ENABLE()    (T1CONbits.RD16 = 1)

#define TIMER1_PRESCALER_SELECT(_PRESCALER) (T1CONbits.T1CKPS = _PRESCALER)

/* Section : Data Type Declarations */
typedef enum{
    TIMER1_PRESCALER_DIV_BY_1,
    TIMER1_PRESCALER_DIV_BY_2,
    TIMER1_PRESCALER_DIV_BY_4,
    TIMER1_PRESCALER_DIV_BY_8
}timer1_prescaler_select_t;

typedef struct{
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* Timer1_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    timer1_prescaler_select_t prescaler_value;
    uint16 timer1_preload_value;    
    uint8 timer1_mode          :1;
    uint8 timer1_counter_mode  :1;
    uint8 timer1_osc_cfg       :1;
    uint8 timer1_reg_wr_mode   :1;
    uint8 timer1_reserved      :4;
}timer1_t;

/* Section : Function Declarations */
Std_ReturnType Timer1_Init(const timer1_t *_timer);
Std_ReturnType Timer1_DeInit(const timer1_t *_timer);
Std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 _value);
Std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16 *_value);

#endif	/* HAL_TIMR1_H */

