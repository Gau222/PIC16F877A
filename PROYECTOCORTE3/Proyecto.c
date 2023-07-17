/*
 * File:   Proyecto.c
 * Author: Galo Cabrera
 *
 * Created on 14 de julio de 2023, 08:38 PM
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
#include "servo.h"

/*
void __interrupt() boton(void){
    
    
    if(PORTBbits.RB0 == 1){
        __delay_ms(20);
        if(PORTBbits.RB0 == 1){
        
            while(RB0==1){

        PORTDbits.RD6 = 1;
        PORTDbits.RD7 = 1;
        __delay_ms(500);
        
                
            }
            
           
            
            
                     }
                        
            
                          
                    
                }
    
    INTCONbits.INTF = 0;
    return;
}




void main(void) {
    INTCON = 0b10010000; //Habilitando interrupciones
    TRISD = 0; //PORTD como OUTPUT
    PORTD = 0; //Limpiar PORTD
    TRISC = 0; //PORTC como OUTPUT
    PORTC = 0; //Limpiar PORTC
    TRISB = 1; //PORTB como INPUT
    PORTB = 0; //Limpiar PORTB
    TRISE = 0;
    PORTE = 0;
    ADCON0 = 0b01000000;//Para AN0
    ADCON1 = 0b10001110;//Usar AN0  como analógico y justificado a la derecha, todos los demás pines son digitales
    TRISA = 0b00000001; // Configurando RA0 como INPUT y todos los demás como OUTPUT
    PORTA = 0b00000000; //Limpiar puerto A
    
    
    Lcd_Init();
    Lcd_Clear();
    
    char t[20];
    int A;
    float P;
    
    
    
    while(1){
        
        ADCON0bits.ADON = 1; //Enciende el convertidor
        __delay_us(30);
        ADCON0bits.GO = 1; //Inicializa la conversión y solito pasa a 0
        while(ADCON0bits.GO==1);
        ADCON0bits.ADON = 0;//Apaga el convertidor
        
        A = ADRESH;//La variable A será ADRESH
        A = A<<8; //Se hace el recorrido de 8 bits
        A=A+ADRESL;//Se hace la suma de ADRESH+ADRESL
        P = (A*100.0)/1024.0;//Convirtiendo a porcentaje
        PORTDbits.RD6 = 0;
        PORTDbits.RD7 = 0;
        
        
        sprintf(t,"Luz = %.1f",P);
        Lcd_Set_Cursor(2,1); //A es fila y B es Columna
        Lcd_Write_String(t);
       /*
        Sacando rangos de bits
        *Para 75% de luminosidad = 730 bits  
        *Para 50% de luminosidad = 487 bits
        *Para 25% de luminosidad = 244 bits
       
        while (P<16){
            PORTAbits.RA5 = 1;
        }
        
    
      
        
                                        int x = 0;
                                int j[10] = {128, 121, 36, 48, 25, 18, 2, 120, 0, 0b0011000};

                                while (1) {
                                    if (RC7 == 1) {
                                        x++; // Incrementar el contador
                                        PORTC = j[x];
                                        PORTAbits.RA1 = 1;
                                        __delay_ms(300);
                                         PORTAbits.RA1 = 0;
                                        
                                        // Si el contador llega a 10, reiniciarlo a 0
                                        if (x >= 10) {
                                            x = 0;
                                        }

                                        PORTB = j[x]; // Mostrar el contador en el display
                                        __delay_ms(500);

                                        if (x < 8) {
                                            PORTAbits.RA2 = 1;
                                            PORTAbits.RA3 = 0;
                                            Lcd_Set_Cursor(2, 1);
                                            Lcd_Write_String("Qx libre");
                                        } else {
                                            PORTAbits.RA2 = 0;
                                            PORTAbits.RA3 = 1;
                                            Lcd_Set_Cursor(2, 1);
                                            Lcd_Write_String("Qx lleno");
                                        }
                                    }
                                            }
                                
                                
    }
   } 
   */

void __interrupt() boton(void) {
    if (INTCONbits.INTF == 1) {
        __delay_ms(20);
        if (INTCONbits.INTF == 1) {
            while (PORTBbits.RB0 == 1) {
                PORTDbits.RD6 = 1;
                PORTDbits.RD7 = 1;
                __delay_ms(500);
            }
        }
        INTCONbits.INTF = 0;
    }
}

void main(void) {
    INTCON = 0b10010000; // Habilitando interrupciones
    TRISD = 0; // PORTD como OUTPUT
    PORTD = 0; // Limpiar PORTD
    TRISC = 0; // PORTC como OUTPUT
    PORTC = 0; // Limpiar PORTC
    TRISB = 1; // PORTB como INPUT
    PORTB = 0; // Limpiar PORTB
    TRISE = 0;
    PORTE = 0;
    ADCON0 = 0b01000000; // Para AN0
    ADCON1 = 0b10001110; // Usar AN0 como analógico y justificado a la derecha, todos los demás pines son digitales
    TRISA = 0b00000001; // Configurando RA0 como INPUT y todos los demás como OUTPUT
    PORTA = 0b00000000; // Limpiar puerto A

    Lcd_Init();
    Lcd_Clear();

    char t[20];
    int A;
    float P;

    while (1) {
        ADCON0bits.ADON = 1; // Enciende el convertidor
        __delay_us(30);
        ADCON0bits.GO = 1; // Inicializa la conversión y se pone a 0 automáticamente
        while (ADCON0bits.GO == 1);
        ADCON0bits.ADON = 0; // Apaga el convertidor

        A = ADRESH; // La variable A será ADRESH
        A = A << 8; // Se hace el recorrido de 8 bits
        A = A + ADRESL; // Se hace la suma de ADRESH + ADRESL
        P = (A * 100.0) / 1024.0; // Convirtiendo a porcentaje
        PORTDbits.RD6 = 0;
        PORTDbits.RD7 = 0;

        sprintf(t, "Luz = %.1f", P);
        Lcd_Set_Cursor(2, 1); // A es la fila y B es la columna
        Lcd_Write_String(t);

        /*
        Sacando rangos de bits
        * Para 75% de luminosidad = 730 bits  
        * Para 50% de luminosidad = 487 bits
        * Para 25% de luminosidad = 244 bits
        */
        if (P < 16) {
            PORTAbits.RA5 = 1;
            PORTAbits.RA4 = 1;
        }
        
                                 int x = 0;
                                int j[10] = {128, 121, 36, 48, 25, 18, 2, 120, 0, 0b0011000};

                                while (1) {
                                    if (RC7 == 1) {
                                        x++; // Incrementar el contador
                                        PORTC = j[x];
                                        PORTAbits.RA1 = 1;
                                        __delay_ms(300);
                                         PORTAbits.RA1 = 0;
                                        
                                        // Si el contador llega a 10, reiniciarlo a 0
                                        if (x >= 10) {
                                            x = 0;
                                        }

                                        PORTB = j[x]; // Mostrar el contador en el display
                                        __delay_ms(500);

                                        if (x < 8) {
                                            PORTAbits.RA2 = 1;
                                            PORTAbits.RA3 = 0;
                                            Lcd_Clear();
                                            Lcd_Set_Cursor(2, 1);
                                            Lcd_Write_String("Qx libre");
                                        } else {
                                            PORTAbits.RA2 = 0;
                                            PORTAbits.RA3 = 1;
                                            Lcd_Clear();
                                            Lcd_Set_Cursor(2, 1);
                                            Lcd_Write_String("Qx lleno");
                                        }
                                    }
                                            }
        
    }
}