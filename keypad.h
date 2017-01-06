#ifndef __keypad_h_
#define __keypad_h_

#include <avr/io.h>
#include <util/delay.h>

#define KB_PORT     PORTA
#define KB_DIR      DDRA
#define KB_PIN  	PINA

char keypad(void);
#endif