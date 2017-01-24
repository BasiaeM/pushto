#ifndef __pushto_lib_h_
#define __pushto_lib_h_

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdio.h>
#include "keypad.h"
#include "lcd.h"
#include "encoder.h"

#define PI 3.14159265
#define ralk ((13.0*15.0)+48.0*(15.0/60.0)+32.0*(15.0/3600.0))*(PI/180.0) //rektascencja gwiazdy alkaid
#define dalk (49.0+18.0/60)*(PI/180.0)	

struct Telescope{
	int time;
	short int update;
	float de_zad; //deklinacja i rektascencja wprowadzane przez uzytkownika (uklad rownikowy)
	float re_zad;
	float wys_obl; //wys i obrot obliczone dla enkoderow (uklad horyzontalny)
	float obr_obl;

	float h_pol; //szerokość geograficzna
} telescope_A;

void kalibracja(struct Enc *enk1, struct Enc *enk2, struct Telescope *tel); //enkoder1 - wysokosc, enkoder2 - obrot
void nowy_cel(struct Key *klaw, struct Telescope *tel);  //wprowadzanie nowego celu
void obliczenie_nastaw(struct Telescope *tel); //aktualizacja wartosci zadanych dla enkoderow
#endif