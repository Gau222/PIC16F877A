/*
 * File:   T4C1.c
 * Author: galou
 *
 * Created on 27 de mayo de 2023, 03:40 AM
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000
void main(void) {
    TRISB = 0b10000000;
    //PORTB = 0b10000000;
    
    
    if(RB7==0){
        PORTB = 0b10000110; //Para 1
        __delay_ms(500);
        PORTB = 0b11011011;  //Para 2
        __delay_ms(500);
        PORTB = 0b11001111;  //Para 3
        __delay_ms(500);
        PORTB = 0b11100110;  //Para 4
        __delay_ms(500);
        PORTB = 0b11101101;  //Para 5
        __delay_ms(500);
        PORTB = 0b11111101;  //Para 6
        __delay_ms(500);
        PORTB = 0b11000111;  //Para 7
        __delay_ms(500);
        PORTB = 0b11111111;  //Para 8
        __delay_ms(500);
        PORTB = 0b11100111;  //Para 9
        __delay_ms(500);
    }else
        if(RD7==1){
          PORTB = 0b00000000;  //Para apagar  
        }
}
