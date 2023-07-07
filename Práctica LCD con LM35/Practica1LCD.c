/*
 * File:   Practica1LCD.c
 * Author: galou
 *
 * Created on 16 de junio de 2023, 09:06 AM
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


void main(void) {
    TRISD = 0x00;
    ADCON0 = 0b01000000;//Para AN0
    ADCON1 = 0b10000000;//Usar puerto A como ANAL�GICOS y justificado a la derecha
    TRISA = 0b00000001; // Configurando RA0 como INPUT y todos los dem�s como OUTPUT
    PORTA = 0b00000000; //Limpiar puerto A
    
    
    
    
    
    Lcd_Init();
    Lcd_Clear();
    
    char t[20];
    int A;
    float Voltaje, Celcius;
    int C;
    
    while(1){
        
        ADCON0bits.ADON = 1; //Enciende el convertidor
        __delay_us(30);
        ADCON0bits.GO = 1; //Inicializa la conversi�n y solito pasa a 0
        while(ADCON0bits.GO==1);
        ADCON0bits.ADON = 0;//Apaga el convertidor
        
        A = ADRESH;//La variable A ser� ADRESH
        A = A<<8; //Se hace el recorrido de 8 bits
        A=A+ADRESL;//Se hace la suma de ADRESH+ADRESL
        Voltaje = A*(5.0/1024.0);//Conversi�n a voltaje
        Celcius = Voltaje*100.0;
    sprintf(t,"Grados = %f",Celcius);
            
    Lcd_Set_Cursor(2,1); //A es fila y B es Columna
    Lcd_Write_String(t);
    
   __delay_ms(1000);
   //Lcd_Set_Cursor(2,1);
   //Lcd_Write_String("Quiero gorditas");
    __delay_ms(1000);
    Lcd_Set_Cursor(1,16);
    Lcd_Write_Char('V');
    }
    
    
}