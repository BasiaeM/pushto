/* "led.c" - programik do testowania środowiska WinAVR */
/* układ ATmega 1MHz */
/* PB0,PB1 - diody LED; PD0 - przycisk */

#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>                

int main(void)
{
    DDRB  |= _BV(0)|_BV(1);
    PORTB |= _BV(0);
    PORTB &= ~_BV(1);
    DDRD  &= ~_BV(0);
    PORTD |=  _BV(0);

    while (1) 
    {
        PORTB ^=_BV(0);
        PORTB ^=_BV(1);
        
        _delay_ms((PIND & _BV(0))? 1000: 200);
    }
}