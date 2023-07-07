/*
 * File:   Interrupciones.c
 * Author: galou
 *
 * Created on 30 de junio de 2023, 08:31 AM
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
#include "lcd.h"

void __interrupt() boton(void){
    if(PORTBbits.RB0 == 1){
        __delay_ms(20);
        if(PORTBbits.RB0 == 1){
        
            while(RB0==1){
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Espera");
        __delay_ms(1000);
            }
            
           
            
            
                     }
                        
            
                          
                    
                }
    
    INTCONbits.INTF = 0;
    return;
}


void main(void) {
    INTCON = 0b10010000; //Habilitando interrupciones
    TRISC = 0;
    TRISB = 1;
    PORTB = 0;
    PORTC = 0;
    TRISD = 0;
    PORTD = 0;
    unsigned char numeros[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
     Lcd_Init(); //Inicializar el LCD
    while(1){
        for(int i=0; i<=9; i++){
            PORTC =~numeros[i];
            __delay_ms(500);
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Contando");
        
        }
    }
    
    
    
}
