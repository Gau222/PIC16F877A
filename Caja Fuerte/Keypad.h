#ifndef __KEYPAD_H
#define __KEYPAD_H
#include <xc.h>

#define _XTAL_FREQ 4000000 //Crystal Frequency, used in delay

// Define pins
#define X_1		RB0
#define X_2		RB1
#define X_3		RB2
#define X_4		RB3
#define Y_1		RB4
#define Y_2		RB5
#define Y_3		RB6
#define Y_4		RB7

#define Keypad_PORT			PORTB
#define Keypad_PORT_Direction		TRISB	


// Function declarations
void InitKeypad(void);
char switch_press_scan(void);

#endif