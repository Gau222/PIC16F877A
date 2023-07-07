/*
 * Inicio bloque de comentario
 * File:   prueba.c
 * Author: galou 203270
 *
 * Created on 12 de mayo de 2023, 09:59 AM
 */

// PIC16F877A Configuration Bit Settings

// 'C' source line config statements


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
    TRISC = 0b00010000;
    PORTC = 0B00000000;
    TRISB = 0b00000000;
    PORTB = 0B11111111;
    
    
    if (RC3==1){
        /// para v
        PORTB=0b01000001;
        __delay_ms (500);
        /// para f
        PORTB=0b00001110;
        __delay_ms (500);
        ///para o
        PORTB=0b01000000;
        __delay_ms (500);
        //para 5
        PORTB=0b00010010;
        __delay_ms (500);
        
    }
    


}