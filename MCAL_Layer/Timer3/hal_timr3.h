/* 
 * File:   hal_timr3.h
 * Author: omarm
 *
 * Created on May 9, 2023, 4:33 PM
 */

#ifndef HAL_TIMR3_H
#define	HAL_TIMR3_H

/* Section : Includes */
#include "../compiler.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declarations */
#define TIMER3_TIMER_MODE               0
#define TIMER3_COUNTER_MODE             1

#define TIMER3_SYNC_COUNTER_MODE        0
#define TIMER3_ASYNC_COUNTER_MODE       1

#define TIMER3_PRESCALER_DIV_BY_1       0
#define TIMER3_PRESCALER_DIV_BY_2       1
#define TIMER3_PRESCALER_DIV_BY_4       2
#define TIMER3_PRESCALER_DIV_BY_8       3

#define TIMER3_RW_REG_8BIT_MODE         0
#define TIMER3_RW_REG_16BIT_MODE        1

/* Section : Macro Functions Declarations */
#define TIMER3_MODULE_ENABLE()              (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()             (T3CONbits.TMR3ON = 0)

#define TIMER3_TIMER_MODE_ENABLE()          (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE()        (T3CONbits.TMR3CS = 1)

#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()  (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()   (T3CONbits.T3SYNC = 0)

#define TIMER3_RW_REG_8BIT_MODE_ENABLE()    (T3CONbits.RD16 = 0)
#define TIMER3_RW_REG_16BIT_MODE_ENABLE()   (T3CONbits.RD16 = 1)

#define TIMER3_PRESCALER_SELECT(_PRESCALER) (T3CONbits.T3CKPS = _PRESCALER)

/* Section : Data Type Declarations */
typedef struct{
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* Timer3_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint16 timer3_preload_value;    
    uint8 timer3_prescaler_value :2;
    uint8 timer3_mode            :1;
    uint8 timer3_counter_mode    :1;
    uint8 timer3_reg_wr_mode     :1;
    uint8 timer3_reserved        :3;
}timer3_t;

/* Section : Function Declarations */
Std_ReturnType Timer3_Init(const timer3_t *_timer);
Std_ReturnType Timer3_DeInit(const timer3_t *_timer);
Std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 _value);
Std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *_value);


#endif	/* HAL_TIMR3_H */

