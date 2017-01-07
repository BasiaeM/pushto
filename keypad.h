#ifndef __keypad_h_
#define __keypad_h_

#include <avr/io.h>
#include <util/delay.h>

#define KB_PORT     PORTB
#define KB_DIR      DDRB
#define KB_PIN  	PINB

//flagi
//#define KB_ACP 0x80;
#define KB_NEW 0x40 //wprowadzanie nowego obiektu
#define KB_CAL 0x20 //kalibracja
#define KB_H 0x08 //flaga znaku godzin H
#define KB_M 0x04  //flaga znaku minut M

/*kody klawiszy

	0b11101110 //1
	0b11011110 //2
	0b10111110 //3
	0b01111110 //A
	0b11101101 //4
	0b11011101 //5
	0b10111101 //6
	0b01111101 //B
	0b11101011 //7
	0b11011011 //8
	0b10111011 //9
	0b01111011 //C
	0b11100111 //"*"
	0b11010111 //0
	0b10110111 //#
	0b01110111 //D

*/

struct Key 
{
	char result; // ostatni nacisniety klawisz
	char buf[16]; //ciag znakow
	int i; //pozycja w buforze
	char flags; 
} keypad_A;

char keypad(struct Key *klaw);
void keypad_proc(struct Key *klaw);

#endif