/*
 * File:   T2C3203270.c
 * Author: Galo Cabrera
 *
 * Created on 10 de julio de 2023, 05:33 AM
 */

#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define D4 RC3
#define D5 RC4
#define D6 RC5
#define D7 RC6
#define RS RC0
#define EN RC1

#define _XTAL_FREQ 4000000
#include <xc.h>

#include <stdio.h>
#include <stdlib.h>
#include "Keypad.h"
#include "lcd.h"


void TIMER2_init(void)
{
    TMR2 = 0;
    PR2 = 249;
    T2CONbits.TOUTPS = 0b1111;      // POSTSCALER 1:16
    T2CONbits.T2CKPS = 0b00;        // Prescaler 1:16
    T2CONbits.TMR2ON = 1;           // TMR2 on    
}

float calcularPorcentaje(unsigned int dc) {
    return (float)dc * 100.0 / 1024.0;
 
}

void main(void) {
    TRISC = 0x00;
    TRISA = 0xFF;
    ADCON0 = 0b10000000;
    ADCON1 = 0b10000000;
    TRISD = 0;
    PORTD = 0;
    CCP1CON = 0b00001111; // habilitando pwm
    TIMER2_init();
     InitKeypad(); // Inicializar el teclado
    Lcd_Init(); // Inicializar el LCD
    
    unsigned int dc; 
    char porcentajeStr[10];
    char Tecla1 = 'n';
    char Tecla2 = 'n';
   
    
    ADCON0bits.ADON = 1;
    __delay_us(30);
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO == 1);
    ADCON0bits.ADON = 0;
    dc = ADRESH;
    dc = dc << 8;
    dc = dc + ADRESL;
    
       Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Menu  ");
        Lcd_Set_Cursor(2,2);
        Lcd_Write_String("1  2    ");
        Tecla1 = switch_press_scan();
        Tecla2 = switch_press_scan();
       
        
        
    
    if (dc > 1000) dc = 1000;
    CCP1CONbits.CCP1Y = dc & (1 << 0);
    CCP1CONbits.CCP1X = dc & (1 << 1);
    CCPR1L = dc >> 2;
    
    
     float porcentaje = calcularPorcentaje(dc);
    
    sprintf(porcentajeStr, "Ciclo = %.2f%%", porcentaje);
     if (Tecla1 == '1'){
     Lcd_Clear(); 
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String(porcentajeStr);
    __delay_ms(2000);

     }
    
    if (Tecla2 == '2'){
     Lcd_Clear(); 
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Ciclo = 50%");
    __delay_ms(2000);

     }
}
