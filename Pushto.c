#include <avr/io.h>
#include <stdio.h>

#define F_CPU 1000000UL
#include <util/delay.h>
#include "lcd.h"
#include "encoder.h"
#include "keypad.h"
    


void system_init (void)
{
	//DDRA = 0xFE;		//set the PORTA Direction Set every pin of PORTA as out except AN0 
	DDRD = 0xFF;		//set the PORTD Direction Set every pin of PORTD as out as our lcd on this
	EN_DIR = 0b00000000; //enkodery
	EN_PORT = 0b00000011;
	//ADCSRA=0X00;		// CODE for ADC demo (optional)
	//ADMUX = 0x40;
	//ADCSRA = 0x87;
}

int main(void)
{
	//unsigned int temp;

	
	system_init();
	lcdInit();

	prints("keypad");
	while(1)
	{
	encoder();
	}
		/*while(1)
		{	
		
		ADCSRA |= 0x40;			// start the adc conversion on AN0
		while(ADCSRA & 0x40);
		temp = ADC;

		gotoXy(1,1 );			//set the cursor to 1 column of 1st row
		prints("ADC = ");		
		integerToLcd(temp);		// print adc value to the lcd

		
		_delay_ms(300);
		
	
	 }*/
}
