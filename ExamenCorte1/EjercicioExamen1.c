/*
 * File:   EjercicioExamen1.c
 * Author: galou
 *
 * Created on 26 de mayo de 2023, 09:09 AM
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
    TRISB = 0b00000000;
    //PORTB = 0b11111111;
    
    //PORTC = 0b11111111;
    TRISC = 0b00000000;
    
    TRISD = 0b10010000;
    PORTD = 0b00000000;
    
    //Para Fuego
    if (RD7==0){
        PORTCbits.RC0 = 1;
        PORTCbits.RC1 = 0;
        PORTCbits.RC2 = 0;
        PORTCbits.RC3 = 0; //Se forma la letra F
        PORTCbits.RC4 = 1;
        PORTCbits.RC5 = 1;
        PORTCbits.RC6 = 1;
        PORTCbits.RC7 = 0;
        
    //}else 
    //    PORTC = 00000000;
    
    //Para humo
    if (RD4==1){
       PORTBbits.RB0 = 1; 
       PORTBbits.RB1 = 0;
       PORTBbits.RB2 = 0;
       PORTBbits.RB3 = 1; //Se forma la letra H
       PORTBbits.RB4 = 0;
       PORTBbits.RB5 = 0;
       PORTBbits.RB6 = 0;
      
    }
    
    if (RD4==0){
       PORTBbits.RB0 = 1; 
       PORTBbits.RB1 = 1;
       PORTBbits.RB2 = 1;
       PORTBbits.RB3 = 1;
       PORTBbits.RB4 = 1;
       PORTBbits.RB5 = 1;
       PORTBbits.RB6 = 1;
       
       
    }
}
