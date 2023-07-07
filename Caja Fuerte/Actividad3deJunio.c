/*
 * File:   Actividad3deJunio.c
 * Author: galou
 *
 * Created on 3 de julio de 2023, 08:20 AM
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
#include "lcd.h"
#include "Keypad.h"


    char const pass[] = {'2', '2', '2', '2'};//contraseña


void main(void) {
    
    TRISD = 0;
    PORTD = 0;
    TRISC = 0;
    PORTC = 0;
    InitKeypad(); //Inicializar el teclado
    Lcd_Init(); //Inicializar el LCD
    
    while (1){
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Bienvenido");
         Lcd_Set_Cursor(2,1);
        Lcd_Write_String("Presionar 0");
        
        char flag = 1; //me dice cuando regresar al menú inicial
        char passOk = 0; // para saber si la contraseña es correcta
        while (flag) {
            char key = switch_press_scan();
            if (key == '0') {
                Lcd_Clear();
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("Dar Password");
                char password[4];//delcaraon un array donde voy a guardar la contraseña que de el usuario
                char contador = 0;//para saber cuantos digitos me han dado para la contraseña
                while (contador < 4) {
                    key = switch_press_scan();
                    if (key != 255 && contador < 4) {
                        password[contador++] = key;
                         Lcd_Set_Cursor(2, 5 + contador);
                        Lcd_Write_Char('*');
                    }
                }
         for (char i = 0; i < 4; i++) {
                    passOk = 1;
                    if (pass[i] != password[i]){
                        passOk = 0;
                        break;//rompe el for
                    }
                }
                flag = 0;
                if (passOk) {
                    Lcd_Clear();
                     Lcd_Set_Cursor(1,1);
                     Lcd_Write_String("Abriendo...");
                    PORTC = 255;
                    PORTCbits.RC1 = 0;
                    __delay_ms(200);
                    PORTCbits.RC2 = 0;
                    __delay_ms(200);
                    PORTCbits.RC2 = 1;
                    __delay_ms(200);
                    PORTCbits.RC2 = 0;
                    __delay_ms(100);
                    PORTCbits.RC2 = 1;
                    __delay_ms(200);
                    PORTC = 0;
                     Lcd_Clear();
                    Lcd_Set_Cursor(1, 1);
                   Lcd_Write_String("Sea bienvenido");
                    Lcd_Set_Cursor(2,1);
                    Lcd_Write_String("Cerrara en 3s");
                    __delay_ms(3000);
                    Lcd_Clear();
                    Lcd_Set_Cursor(1, 1);
                    Lcd_Write_String("Cerrando tapa...");
                    PORTC = 255;
                    PORTCbits.RC0 = 0;
                    __delay_ms(200);
                    PORTCbits.RC2 = 0;
                    __delay_ms(200);
                    PORTCbits.RC2 = 1;
                    __delay_ms(200);
                    PORTCbits.RC2 = 0;
                    __delay_ms(200);
                    PORTCbits.RC2 = 1;
                    __delay_ms(200);
                    PORTC = 0;
                     } else {
                    Lcd_Clear();
                     Lcd_Set_Cursor(1, 1);
                    Lcd_Write_String("Lastima");
                    Lcd_Set_Cursor(2, 1);
                   Lcd_Write_String("Margarito");
                    __delay_ms(2000);
                }   
        
        
        
        
    }
    
}
        }
    }
