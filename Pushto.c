#include <avr/io.h>
#include <stdio.h>

#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "encoder.h"
#include "keypad.h"
    


void system_init (void)
{	
	/*Inicjalizacja przerwań zewnetrznych*/
	MCUCR |=(1<<ISC00) | (1<<ISC10);	//ustawienie przerwan na zmiane na INT0 i INT1
	GICR |= (1<<INT0) | (1<<INT1); //wlaczenie zewnetrznych przerwan na INT0 i INT1
	
	/*inicjalizacja LCD*/
	LCD_DIR = 0xFF;		//Ustawienie pinow dla wyswietlacza LCD

	/*inicjalizacja encoderow*/
	EN_DIR = 0b00000000; //Ustawienie pinow dla encoderow
	EN_PORT = 0b00001111; //pullupy dla encoderow

	encoder1.maskA=0b00000100;
	encoder1.maskB=0b00000001;
	encoder1.count=0;
	encoder2.maskA=0b000001000;
	encoder2.maskB=0b000000010;
	encoder2.count=0;
	
	//############# Timer1 16bit config ####################
	TCCR1A |= 0;   // not required since WGM11:0, both are zero (0)
 	TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);   // Mode = CTC, Prescaler = 64
	OCR1A = 31250;   // timer compare value 1Hz - 31250 
	TIMSK|=(1<<OCIE1A); //enable compare reg A interrupt
	
    	sei(); // enable global interrupts

}

ISR(TIMER1_COMPA_vect) //obsluga przerwania dla timera
{

}

ISR(INT0_vect) //przerwanie dla INT0 dla encodera1
{
	direction(&encoder1);
}

ISR(INT1_vect) //przerwanie dla INT1 dla encodera2
{
	direction(&encoder2);
}


int main(void)
{

	//unsigned int temp;
	system_init();
	lcdInit();
	prints("PUSHTO");
	while(1)
	{
	gotoXy(0,0);
	prints("E1=");
	integerToLcd(encoder1.count);
	prints(" E2=");
	integerToLcd(encoder2.count);
	//gotoXy(0,1);
	//integerToLcd(keypad());

	}

}
