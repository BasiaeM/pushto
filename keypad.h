#ifndef __keypad_h_
#define __keypad_h_

#include <avr/io.h>
#include <util/delay.h>

#define KB_PORT     PORTC
#define KB_DIR      DDRC
#define KB_PIN  	PINC

char keypad(void);
#endif