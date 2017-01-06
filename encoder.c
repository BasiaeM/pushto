#include "encoder.h"

void encoder()
{
		//DDRB = 0b00000000; //piny b7 i b6 to wyjscia
	//PORTB = 0b11000000;
	
	gotoXy(0,1 );			//set the cursor to 1 column of 1st row
	prints("A=");
	if(EN_PIN & 0b00000001)	
		integerToLcd(1);		// print adc value to the lcd
		else
		integerToLcd(0);
	prints(" B=");
	if(EN_PIN & 0b00000010)	
		integerToLcd(1);		// print adc value to the lcd
		else
		integerToLcd(0);
}

