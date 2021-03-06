#ifndef __lcd_h_
#define __lcd_h_


#include <avr/io.h>


#define RS  0x01
#define EN  0x04
#define RW  0x02
#define LCD_DIR DDRA
#define LCD_PORT PORTA

void gotoXy(unsigned char  ,unsigned char );
void lcdInit(void);
void lcdCmd(unsigned char);
void lcdData(unsigned char);
void prints(const char * message);
void lcd_clr(void);

void integerToLcd(int integer);
#endif
