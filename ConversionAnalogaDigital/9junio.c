/*
 * File:   9junio.c
 * Author: galou
 *Actividad 1 Corte 2 Conversión analógica digital 
 * Galo Udiel Cabrera Cruz 203270
 * Created on 9 de junio de 2023, 08:37 AM
 */

#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Sinvgle-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 4000000

void main(void) {
    ADCON1 = 0b00000010;//Usar puerto A como todo análogicos
    ADCON0 = 0b01011000; //Seleciona el canal
    TRISA = 0b11111111; // Configurando RA1 como INPUT y todos los demás como OUTPUT
    TRISB = 0b00000000;
    TRISC = 0b00000000;
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    PORTC = 0b00000000;
    while(1){
    ADCON0bits.ADON = 1; //Encendiendo convertidor
    __delay_us(30);
    ADCON0bits.GO = 1; // Inicia conversión
    while (ADCON0bits.GO==1); //Hasta que GODONE sea 0, pasa a la siguiente etapa, o sea cuando termine la conversión
    
    ADCON0bits.ADON = 0; //Apago convertidor
    
    PORTC = ADRESL;
    PORTB = ADRESH;
    }
    
    
    
    
    
    }

