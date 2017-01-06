#ifndef __encoder_h_
#define __encoder_h_

#include <avr/io.h>

#define EN_PORT		PORTB
#define EN_DIR		DDRB
#define EN_PIN 		PINB

struct Enc 
{
	unsigned char maskB; //maska do sprawdzania, czy na danej nozce jest stan wysoki - jedynka na danej nodze
	int count;			//licznik obrotow enkodera
} encoder1, encoder2;
/*funkcja sprawdzajaca w ktora strone jest wykonywany obrot i zmieniajaca licznik encodera*/
void direction(struct Enc *danyEncoder); 
#endif