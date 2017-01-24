#include "pushto_lib.h"

	//do wrzucenia gdzieś????????????????????????????????????????????????????????
	float ralk= ((13.0*15.0)+48.0*(15.0/60.0)+32.0*(15.0/3600.0))*(PI/180.0); //rektascencja gwiazdy alkaid
	float dalk= (49.0+18.0/60)*(PI/180.0);										//deklinacja

void kalibracja(struct Enc *enk1, struct Enc *enk2, struct Telescope *tel) //enkoder1 - wysokosc, enkoder2 - obrot
{
    /*funkcja do kalibracji pushtu, okreslenie polozenia ukladu rownikowego wzgledem ukladu horyzontalnego*/

	float halk;	//wysokość alkaida
	float talk; //kąt godzinny

	gotoXy(0,0);
	prints("Goto zenit-> C");
	while(keypad(&keypad_A)!=0b01111011){} //oczekuj na C
	enk1->count=EN1_RANGE/4; //ustawienie wysokosci zenitu
	
	gotoXy(0,0);
	prints("Goto polaris-> C");
	while(keypad(&keypad_A)!=0b01111011){} //oczekuj na C
	enk2->count=0; //ustawienie 0 enkodera na azymucie=0
	tel->h_pol=(enk1->count*2.0*PI)/EN1_RANGE; //szerokość geograficzna h_pol, rad

	gotoXy(0,0);
	prints("Goto alkaid -> C");
	while(keypad(&keypad_A)!=0b01111011){} //oczekuj na C
	
	halk=(((EN1_RANGE/4)-enk1->count)/EN1_RANGE)*2.0*PI; //przeliczenie zmierzonej wysokości na radiany
	talk= acos(((sin(halk)-sin(tel->h_pol)*sin(dalk))/(cos(dalk)*cos(tel->h_pol))));
	if(enk2->count*2.0*PI/EN2_RANGE<=PI) talk+=PI; //wynikajace z zakresu funkcji asin

	//w radianach????????????????????????????????????
	tel->time=talk+ralk; //ustawianie zegara
	lcd_clr();

}

void nowy_cel(struct Key *klaw, struct Telescope *tel)
{
    /*funkcja obslugujaca wprowadzanie nowego celu, 
    zawiera wskazowki dotyczace formatu wprowadzania,
    po wprowadzeniu konwertuje znaki z bufora klawiatury na liczby
    reprezentujace deklinacje i rektastencje zadana*/

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
    tel->re_zad = (15*h+15/60.0*m+15/3600.0*s)*(PI/180.0); //z przeliczeniem na radiany

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
    tel->de_zad = (h+m/60.0+s/3600.0)*(PI/180.0); //w radianach
 	
 	keypad_clr_buf();
 	lcd_clr();
	klaw->flags='\0'; //czszczenie flag
}

void obliczenie_nastaw(struct Telescope *tel)
{
    /*funkcja obliczajaca nastawy dla enkoderow na podstawie wprowadzonych(zadanych)
     deklinacji(wys_zad) i rektastencji(obr_zad)
     oraz czasu ktory minal od momentu kalibracji */

	float o_time = tel->time-tel->re_zad; //kąt godzinny obiektu
	tel->wys_obl= asin(sin(tel->de_zad)*sin(tel->h_pol)+cos(tel->de_zad)*cos(tel->h_pol)*cos(o_time));
	tel->obr_obl= atan(cos(tel->de_zad)*sin(o_time)/(-sin(tel->de_zad)*cos(tel->h_pol)+cos(tel->de_zad)*sin(tel->h_pol)*cos(o_time)));
		if(tel->obr_obl<=0) tel->obr_obl+=2*PI;

	tel->wys_obl=(tel->wys_obl*EN1_RANGE)/(2.0*PI); //przeliczenie na obroty
	tel->obr_obl=(tel->obr_obl*EN2_RANGE)/(2.0*PI);
}