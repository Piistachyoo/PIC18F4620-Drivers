/* 
 * File:   mcal_interrupt_manager.c
 * Author: omarm
 *
 * Created on March 15, 2023, 12:26 AM
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_flag = 0;
static volatile uint8 RB5_flag = 0;
static volatile uint8 RB6_flag = 0;
static volatile uint8 RB7_flag = 0;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
void __interrupt() InterruptManagerHigh(void){
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCUR)){
        INT0_ISR();
    }
    else{ /* Do Nothing */ }
    if((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == INTERRUPT_OCCUR) && (INTCON3bits.INT1IP == INTERRUPT_HIGH_PRIORITY)){
        INT1_ISR();
    }
    else{ /* Do Nothing */ }
    if((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_OCCUR) && (INTCON3bits.INT2IP == INTERRUPT_HIGH_PRIORITY)){
        INT2_ISR();
    }
    else{ /* Do Nothing */ }
    if(INTCON2bits.RBIP == INTERRUPT_HIGH_PRIORITY){
        if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB4 == STD_HIGH) && (RB4_flag == STD_LOW)){
        RB4_flag = STD_HIGH;
        RB4_ISR(STD_HIGH);
    }
    else if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB4 == STD_LOW) && (RB4_flag == STD_HIGH)){
        RB4_flag = STD_LOW;
        RB4_ISR(STD_LOW);
    }
    else{ /* Do Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB5 == STD_HIGH) && (RB5_flag == STD_LOW)){
        RB5_flag = STD_HIGH;
        RB5_ISR(STD_HIGH);
    }
    else if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB5 == STD_LOW) && (RB5_flag == STD_HIGH)){
        RB5_flag = STD_LOW;
        RB5_ISR(STD_LOW);
    }
    else{ /* Do Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB6 == STD_HIGH) && (RB6_flag == STD_LOW)){
        RB6_flag = STD_HIGH;
        RB6_ISR(STD_HIGH);
    }
    else if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB6 == STD_LOW) && (RB6_flag == STD_HIGH)){
        RB6_flag = STD_LOW;
        RB6_ISR(STD_LOW);
    }
    else{ /* Do Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB7 == STD_HIGH) && (RB7_flag == STD_LOW)){
        RB7_flag = STD_HIGH;
        RB7_ISR(STD_HIGH);
    }
    else if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB7 == STD_LOW) && (RB7_flag == STD_HIGH)){
        RB7_flag = STD_LOW;
        RB7_ISR(STD_LOW);
    }
    else{ /* Do Nothing */ }
    }else{ /* Do Nothing */ }
    if((PIE1bits.ADIE == INTERRUPT_ENABLE) && (PIR1bits.ADIF == INTERRUPT_OCCUR) && (IPR1bits.ADIP == INTERRUPT_HIGH_PRIORITY)){
        ADC_Interrupt_ISR();
    }
    else{ /* Do Nothing */ }
    if((INTCONbits.TMR0IE == INTERRUPT_ENABLE) && (INTCONbits.TMR0IF == INTERRUPT_OCCUR) && (INTCON2bits.TMR0IP == INTERRUPT_HIGH_PRIORITY)){
        TMR0_Int_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.TMR1IE == INTERRUPT_ENABLE) && (PIR1bits.TMR1IF == INTERRUPT_OCCUR) && (IPR1bits.TMR1IP == INTERRUPT_HIGH_PRIORITY)){
        TMR1_Int_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.TMR2IE == INTERRUPT_ENABLE) && (PIR1bits.TMR2IF == INTERRUPT_OCCUR) && (IPR1bits.TMR2IP == INTERRUPT_HIGH_PRIORITY)){
        TMR2_Int_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE2bits.TMR3IE == INTERRUPT_ENABLE) && (PIR2bits.TMR3IF == INTERRUPT_OCCUR) && (IPR2bits.TMR3IP == INTERRUPT_HIGH_PRIORITY)){
        TMR3_Int_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.TXIE == INTERRUPT_ENABLE) && (PIR1bits.TXIF == INTERRUPT_OCCUR) && (IPR1bits.TXIP == INTERRUPT_HIGH_PRIORITY)){
        EUSART_TX_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.RCIE == INTERRUPT_ENABLE) && (PIR1bits.RCIF == INTERRUPT_OCCUR) && (IPR1bits.RCIP == INTERRUPT_HIGH_PRIORITY)){
        EUSART_RX_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.SSPIE == INTERRUPT_ENABLE) && (PIR1bits.SSPIF == INTERRUPT_OCCUR) && (IPR1bits.SSPIP == INTERRUPT_HIGH_PRIORITY)){
        MSSP_I2C_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE2bits.BCLIE == INTERRUPT_ENABLE) && (PIR2bits.BCLIF == INTERRUPT_OCCUR) && (IPR2bits.BCLIP == INTERRUPT_HIGH_PRIORITY)){
        MSSP_I2C_BC_ISR();
    }
    else{ /* Do Nothing */ }
}

void __interrupt(low_priority) InterruptManagerLow(void){
    if((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == INTERRUPT_OCCUR) && (INTCON3bits.INT1IP == INTERRUPT_LOW_PRIORITY)){
        INT1_ISR();
    }
    else{ /* Do Nothing */ }
    if((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_OCCUR) && (INTCON3bits.INT2IP == INTERRUPT_LOW_PRIORITY)){
        INT2_ISR();
    }
    else{ /* Do Nothing */ }
    if(INTCON2bits.RBIP == INTERRUPT_LOW_PRIORITY){
        if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB4 == STD_HIGH) && (RB4_flag == STD_LOW)){
        RB4_flag = STD_HIGH;
        RB4_ISR(STD_HIGH);
    }
    else if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB4 == STD_LOW) && (RB4_flag == STD_HIGH)){
        RB4_flag = STD_LOW;
        RB4_ISR(STD_LOW);
    }
    else{ /* Do Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB5 == STD_HIGH) && (RB5_flag == STD_LOW)){
        RB5_flag = STD_HIGH;
        RB5_ISR(STD_HIGH);
    }
    else if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB5 == STD_LOW) && (RB5_flag == STD_HIGH)){
        RB5_flag = STD_LOW;
        RB5_ISR(STD_LOW);
    }
    else{ /* Do Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB6 == STD_HIGH) && (RB6_flag == STD_LOW)){
        RB6_flag = STD_HIGH;
        RB6_ISR(STD_HIGH);
    }
    else if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB6 == STD_LOW) && (RB6_flag == STD_HIGH)){
        RB6_flag = STD_LOW;
        RB6_ISR(STD_LOW);
    }
    else{ /* Do Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB7 == STD_HIGH) && (RB7_flag == STD_LOW)){
        RB7_flag = STD_HIGH;
        RB7_ISR(STD_HIGH);
    }
    else if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB7 == STD_LOW) && (RB7_flag == STD_HIGH)){
        RB7_flag = STD_LOW;
        RB7_ISR(STD_LOW);
    }
    else{ /* Do Nothing */ }
    }else{ /* Do Nothing */ }
    if((PIE1bits.ADIE == INTERRUPT_ENABLE) && (PIR1bits.ADIF == INTERRUPT_OCCUR) && (IPR1bits.ADIP == INTERRUPT_LOW_PRIORITY)){
        ADC_Interrupt_ISR();
    }
    else{ /* Do Nothing */ }
    if((INTCONbits.TMR0IE == INTERRUPT_ENABLE) && (INTCONbits.TMR0IF == INTERRUPT_OCCUR) && (INTCON2bits.TMR0IP == INTERRUPT_LOW_PRIORITY)){
        TMR0_Int_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.TMR1IE == INTERRUPT_ENABLE) && (PIR1bits.TMR1IF == INTERRUPT_OCCUR) && (IPR1bits.TMR1IP == INTERRUPT_LOW_PRIORITY)){
        TMR1_Int_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.TMR2IE == INTERRUPT_ENABLE) && (PIR1bits.TMR2IF == INTERRUPT_OCCUR) && (IPR1bits.TMR2IP == INTERRUPT_LOW_PRIORITY)){
        TMR2_Int_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE2bits.TMR3IE == INTERRUPT_ENABLE) && (PIR2bits.TMR3IF == INTERRUPT_OCCUR) && (IPR2bits.TMR3IP == INTERRUPT_LOW_PRIORITY)){
        TMR3_Int_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.TXIE == INTERRUPT_ENABLE) && (PIR1bits.TXIF == INTERRUPT_OCCUR) && (IPR1bits.TXIP == INTERRUPT_LOW_PRIORITY)){
        EUSART_TX_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.RCIE == INTERRUPT_ENABLE) && (PIR1bits.RCIF == INTERRUPT_OCCUR) && (IPR1bits.RCIP == INTERRUPT_LOW_PRIORITY)){
        EUSART_RX_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.SSPIE == INTERRUPT_ENABLE) && (PIR1bits.SSPIF == INTERRUPT_OCCUR) && (IPR1bits.SSPIP == INTERRUPT_LOW_PRIORITY)){
        MSSP_I2C_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE2bits.BCLIE == INTERRUPT_ENABLE) && (PIR2bits.BCLIF == INTERRUPT_OCCUR) && (IPR2bits.BCLIP == INTERRUPT_LOW_PRIORITY)){
        MSSP_I2C_BC_ISR();
    }
    else{ /* Do Nothing */ }
}
#else
void __interrupt() InterruptManager(void){
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCUR)){
        INT0_ISR();
    }
    else{ /* Do Nothing */ }
    if((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == INTERRUPT_OCCUR)){
        INT1_ISR();
    }
    else{ /* Do Nothing */ }
    if((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_OCCUR)){
        INT2_ISR();
    }
    else{ /* Do Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB4 == STD_HIGH) && (RB4_flag == STD_LOW)){
        RB4_flag = STD_HIGH;
        RB4_ISR(STD_HIGH);
    }
    else if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB4 == STD_LOW) && (RB4_flag == STD_HIGH)){
        RB4_flag = STD_LOW;
        RB4_ISR(STD_LOW);
    }
    else{ /* Do Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB5 == STD_HIGH) && (RB5_flag == STD_LOW)){
        RB5_flag = STD_HIGH;
        RB5_ISR(STD_HIGH);
    }
    else if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB5 == STD_LOW) && (RB5_flag == STD_HIGH)){
        RB5_flag = STD_LOW;
        RB5_ISR(STD_LOW);
    }
    else{ /* Do Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB6 == STD_HIGH) && (RB6_flag == STD_LOW)){
        RB6_flag = STD_HIGH;
        RB6_ISR(STD_HIGH);
    }
    else if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB6 == STD_LOW) && (RB6_flag == STD_HIGH)){
        RB6_flag = STD_LOW;
        RB6_ISR(STD_LOW);
    }
    else{ /* Do Nothing */ }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB7 == STD_HIGH) && (RB7_flag == STD_LOW)){
        RB7_flag = STD_HIGH;
        RB7_ISR(STD_HIGH);
    }
    else if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB7 == STD_LOW) && (RB7_flag == STD_HIGH)){
        RB7_flag = STD_LOW;
        RB7_ISR(STD_LOW);
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.ADIE == INTERRUPT_ENABLE) && (PIR1bits.ADIF == INTERRUPT_OCCUR)){
        ADC_Interrupt_ISR();
    }
    else{ /* Do Nothing */ }
    if((INTCONbits.TMR0IE == INTERRUPT_ENABLE) && (INTCONbits.TMR0IF == INTERRUPT_OCCUR)){
        TMR0_Int_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.TMR1IE == INTERRUPT_ENABLE) && (PIR1bits.TMR1IF == INTERRUPT_OCCUR)){
        TMR1_Int_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.TMR2IE == INTERRUPT_ENABLE) && (PIR1bits.TMR2IF == INTERRUPT_OCCUR)){
        TMR2_Int_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE2bits.TMR3IE == INTERRUPT_ENABLE) && (PIR2bits.TMR3IF == INTERRUPT_OCCUR)){
        TMR3_Int_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.TXIE == INTERRUPT_ENABLE) && (PIR1bits.TXIF == INTERRUPT_OCCUR)){
        EUSART_TX_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.RCIE == INTERRUPT_ENABLE) && (PIR1bits.RCIF == INTERRUPT_OCCUR)){
        EUSART_RX_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE1bits.SSPIE == INTERRUPT_ENABLE) && (PIR1bits.SSPIF == INTERRUPT_OCCUR)){
        MSSP_I2C_ISR();
    }
    else{ /* Do Nothing */ }
    if((PIE2bits.BCLIE == INTERRUPT_ENABLE) && (PIR2bits.BCLIF == INTERRUPT_OCCUR)){
        MSSP_I2C_BC_ISR();
    }
    else{ /* Do Nothing */ }
}

#endif
