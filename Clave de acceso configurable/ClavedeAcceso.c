/*
 * File:   ClavedeAcceso.c
 * Author: galou
 *
 * Created on 6 de julio de 2023, 11:45 AM
 */


#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Sinvgle-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define D4 RD2
#define D5 RD3
#define D6 RD4
#define D7 RD5
#define RS RD0
#define EN RD1

#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "Keypad.h"

void main(void) {
    TRISA = 1;
    TRISD = 0;
    TRISC = 0;
    PORTA = 0;
    PORTD = 0;
    PORTC = 0;
    ADCON0 = 0;
    ADCON1 = 0;
    
    InitKeypad(); //Inicializar el teclado
    Lcd_Init(); //Inicializar el LCD
    
    
    
    
    
}
