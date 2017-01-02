/*
 * Atmega_16_Learn.c
 *
 * Created: 9/23/2012 8:46:23 PM
 *  Author: Gaurav
 */ 

#include <avr/io.h>
#include <stdio.h>

#define F_CPU 1000000UL
#include <util/delay.h>
#include "lcd16.h"

unsigned char result;    	        // Liczba wprowadzona 
unsigned int i; 
#define KB_PORT     PORTA
#define KB_DIR      DDRA
#define KB_PIN  		PINA


void system_init (void)
{
	//DDRA = 0xFE;		//set the PORTA Direction Set every pin of PORTA as out except AN0 
	DDRD = 0xFF;		//set the PORTD Direction Set every pin of PORTD as out as our lcd on this
	
	//ADCSRA=0X00;		// CODE for ADC demo (optional)
	//ADMUX = 0x40;
	//ADCSRA = 0x87;
}

void keypad(void) 
 {
result=0;
KB_DIR =0b11110000; //wymuszenie zer dla wszystkich kolumn
KB_PORT=0b00001111;
_delay_ms(200);
result=KB_PIN;

//odczyt wierszy
KB_DIR =0b00001111; //wymuszenie zer dla wszystkich wierszy
KB_PORT=0b11110000;
_delay_ms(200);
result = result | KB_PIN; 

//uzyskanie kodu skanowania 
switch
( result) {
case 0b11101110     : i= 1; break; //1
case 0b11011110     : i= 2 ; break; //2
case 0b10111110     : i= 3; break; //3
case 0b01111110     : i= 4; break; //A
case 0b11101101     : i= 5; break; //4
case 0b11011101     : i= 6; break; //5
case 0b10111101     : i= 7; break; //6
case 0b01111101     : i= 8; break; //B
case 0b11101011     : i= 9; break; //7
case 0b11011011     : i= 10; break; //8
case 0b10111011     : i= 11; break; //9
case 0b01111011     : i= 12; break; //C
case 0b11100111     : i= 13; break; //*
case 0b11010111     : i= 14; break; //0
case 0b10110111     : i= 15; break; //#
case 0b01110111     : i= 16; break; //D
default:              
     i= 0;
}
		gotoXy(1,1 );			//set the cursor to 1 column of 1st row	
		integerToLcd(i);		// print adc value to the lcd
		_delay_ms(200);

}

int main(void)
{
	//unsigned int temp;

	
	system_init();
	lcdInit();

	prints("PushTo");
	while(1)
	{
	keypad();
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
