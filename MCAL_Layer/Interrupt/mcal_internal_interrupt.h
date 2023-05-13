/* 
 * File:   mcal_internal_interrupt.h
 * Author: omarm
 *
 * Created on March 15, 2023, 12:25 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* Section : Includes */
#include "mcal_interrupt_config.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

// This macro clears the interrupt enable for the ADC module
#define ADC_INTERRUPT_ENABLE()      (PIE1bits.ADIE = 1)
// This macro sets the interrupt enable for the ADC module
#define ADC_INTERRUPT_DISABLE()     (PIE1bits.ADIE = 0)
// This macro clears the interrupt flag for the ADC module
#define ADC_FLAG_CLEAR()            (PIR1bits.ADIF = 0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
// This macro sets the ADC interrupt priority to be high priority
#define ADC_HighPrioritySet()       (IPR1bits.ADIP = 1)
// This macro sets the ADC interrupt priority to be low priority
#define ADC_LowPrioritySet()        (IPR1bits.ADIP = 0)

#endif

#endif

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

// This macro clears the interrupt enable for the TIMER0 module
#define TIMER0_INTERRUPT_ENABLE()      (INTCONbits.TMR0IE = 1)
// This macro sets the interrupt enable for the TIMER0 module
#define TIMER0_INTERRUPT_DISABLE()     (INTCONbits.TMR0IE = 0)
// This macro clears the interrupt flag for the TIMER0 module
#define TIMER0_FLAG_CLEAR()            (INTCONbits.TMR0IF = 0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
// This macro sets the TIMER0 interrupt priority to be high priority
#define TIMER0_HighPrioritySet()       (INTCON2bits.TMR0IP = 1)
// This macro sets the TIMER0 interrupt priority to be low priority
#define TIMER0_LowPrioritySet()        (INTCON2bits.TMR0IP = 0)

#endif

#endif

#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

// This macro clears the interrupt enable for the TIMER1 module
#define TIMER1_INTERRUPT_ENABLE()      (PIE1bits.TMR1IE = 1)
// This macro sets the interrupt enable for the TIMER1 module
#define TIMER1_INTERRUPT_DISABLE()     (PIE1bits.TMR1IE = 0)
// This macro clears the interrupt flag for the TIMER1 module
#define TIMER1_FLAG_CLEAR()            (PIR1bits.TMR1IF = 0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
// This macro sets the TIMER1 interrupt priority to be high priority
#define TIMER1_HighPrioritySet()       (IPR1bits.TMR1IP = 1)
// This macro sets the TIMER1 interrupt priority to be low priority
#define TIMER1_LowPrioritySet()        (IPR1bits.TMR1IP = 0)

#endif

#endif

#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

// This macro clears the interrupt enable for the TIMER2 module
#define TIMER2_INTERRUPT_ENABLE()      (PIE1bits.TMR2IE = 1)
// This macro sets the interrupt enable for the TIMER2 module
#define TIMER2_INTERRUPT_DISABLE()     (PIE1bits.TMR2IE = 0)
// This macro clears the interrupt flag for the TIMER2 module
#define TIMER2_FLAG_CLEAR()            (PIR1bits.TMR2IF = 0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
// This macro sets the TIMER2 interrupt priority to be high priority
#define TIMER2_HighPrioritySet()       (IPR1bits.TMR2IP = 1)
// This macro sets the TIMER2 interrupt priority to be low priority
#define TIMER2_LowPrioritySet()        (IPR1bits.TMR2IP = 0)

#endif

#endif

#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

// This macro clears the interrupt enable for the TIMER3 module
#define TIMER3_INTERRUPT_ENABLE()      (PIE2bits.TMR3IE = 1)
// This macro sets the interrupt enable for the TIMER3 module
#define TIMER3_INTERRUPT_DISABLE()     (PIE2bits.TMR3IE = 0)
// This macro clears the interrupt flag for the TIMER3 module
#define TIMER3_FLAG_CLEAR()            (PIR2bits.TMR3IF = 0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
// This macro sets the TIMER3 interrupt priority to be high priority
#define TIMER3_HighPrioritySet()       (IPR2bits.TMR3IP = 1)
// This macro sets the TIMER3 interrupt priority to be low priority
#define TIMER3_LowPrioritySet()        (IPR2bits.TMR3IP = 0)

#endif

#endif

#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

// This macro clears the interrupt enable for the CCP1 module
#define CCP1_INTERRUPT_ENABLE()      (PIE1bits.CCP1IE = 1)
// This macro sets the interrupt enable for the CCP1 module
#define CCP1_INTERRUPT_DISABLE()     (PIE1bits.CCP1IE = 0)
// This macro clears the interrupt flag for the CCP1 module
#define CCP1_FLAG_CLEAR()            (PIR1bits.CCP1IF = 0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
// This macro sets the CCP1 interrupt priority to be high priority
#define CCP1_HighPrioritySet()       (IPR1bits.CCP1IP = 1)
// This macro sets the CCP1 interrupt priority to be low priority
#define CCP1_LowPrioritySet()        (IPR1bits.CCP1IP = 0)

#endif

#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

// This macro clears the interrupt enable for the CCP2 module
#define CCP2_INTERRUPT_ENABLE()      (PIE2bits.CCP2IE = 1)
// This macro sets the interrupt enable for the CCP2 module
#define CCP2_INTERRUPT_DISABLE()     (PIE2bits.CCP2IE = 0)
// This macro clears the interrupt flag for the CCP2 module
#define CCP2_FLAG_CLEAR()            (PIR2bits.CCP2IF = 0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
// This macro sets the CCP2 interrupt priority to be high priority
#define CCP2_HighPrioritySet()       (IPR2bits.CCP2IP = 1)
// This macro sets the CCP2 interrupt priority to be low priority
#define CCP2_LowPrioritySet()        (IPR2bits.CCP2IP = 0)

#endif

#endif

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

// This macro clears the interrupt enable for the EUSART TX module
#define EUSART_TX_INTERRUPT_ENABLE()      (PIE1bits.TXIE = 1)
// This macro sets the interrupt enable for the EUSART TX module
#define EUSART_TX_INTERRUPT_DISABLE()     (PIE1bits.TXIE = 0)
// This macro clears the interrupt flag for the EUSART TX module
#define EUSART_TX_FLAG_CLEAR()            (PIR1bits.TXIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

// This macro sets the EUSART TX interrupt priority to be high priority
#define EUSART_TX_HighPrioritySet()       (IPR1bits.TXIP = 1)
// This macro sets the EUSART TX interrupt priority to be low priority
#define EUSART_TX_LowPrioritySet()        (IPR1bits.TXIP = 0)

#endif

#endif

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

// This macro clears the interrupt enable for the EUSART RX module
#define EUSART_RX_INTERRUPT_ENABLE()      (PIE1bits.RCIE = 1)
// This macro sets the interrupt enable for the EUSART RX module
#define EUSART_RX_INTERRUPT_DISABLE()     (PIE1bits.RCIE = 0)
// This macro clears the interrupt flag for the EUSART RX module
#define EUSART_RX_FLAG_CLEAR()            (PIR1bits.RCIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

// This macro sets the EUSART RX interrupt priority to be high priority
#define EUSART_RX_HighPrioritySet()       (IPR1bits.RCIP = 1)
// This macro sets the EUSART RX interrupt priority to be low priority
#define EUSART_RX_LowPrioritySet()        (IPR1bits.RCIP = 0)

#endif
#endif

#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

// This macro clears the interrupt enable for the SPI module
#define MSSP_SPI_INTERRUPT_ENABLE()      (PIE1bits.SSPIE = 1)
// This macro sets the interrupt enable for the SPI module
#define MSSP_SPI_INTERRUPT_DISABLE()     (PIE1bits.SSPIE = 0)
// This macro clears the interrupt flag for the SPI module
#define MSSP_SPI_FLAG_CLEAR()            (PIR1bits.SSPIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
// This macro sets the SPI interrupt priority to be high priority
#define MSSP_SPI_HighPrioritySet()       (IPR1bits.SSPIP = 1)
// This macro sets the SPI interrupt priority to be low priority
#define MSSP_SPI_LowPrioritySet()        (IPR1bits.SSPIP = 0)
#endif

#endif

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

// This macro clears the interrupt enable for the I2C module
#define MSSP_I2C_INTERRUPT_ENABLE()      (PIE1bits.SSPIE = 1)
#define MSSP_I2C_BUS_COL_INTERRUPTENABLE()  (PIE2bits.BCLIE = 0)
// This macro sets the interrupt enable for the I2C module
#define MSSP_I2C_INTERRUPT_DISABLE()     (PIE1bits.SSPIE = 0)
#define MSSP_I2C_BUS_COL_INTERRUPTDISABLE() (PIE2bits.BCLIE = 1)
// This macro clears the interrupt flag for the I2C module
#define MSSP_I2C_FLAG_CLEAR()            (PIR1bits.SSPIF = 0)
#define MSSP_I2C_BUS_COL_InterruptFlagClear()   (PIR2bits.BCLIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
// This macro sets the I2C interrupt priority to be high priority
#define MSSP_I2C_HighPrioritySet()       (IPR1bits.SSPIP = 1)
#define MSSP_I2C_BUS_COL_HighPrioritySet()  (IPR2bits.BCLIP = 1)
// This macro sets the I2C interrupt priority to be low priority
#define MSSP_I2C_LowPrioritySet()        (IPR1bits.SSPIP = 0)
#define MSSP_I2C_BUS_COL_LowPrioritySet()  (IPR2bits.BCLIP = 0)
#endif

#endif

/* Section : Data Type Declarations */

/* Section : Function Declarations */


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

