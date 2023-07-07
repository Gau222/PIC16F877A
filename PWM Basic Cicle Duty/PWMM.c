/*
 * File:   PWMM.c
 * Author: galou
 *
 * Created on 4 de julio de 2023, 12:22 PM
 */

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 4000000
#include <xc.h>


void TIMER2_init(void)
{
    TMR2 = 0;
    PR2 = 249;
    T2CONbits.TOUTPS = 0b1111;      //POSTSCALER 1:16
    T2CONbits.T2CKPS = 0b00;        //Prescaler 1:16
    T2CONbits.TMR2ON = 1;           //tmr2 on    
}

void main(void) {
    TRISC= 0x00;
    TRISA= 0XFF;
    ADCON0= 0b10000000;
    ADCON1= 0b10000000;
    CCP1CON= 0b00001111; //habilitando pwm
    TIMER2_init();
     
    unsigned int dc;
    
    ADCON0bits.ADON=1;
    __delay_us(30);
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
    ADCON0bits.ADON = 0;
    dc = ADRESH;
    dc = dc<<8;
    dc = dc + ADRESL;
    
    if (dc>1000) dc= 1000;
        CCP1CONbits.CCP1Y = dc & (1<<0);
        CCP1CONbits.CCP1X = dc & (1<<1);
        CCPR1L = dc>>2;
}   