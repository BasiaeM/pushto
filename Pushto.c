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
	MCUCR = MCUCR | 0b00001111;	//ustawienie przerwan na narastajacych zboczach na INT0 i INT1
	LCD_DIR = 0xFF;		//Ustawienie pinow dla wyswietlacza LCD
	EN_DIR = 0b00000000; //Ustawienie pinow dla encoderow
	EN_PORT = 0b00000011; //pullupy dla encoderow

	encoder1.maskB=0b00000010;
	encoder1.count=0;
	encoder2.maskB=0b00001000;
	encoder2.count=0;
	//ADCSRA=0X00;		// CODE for ADC demo (optional)
	//ADMUX = 0x40;
	//ADCSRA = 0x87;
}

int main(void)
{

	//unsigned int temp;
	system_init();
	lcdInit();
	prints("PUSHTO");
	while(1)
	{
	direction(& encoder1);
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
