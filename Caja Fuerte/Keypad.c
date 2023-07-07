#include "Keypad.h"

// Function name: InitKeypad
void InitKeypad(void)
{
	Keypad_PORT = 0x00;	// Set Keypad port pin values zero
	Keypad_PORT_Direction = 0xF0;	// Last 4 pins input, First 4 pins output

	
	OPTION_REG &= 0x7F; //Habilita las resistencias PULL UP internas
}

char keypad_scanner(void)	
{	
	X_1 = 0; X_2 = 1; X_3 = 1; X_4 = 1; 	

	if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return '7'; }
	if (Y_2 == 0) { __delay_ms(100); while (Y_2==0); return '8'; }
	if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '9'; }
	if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return '/'; }

	X_1 = 1; X_2 = 0; X_3 = 1; X_4 = 1; 	

	if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return '4'; }
	if (Y_2 == 0) { __delay_ms(100); while (Y_2==0); return '5'; }
	if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '6'; }
	if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return 'X'; }
	
	X_1 = 1; X_2 = 1; X_3 = 0; X_4 = 1; 	

	if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return '1'; }
	if (Y_2 == 0) { __delay_ms(100); while (Y_2==0); return '2'; }
	if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '3'; }
	if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return '-'; }
	
	X_1 = 1; X_2 = 1; X_3 = 1; X_4 = 0; 	

	if (Y_1 == 0) { __delay_ms(100); while (Y_1==0); return 'ON'; }
	if (Y_2 == 0) { __delay_ms(100); while (Y_2==0); return '0'; }
	if (Y_3 == 0) { __delay_ms(100); while (Y_3==0); return '='; }
	if (Y_4 == 0) { __delay_ms(100); while (Y_4==0); return '+'; }

	return 'n';    
}


// Function name: GetKey
// Read pressed key value from keypad and return its value
char switch_press_scan(void)           	 // Get key from user
{
	char key = 'n';              // Assume no key pressed

	while(key=='n')              // Wait untill a key is pressed
		key = keypad_scanner();   // Scan the keys again and again

	return key;                  //when key pressed then return its value
}