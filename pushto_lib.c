#include "pushto_lib.h"

void kalibracja(struct Enc *enk1, struct Enc *enk2, struct Telescope *tel) //enkoder1 - wysokosc, enkoder2 - obrot
{
	gotoXy(0,0);
	prints("Goto polaris-> C");
	while(keypad(&keypad_A)!=0b01111011){} //oczekuj na C
	enk1->count=0; //ustawienie wysokosci 
	gotoXy(0,0);
	prints("Goto alkaid -> C");
	while(keypad(&keypad_A)!=0b01111011){} //oczekuj na C
	enk2->count=0; //ustawienie rektascencji
	tel->time=0;//zerowanie zegara
	lcd_clr();

}

void nowy_cel(struct Key *klaw, struct Telescope *tel)
{
	int h=0;
	int m=0;
	int s=0;
	//testy
	 gotoXy(0,1);
    integerToLcd(h);
    gotoXy(6,1);
    integerToLcd(m);
    gotoXy(11,1);
    integerToLcd(s);
    while(keypad(klaw)!=0b01111101){} //oczekuj na B


	keypad_clr_buf(); //czyszczenie bufora
	gotoXy(0,0);
	prints("podaj dekl i RA ");
	gotoXy(0,1);
	prints("format xHyMz ->B");
	while(keypad(klaw)!=0b01111101){} //oczekuj na B
	gotoXy(0,0);
	prints("oznaczenia:     ");
	gotoXy(0,1);
	prints("H(*) M(#)    ->B");
	while(keypad(klaw)!=0b01111101){} //oczekuj na B
	lcd_clr();

	gotoXy(0,0);
    prints("podaj RA     ->B");
    while(keypad(klaw)!=0b01111101) //oczekuj na B
    {
    	gotoXy(0,1);
    	keypad_proc(klaw);
    	prints(klaw->buf);
    }
    sscanf(klaw->buf,"%iH%iM%i",&h,&m,&s);
    //testy
    gotoXy(0,1);
    integerToLcd(h);
    gotoXy(6,1);
    integerToLcd(m);
    gotoXy(11,1);
    integerToLcd(s);
    while(keypad(klaw)!=0b01111101){} //oczekuj na B
    tel->obr_zad = 15*h+15/60.0*m+15/3600.0*s;

    keypad_clr_buf(); // czyszczenie bufora
    lcd_clr();
    h=0;m=0;s=0;
    klaw->flags &= ~KB_H;
	klaw->flags &= ~KB_M;
	gotoXy(0,0);
    prints("dekl H to st ->B");
    while(keypad(klaw)!=0b01111101) //oczekuj na B
    {
    	gotoXy(0,1);
    	keypad_proc(klaw);
    	prints(klaw->buf);
    }
    sscanf(klaw->buf,"%iH%iM%i",&h,&m,&s);
    tel->wys_zad = h+m/60.0+s/3600.0;
 	
 	keypad_clr_buf();
 	lcd_clr();
	klaw->flags='\0'; //czszczenie flag
}