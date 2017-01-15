#ifndef __pushto_lib_h_
#define __pushto_lib_h_

#include <avr/io.h>
#include <util/delay.h>
#include "keypad.h"
#include "lcd.h"
#include "encoder.h"

struct Telescope{
	int time;
	float wys_zad; //wys i obrot wprowadzane przez uzytkownika (uklad rownikowy)
	float obr_zad;
	float wys_obl; //wys i obrot obliczone dla enkoderow (uklad horyzontalny)
	float obr_obl;
} telescope_A;

void kalibracja(struct Enc *enk1, struct Enc *enk2, struct Telescope *tel); //enkoder1 - wysokosc, enkoder2 - obrot
void nowy_cel(struct Key *klaw, struct Telescope *tel); 
#endif