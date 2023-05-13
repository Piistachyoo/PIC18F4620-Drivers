/* 
 * File:   hal_timr2.h
 * Author: omarm
 *
 * Created on May 9, 2023, 4:32 PM
 */

#ifndef HAL_TIMR2_H
#define	HAL_TIMR2_H

/* Section : Includes */
#include "../compiler.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section : Macro Declarations */
/* Timer 1 input clock post-scaler */
#define TIMER2_POSTSCALER_DIV_BY_1      0
#define TIMER2_POSTSCALER_DIV_BY_2      1
#define TIMER2_POSTSCALER_DIV_BY_3      2
#define TIMER2_POSTSCALER_DIV_BY_4      3
#define TIMER2_POSTSCALER_DIV_BY_5      4
#define TIMER2_POSTSCALER_DIV_BY_6      5
#define TIMER2_POSTSCALER_DIV_BY_7      6
#define TIMER2_POSTSCALER_DIV_BY_8      7
#define TIMER2_POSTSCALER_DIV_BY_9      8
#define TIMER2_POSTSCALER_DIV_BY_10     9
#define TIMER2_POSTSCALER_DIV_BY_11     10
#define TIMER2_POSTSCALER_DIV_BY_12     11
#define TIMER2_POSTSCALER_DIV_BY_13     12
#define TIMER2_POSTSCALER_DIV_BY_14     13
#define TIMER2_POSTSCALER_DIV_BY_15     14
#define TIMER2_POSTSCALER_DIV_BY_16     15

/* Timer 1 input clock pre-scaler */
#define TIMER1_PRESCALER_DIV_BY_1       0
#define TIMER1_PRESCALER_DIV_BY_4       1
#define TIMER1_PRESCALER_DIV_BY_16      2

/* Section : Macro Functions Declarations */
/* Section : Macro Functions Declarations */
#define TIMER2_MODULE_ENABLE()              (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()             (T2CONbits.TMR2ON = 0)

#define TIMER2_PRESCALER_SELECT(_PRESCALER)  (T2CONbits.T2CKPS = _PRESCALER)
#define TIMER2_POSTSCALER_SELECT(_PRESCALER) (T2CONbits.TOUTPS = _PRESCALER)

/* Section : Data Type Declarations */
typedef struct{
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* Timer2_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint8 timer2_preload_value;
    uint8 timer2_postscaler_value :4;
    uint8 timer2_prescaler_value  :2;
    uint8 timer2_reserved         :2;
}timer2_t;

/* Section : Function Declarations */
Std_ReturnType Timer2_Init(const timer2_t *_timer);
Std_ReturnType Timer2_DeInit(const timer2_t *_timer);
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _value);
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *_value);



#endif	/* HAL_TIMR2_H */

