/*
 * File:   203270T1C3.c
 * Author: Galo Cabrera
 *
 * Created on 9 de julio de 2023, 08:38 PM
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
#define RS RD0
#define EN RD1

#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "Keypad.h"

char password[4]; // Contraseña ingresada por el usuario
char confirmPassword[4]; // Contraseña para confirmar

void main(void) {
    TRISD = 0;
    PORTD = 0;
    TRISC = 0;
    PORTC = 0;
    ADCON0 = 0b01000000;//Para AN0
    ADCON1 = 0b10000000;//Usar puerto A como ANALÓGICOS y justificado a la derecha
    TRISA = 0b00000001; // Configurando RA0 como INPUT y todos los demás como OUTPUT
    PORTA = 0b00000000; //Limpiar puerto A
    
    InitKeypad(); // Inicializar el teclado
    Lcd_Init(); // Inicializar el LCD
    char t[20];
    int A;
    float Voltaje, Celcius;
    int C;
    
    while(1){
        
        ADCON0bits.ADON = 1; //Enciende el convertidor
        __delay_us(30);
        ADCON0bits.GO = 1; //Inicializa la conversión y solito pasa a 0
        while(ADCON0bits.GO==1);
        ADCON0bits.ADON = 0;//Apaga el convertidor
        
        A = ADRESH;//La variable A será ADRESH
        A = A<<8; //Se hace el recorrido de 8 bits
        A=A+ADRESL;//Se hace la suma de ADRESH+ADRESL
        Voltaje = A*(5.0/1024.0);//Conversión a voltaje
        Celcius = Voltaje*100.0;
        sprintf(t,"Grados = %f",Celcius);
        
    
    while (1) {
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("Bienvenido");
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_String("Presionar 0");
        
        char flag = 1; // Indica cuando regresar al menú inicial
        
        while (flag) {
            char key = switch_press_scan();
            
            if (key == '0') {
                Lcd_Clear();
                Lcd_Set_Cursor(1, 1);
                Lcd_Write_String("Dar Password");
                
                char contador = 0; // Para llevar la cuenta de cuántos dígitos se han ingresado
                
                while (contador < 4) {
                    key = switch_press_scan();
                    
                    if (key != 255 && contador < 4) {
                        password[contador++] = key;
                        Lcd_Set_Cursor(2, 5 + contador);
                        Lcd_Write_Char('*');
                    }
                }
                
                flag = 0;
                
                if (contador == 4) {
                    Lcd_Clear();
                    Lcd_Set_Cursor(1, 1);
                    Lcd_Write_String("Contrasena ");
                    Lcd_Set_Cursor(2, 1);
                    Lcd_Write_String("guardada");
                    __delay_ms(2000);
                    
                    Lcd_Clear();
                    Lcd_Set_Cursor(1, 1);
                    Lcd_Write_String("Confirmar");
                    Lcd_Set_Cursor(2, 1);
                    Lcd_Write_String("contrasena");
                    
                    contador = 0;
                    
                    while (contador < 4) {
                        key = switch_press_scan();
                        
                        if (key != 255 && contador < 4) {
                            confirmPassword[contador++] = key;
                            Lcd_Clear();
                            Lcd_Set_Cursor(2, 5 + contador);
                            Lcd_Write_Char('*');
                        }
                    }
                    
                    if (contador == 4) {
                        Lcd_Clear();
                        Lcd_Set_Cursor(1, 1);
                        
                        char confirmOk = 1;
                        
                        for (char i = 0; i < 4; i++) {
                            if (password[i] != confirmPassword[i]) {
                                confirmOk = 0;
                                break;
                            }
                        }
                        
                        if (confirmOk) {
                            Lcd_Set_Cursor(1, 1);
                            Lcd_Write_String("Contrasena");
                            Lcd_Set_Cursor(2, 1);
                            Lcd_Write_String("Confirmada");
                            __delay_ms(2000);
                            break; // Salir del bucle para continuar con la verificación de la contraseña
                        } else {
                            Lcd_Write_String("Contraseña");
                            Lcd_Set_Cursor(2, 1);
                            Lcd_Write_String("incorrecta");
                            __delay_ms(2000);
                        }
                    } else {
                        Lcd_Clear();
                        Lcd_Set_Cursor(1, 1);
                        Lcd_Write_String("Contraseña");
                         Lcd_Set_Cursor(2, 1);
                         Lcd_Write_String("incompleta");
                        __delay_ms(2000);
                    }
                } else {
                    Lcd_Clear();
                    Lcd_Set_Cursor(1, 1);
                    Lcd_Write_String("Contraseña incompleta");
                    __delay_ms(2000);
                }
            }
        }
        
       /* Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("Verificando...");
        */
        char passOk = 1; // Variable para indicar si la contraseña es correcta
        
        // Verificar si la contraseña ingresada es igual a la contraseña guardada
        for (char i = 0; i < 4; i++) {
            if (password[i] != confirmPassword[i]) {
                passOk = 0;
                break;
            }
        }
        
        if (passOk) {
            Lcd_Clear();
            Lcd_Set_Cursor(1, 1);
            Lcd_Write_String("Contrasena");
             Lcd_Set_Cursor(2, 1);
            Lcd_Write_String("correcta");
            // Realizar acciones si la contraseña es correcta
                        PORTCbits.RC1 = 1;
                        __delay_ms(2000);
                         PORTCbits.RC1 = 0;
                        
        } else {
            Lcd_Clear();
            Lcd_Set_Cursor(1, 1);
            Lcd_Write_String("Contrasena");
             Lcd_Set_Cursor(2, 1);
             Lcd_Write_String("incorrecta");
            // Realizar acciones si la contraseña es incorrecta
                        PORTCbits.RC0 = 1;
                        Lcd_Set_Cursor(2,1); //A es fila y B es Columna
                        Lcd_Write_String(t);

        }
        
        __delay_ms(2000);
    }
}
    }