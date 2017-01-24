#include "encoder.h"

void direction(struct Enc *danyEncoder)
{
	/*funkcja wykonywana po przyjściu przerwania (zmiany stanu nóżki enkodera)
	zmieniająca determinująca kierunek obrotu i odpowiednio
	inkrementująca licznik enkodera*/

	if (EN_PIN & danyEncoder->maskA)		//A zmianilo stan na wysoki
	{
		if(EN_PIN & danyEncoder->maskB)
			danyEncoder->count-=1;
		else
			danyEncoder->count+=1;
	}

	else									//A zmienilo stan na niski
	{
		if(EN_PIN & danyEncoder->maskB)
			danyEncoder->count+=1;
		else
			danyEncoder->count-=1;
	}

	if (danyEncoder->count >=danyEncoder->range) //zerowanie po pełnym obrocie
	{
		danyEncoder->count=0; 
}
}

