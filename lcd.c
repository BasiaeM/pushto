
#include "lcd.h"
#include <util/delay.h>

void lcdcmd(unsigned char Data)
{

LCD_PORT &= ~RS; //because sending command
LCD_PORT  &=~EN;
LCD_PORT &=~RW;
LCD_PORT &= 0x0f;

LCD_PORT |= ((Data ) & 0xf0);
LCD_PORT &=~RW;
LCD_PORT  |=EN;
_delay_ms(2);
LCD_PORT  &=~EN;

LCD_PORT &= 0x0f;

LCD_PORT  |= ((Data<<4) &  0xf0);
LCD_PORT  |=EN;
_delay_ms(2);
LCD_PORT  &=~EN;


}
void lcdData(unsigned char l)
{
LCD_PORT |=RS;  //because sending data
LCD_PORT &=~RW;
LCD_PORT  &=~EN;
LCD_PORT &= 0x0f;
LCD_PORT |=((l ) & 0xf0);
LCD_PORT &=~RW;
LCD_PORT  |=EN;
_delay_ms(2);
LCD_PORT  &=~EN;
LCD_PORT &= 0x0f;
LCD_PORT  |= ((l<<4) &  0xf0);
LCD_PORT  |=EN;
_delay_ms(2);
LCD_PORT  &=~EN;



}

void lcdInit(void)
{
LCD_PORT &=~RS;
LCD_PORT  &=~EN;
LCD_PORT &=~RW;
LCD_PORT |= 0x30;
_delay_ms(40);
LCD_PORT  |=EN;
LCD_PORT  &=~EN;
_delay_ms(5);
LCD_PORT  |=EN;
LCD_PORT  &=~EN;
_delay_ms(5);
LCD_PORT  |=EN;
LCD_PORT  &=~EN;
_delay_ms(2);

LCD_PORT &= 0x20;
LCD_PORT  |=EN;
LCD_PORT  &=~EN;
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
