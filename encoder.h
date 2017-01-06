#ifndef __encoder_h_
#define __encoder_h_

#include <avr/io.h>

#define EN_PORT		PORTB
#define EN_DIR		DDRB
#define EN_PIN 		PINB

void encoder(void);
#endif