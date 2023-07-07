/*
 * File:   Practica3.c
 * Author: galou
 *
 * Created on 22 de junio de 2023, 10:49 PM
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
#define RS RD2
#define EN RD3
#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "Keypad.h"





void main(void) {
    TRISA = 1;
    TRISB = 0;
    TRISD = 0;
    PORTA = 0;
    PORTB = 0;
    TRISD = 0;
    ADCON0 = 0b01000000;
    ADCON1 = 0b10000000;
    
    InitKeypad(); //Inicializar el teclado
    Lcd_Init(); //Inicializar el LCD
    
    //Inicializando variable
    int B;
    float Voltaje, Celcius, Fahrenheit; 
    char V[20];
    char C[20];
    char F[20];
    char Tecla1 = 'n';
    char Tecla2 = 'n';
    char Tecla3 = 'n';
    
    int i;
    while(1){//While para proteger del PORT a nuestro código
        ADCON0bits.ADON = 1; //Encedemos convertidor
        __delay_us(30);
        ADCON0bits.GO = 1; //Conversión en progreso
        while(ADCON0bits.GO ==1 );
        ADCON0bits.ADON = 0;
        
        
       
        B = ADRESH; //Declaro B con los bits de ADRESH
        B = B<<8; //Hacemos el recorrido hacia los bits más significantes
        B = B+ADRESL; //Sumamos ADRESH con bits corregidos + ADRESL
        Voltaje = B*(5.0/1024.0);//Conversión a voltaje
        Celcius = Voltaje*100.0;
        Fahrenheit = (Celcius*1.8)+32.0;
        sprintf(V,"Voltaje = %.2f",Voltaje);
        sprintf(C,"C = %.2f",Celcius);
        sprintf(F,"F = %.2f",Fahrenheit);
        
        
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Menu  ");
        Lcd_Set_Cursor(2,2);
        Lcd_Write_String("1  2  3  ");
        Tecla1 = switch_press_scan();
        Tecla2 = switch_press_scan();
        Tecla3 = switch_press_scan();
        
        
       
        
        
          if (Tecla1 == '1'){
        Lcd_Clear();
        Lcd_Set_Cursor(1,2);
        Lcd_Write_String("Dana Valeria");
        Lcd_Set_Cursor(2,2);
        Lcd_Write_String("Micro");
        __delay_ms(1500);
        Lcd_Clear();
        Lcd_Set_Cursor(1,2);
        Lcd_Write_String("203295");
        Lcd_Set_Cursor(2,2);
        Lcd_Write_String("7A");
        __delay_ms(1500);
          }
        
       
        if (Tecla2 == '2'){
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String(C);
        __delay_ms(1500);  
        }
        
        if(Tecla3 == '3'){
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String(F);
        __delay_ms(1000);  
        }
        
        
     
    }
}
 