
#include "lcd16.h"
 #include <util/delay.h>
void lcdcmd(unsigned char Data)
{

PORTD &= ~RS; //because sending command
PORTD  &=~EN;
PORTD &=~RW;
PORTD &= 0x0f;

PORTD |= ((Data ) & 0xf0);
PORTD &=~RW;
PORTD  |=EN;
_delay_ms(2);
PORTD  &=~EN;

PORTD &= 0x0f;

PORTD  |= ((Data<<4) &  0xf0);
PORTD  |=EN;
_delay_ms(2);
PORTD  &=~EN;


}
void lcdData(unsigned char l)
{
PORTD |=RS;  //because sending data
PORTD &=~RW;
PORTD  &=~EN;
PORTD &= 0x0f;
PORTD |=((l ) & 0xf0);
PORTD &=~RW;
PORTD  |=EN;
_delay_ms(2);
PORTD  &=~EN;
PORTD &= 0x0f;
PORTD  |= ((l<<4) &  0xf0);
PORTD  |=EN;
_delay_ms(2);
PORTD  &=~EN;



}

void lcdInit(void)
{
PORTD &=~RS;
PORTD  &=~EN;
PORTD &=~RW;
PORTD |= 0x30;
_delay_ms(40);
PORTD  |=EN;
PORTD  &=~EN;
_delay_ms(5);
PORTD  |=EN;
PORTD  &=~EN;
_delay_ms(5);
PORTD  |=EN;
PORTD  &=~EN;
_delay_ms(2);

PORTD &= 0x20;
PORTD  |=EN;
PORTD  &=~EN;
lcdcmd(0x28);   //set data length 4 bit 2 line
_delay_ms(50);
lcdcmd(0x0E);   // set display on cursor on blink on
_delay_ms(50);
lcdcmd(0x01); // clear lcd
_delay_ms(50);
lcdcmd(0x06);  // cursor shift direction
_delay_ms(50);
lcdcmd(0x80);  //set ram address
_delay_ms(50);
}



void prints(const char *s)
  {

    while (*s)
      {
	 lcdData(*s);
	 s++;
      }
  }

void gotoXy(unsigned char  x,unsigned char y)
{
 if(x<40)
 {
  if(y) x |= 0x40;
  x |=0x80;
  lcdcmd(x);
  }

}
void integerToLcd(int integer )
{

unsigned char thousands,hundreds,tens,ones;
thousands = integer / 1000;

    lcdData(thousands + 0x30);

	 hundreds = ((integer - thousands*1000)-1) / 100;

	lcdData( hundreds + 0x30);
tens=(integer%100)/10;

	lcdData( tens + 0x30);
	ones=integer%10;

	lcdData( ones + 0x30);
}
