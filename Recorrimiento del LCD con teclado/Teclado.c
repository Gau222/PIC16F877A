/*
 * File:   Teclado.c
 * Author: galou
 *
 * Created on 19 de junio de 2023, 08:20 AM
 */

#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Sinvgle-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
#define RS RD3
#define EN RD2
#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "Keypad.h"

void main(void) {
    TRISD=0x00;
    
    char Tecla = 'n';
    
    InitKeypad();//Inicializando teclado
    Lcd_Init();//Inicializando LCD
    
    Lcd_Clear();
    
    while(1){
        for(int i=0;i<17;i++){
        Tecla = switch_press_scan();
        Lcd_Set_Cursor(1,1+i);
        Lcd_Write_Char(Tecla);
    }
    }
    
    
    
  
    
    
}
