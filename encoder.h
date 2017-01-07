#ifndef __encoder_h_
#define __encoder_h_

#include <avr/io.h>

#define EN_PORT		PORTD
#define EN_DIR		DDRD
#define EN_PIN 		PIND

struct Enc 
{
	unsigned char maskA;
	unsigned char maskB; //maska do sprawdzania, czy na danej nozce jest stan wysoki - jedynka na danej nodze
	int count;			//licznik obrotow enkodera
} encoder1, encoder2;
/*funkcja sprawdzajaca w ktora strone jest wykonywany obrot i zmieniajaca licznik encodera*/
void direction(struct Enc *danyEncoder); 
#endif