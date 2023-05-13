/* 
 * File:   mcal_external_interrupt.h
 * Author: omarm
 *
 * Created on March 15, 2023, 12:26 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* Section : Includes */
#include "mcal_interrupt_config.h"
#include "../GPIO/hal_gpio.h"

/* Section : Macro Declarations */
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
// This macro clears the interrupt enable for the external interrupt INT0
#define EXT_INT0_InterruptDisable()     (INTCONbits.INT0IE = 0)
// This macro sets the interrupt enable for the external interrupt INT0
#define EXT_INT0_InterruptEnable()      (INTCONbits.INT0IE = 1)
// This macro clears the interrupt flag for the external interrupt INT0
#define EXT_INT0_InterruptFlagClear()   (INTCONbits.INT0IF = 0)
// This macro sets the edge detect of the external interrupt INT0 to rising edge
#define EXT_INT0_RisingEdgeSet()        (INTCON2bits.INTEDG0 = 1)
// This macro clears the edge detect of the external interrupt INT0 to falling edge
#define EXT_INT0_FallingEdgeSet()       (INTCON2bits.INTEDG0 = 0)

// This macro clears the interrupt enable for the external interrupt INT1
#define EXT_INT1_InterruptDisable()     (INTCON3bits.INT1IE = 0)
// This macro sets the interrupt enable for the external interrupt INT1
#define EXT_INT1_InterruptEnable()      (INTCON3bits.INT1IE = 1)
// This macro clears the interrupt flag for the external interrupt INT1
#define EXT_INT1_InterruptFlagClear()   (INTCON3bits.INT1IF = 0)
// This macro sets the edge detect of the external interrupt INT1 to rising edge
#define EXT_INT1_RisingEdgeSet()        (INTCON2bits.INTEDG1 = 1)
// This macro clears the edge detect of the external interrupt INT1 to falling edge
#define EXT_INT1_FallingEdgeSet()       (INTCON2bits.INTEDG1 = 0)

// This macro clears the interrupt enable for the external interrupt INT2
#define EXT_INT2_InterruptDisable()     (INTCON3bits.INT2IE = 0)
// This macro sets the interrupt enable for the external interrupt INT2
#define EXT_INT2_InterruptEnable()      (INTCON3bits.INT2IE = 1)
// This macro clears the interrupt flag for the external interrupt INT2
#define EXT_INT2_InterruptFlagClear()   (INTCON3bits.INT2IF = 0)
// This macro sets the edge detect of the external interrupt INT2 to rising edge
#define EXT_INT2_RisingEdgeSet()        (INTCON2bits.INTEDG2 = 1)
// This macro clears the edge detect of the external interrupt INT2 to falling edge
#define EXT_INT2_FallingEdgeSet()       (INTCON2bits.INTEDG2 = 0)
        
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
// This macro sets the INT1 external interrupt priority to be high priority
#define EXT_INT1_HighPrioritySet()      (INTCON3bits.INT1IP = 1)
// This macro sets the INT1 external interrupt priority to be low priority
#define EXT_INT1_LowPrioritySet()       (INTCON3bits.INT1IP = 0)

// This macro sets the INT2 external interrupt priority to be high priority
#define EXT_INT2_HighPrioritySet()      (INTCON3bits.INT2IP = 1)
// This macro sets the INT2 external interrupt priority to be low priority
#define EXT_INT2_LowPrioritySet()       (INTCON3bits.INT2IP = 0)

#endif

#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
// This macro clears the interrupt enable for the external interrupt RBx
#define EXT_RBx_InterruptDisable()      (INTCONbits.RBIE = 0)
// This macro sets the interrupt enable for the external interrupt RBx
#define EXT_RBx_InterruptEnable()       (INTCONbits.RBIE = 1)

// This macro clears the interrupt flag for the external interrupt RBx
#define EXT_RBx_InterruptFlagClear()    (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
// This macro sets the RBx External Interrupt priority to be High priority
#define EXT_RBx_Priority_High()         (INTCON2bits.RBIP = 1)
// This macro sets the RBx External Interrupt priority to be Low priority
#define EXT_RBx_Priority_Low()          (INTCON2bits.RBIP = 0)


#endif

#endif

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE
}interrupt_INTx_edge;

typedef enum{
    INTERRUPT_INT0 = 0,
    INTERRUPT_INT1,
    INTERRUPT_INT2
}interrupt_INTX_src;

typedef struct{
    interrupt_INTx_edge     int_edge;
    interrupt_INTX_src      int_scr;
    interrupt_priority_cfg  int_prio;
    pin_config_t            gpio_pin;
    void (*EXT_InterruptHandler)(void);
}interrupt_INTX_t;

typedef struct{
    interrupt_priority_cfg  int_prio;
    pin_config_t            gpio_pin;
    void (*EXT_InterruptHandler_High)(void);
    void (*EXT_InterruptHandler_Low)(void);
}interrupt_RBX_t;

/* Section : Function Declarations */
Std_ReturnType interrupt_INTx_Init(const interrupt_INTX_t *int_obj);
Std_ReturnType interrupt_INTx_DeInit(const interrupt_INTX_t *int_obj);

Std_ReturnType interrupt_RBx_Init(const interrupt_RBX_t *int_obj);
Std_ReturnType interrupt_RBx_DeInit(const interrupt_RBX_t *int_obj);



#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

