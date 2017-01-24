#include <avr/io.h>
#include <stdio.h>

#define F_CPU 2000000UL //kwarc 2MHz
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "encoder.h"
#include "keypad.h"
#include "pushto_lib.h"
    

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
	encoder1.count=0; //----------------------------enkodery start 0 
	encoder2.maskA=0b000001000;
	encoder2.maskB=0b000000010;
	encoder2.count=0;
	encoder1.range=EN1_RANGE;
	encoder2.range=EN2_RANGE;

	//inicjalizacja klawiatury
	keypad_A.i=0; //zerowanie wskaznika buforu
	keypad_A.flags='\0';
	keypad_A.last_result = 0xFF;

	telescope_A.update=0; //flaga aktualizacja nastaw

	//konfiguracja timera TIMER1
	TCCR1A |= 0;   // not required since WGM11:0, both are zero (0)
 	TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);   // Tryb = CTC, Dzielnik = 64
	OCR1A = 31165;   // licznik porownawczy 1Hz - 31250, dla sekundy gwiazdowej -31165
	TIMSK|=(1<<OCIE1A); //włączenie przerwań na porownanie z rejestrem A
	
    	sei(); //globalne włączenie przerwań

}

ISR(TIMER1_COMPA_vect) //obsluga przerwania dla timera
{
	telescope_A.time+=0.000004835; //czas gwiazdowy w radianach
	telescope_A.update++;
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
	system_init();
	lcdInit();
	while(1)
	{

		keypad(&keypad_A); //odczyt klawiatury
		keypad_proc(&keypad_A); //przetwarzanie znakow

		if(keypad_A.flags & KB_NEW)
		{
			nowy_cel(&keypad_A,&telescope_A);
			keypad_A.flags &= ~KB_NEW;
		}

		if(keypad_A.flags & KB_CAL)
		{
			kalibracja(&encoder1,&encoder2,&telescope_A); // funkcja z pushto_lib
			keypad_A.flags &= ~KB_CAL;
		}

		if(keypad_A.flags & KB_CLR)
		{
			lcd_clr();
			keypad_A.flags &= ~KB_CLR;
		}

		if(telescope_A.update==10)
		{
			obliczenie_nastaw(&telescope_A); //funkcja na obliczenie nastaw, co 10sek (patrz ISR(TIMER1_COMPA_vect))
			telescope_A.update=0;
		}


		if(keypad_A.i > 14)
			keypad_A.i=0;

	}

}
