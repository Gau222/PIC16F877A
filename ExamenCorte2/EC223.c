/*
 * File:   EC223.c
 * Author: galou
 *
 * Created on 23 de junio de 2023, 08:24 AM
 */

/*#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Sinvgle-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define D4 RC2
#define D5 RC3
#define D6 RC4
#define D7 RC5
#define RS RC0
#define EN RC1
#define A1 RE1
#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"

void main(void) {
//Inicialización de puertos
    TRISA = 8;
    TRISE = 2;
    TRISC = 0;
    TRISD = 0;
    PORTA = 0;
    PORTE = 0;
    PORTC = 0;
    PORTD = 0;
    
    Lcd_Init(); //Inicializar el LCD
    
//Inicializamos registro ADCON
    ADCON0 = 0b01011000;//Canal AN3 para la conversión de bits
    ADCON1 = 0b10001001;//Justificado a la derecha, entrada AN6 como digital y AN3 como analógica
    
//Declaración de variables
    int B;//Declaramos variable para el registro de Bits
    char b[20];//Declaramos char para guardar el sprintf
    float P;
    
//Encendemos módulo convertidor con ADON y iniciamos la conversión el GO
    while(1){//While para proteger del PORT a nuestro código
        ADCON0bits.ADON = 1; //Encedemos convertidor
        __delay_us(30);
        ADCON0bits.GO = 1; //Conversión en progreso
        while(ADCON0bits.GO ==1 );
        ADCON0bits.ADON = 0;
    
        B = ADRESH; //Declaro B con los bits de ADRESH
        B = B<<8; //Hacemos el recorrido hacia los bits más significantes
        B = B+ADRESL; //Sumamos ADRESH con bits corregidos + ADRESL
        P = (B*100.0)/1024.0;//Convirtiendo a porcentaje
        
        
        
         
        while(A1==1){ //Encerramos en un While para cuando A1=0 esto porque sino se ejecutaría ambas ocasiones
        /*Iniciamos condiciones para los valores del POT 
         
         Para 0-15% = 163 bits
         Para 16-30& = 164 y 307 bits
         Para 31-100& = 308 bits
         
        if(0<B && B<163){ //Para un rango de 0 a 15% de humedad 
            Lcd_Clear();
            sprintf(b,"Humedad= %.2f",P);
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String(b);
            __delay_ms(500);
        }
        
        if(164<B && B<307){ //Para un rango de 16 a 30 % de humedad
            Lcd_Clear();
            sprintf(b,"Humedad= %.2f",P);
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String(b);
            __delay_ms(100);
        }
        
        if(308<B && B<1024){//Para un rango de 30 a 100% de humedad
            Lcd_Clear();
            sprintf(b,"Humedad= %.2f",P);
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String(b);
            __delay_ms(100);
                            }
        }
        
        
        while(A1==0){//Encerramos esta parte en un while para cuando A1 esté presionado se ejecute la parte con el semáforo de LEDS y su respectiva clasificación
            if(0<B && B<163){//Para el rango de 0 a 15% de humedad
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Humedad baja");
            PORTDbits.RD0 = 1;//Encendemos verde
            PORTDbits.RD1 = 0;//Apagamos
            PORTDbits.RD2 = 0;//Apagamos
            __delay_ms(100);
                            }
            if(164<B && B<307){//Para el rango de 16 a 30% de humedad
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Humedad media");
            PORTDbits.RD0 = 0;//Apagamos 
            PORTDbits.RD1 = 1;//Encendemos amarillo
            PORTDbits.RD2 = 0;//Apagamos
            __delay_ms(100);
                            }
            if(308<B && B<1024){//Para el rango de 31 a 100% de humedad
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Humedad alta");
            PORTDbits.RD0 = 0;//Apagamos
            PORTDbits.RD1 = 0;//Apagamos
            PORTDbits.RD2 = 1;//Encendemos rojo
            __delay_ms(100);
            PORTDbits.RD0 = 0;//Apagamos
            PORTDbits.RD1 = 0;//Apagamos
            PORTDbits.RD2 = 0;//Apagamos
                            }
            
            
            
            
            
            
                     }

    
            
    

            }
    
    
}
 */
// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7


// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 4000000
#include <xc.h>
#include "lcd.h"
#include "Keypad.h"
#include <stdio.h>
#include <stdlib.h>
#define Keypad_PORT   PORTB
#define Keypad_PORT_Direction   TRISB


void main(void) {
    
    TRISD= 0b00000000; //Declarando el puerto D como salida para el LCD
    TRISB= 0b11111111; //Declarando el puerto B como entrada para el teclado matricial 
    TRISA= 0b11111111; //Se define el puerto A como salida
    PORTA= 0b00000000; //Limpiando el piuerto A
    
    ADCON0 = 0b01110011; // 0B11111111 - canal AN6
    ADCON1 = 0b10000000; //Justificacion a la derecha y entradas analógicas
    
    Lcd_Init();
    Lcd_Clear();
    InitKeypad();
    
    //Definicion de variables
    int i; //Variable de entrada para hacer los calculos  
    float voltaje, ctemperatura, ftemperatura; //Variable de voltaje, temperatura en celsius y temperatura en fahrenheit  
    char s[25]; //Para escribir sobre el LCD
    char T='n'; //Para definir las entradas del teclado
    unsigned int b; 
     
     
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Opciones");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("1=D 2=C 3=F");
    
    while(1){
        
        ADCON0bits.ADON=1;
        __delay_us(30);
        ADCON0bits.GO=1;
        while(ADCON0bits.GO==1);
        ADCON0bits.ADON=0; 
        __delay_ms(20);
        i=ADRESH<<8;
        i=i + ADRESL;
        
        voltaje = i*5.0/1024.0;
        ctemperatura = voltaje*100.0;
        ftemperatura = (ctemperatura*1.8)+32.0;
    
        T=switch_press_scan();

    if (T == '1') {
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("Kamilah Morales");
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String("203079");
            for(b=0;b<12;b++){
                __delay_ms(100);
                Lcd_Shift_Left();
                }
            Lcd_Clear();
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String("UPChiapas");
            Lcd_Set_Cursor(2,1);
            Lcd_Write_String("Microcontroladores 7A");
            for(b=0;b<21;b++){
                __delay_ms(100);
                Lcd_Shift_Left();
            }
        }
        
    if(T=='2'){
            for(b=0;b<15;b++){
                __delay_ms(1);
                Lcd_Shift_Left();
            }
            Lcd_Clear();
            sprintf(s,"Temp C=%f",ctemperatura); 
            Lcd_Set_Cursor(1,1);
            Lcd_Write_String(s);
            
        }
    if (T == '3') {
            for(b=0;b<15;b++){
                __delay_ms(1);
                Lcd_Shift_Left();
            }
            Lcd_Cl?