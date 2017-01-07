#include "encoder.h"

void direction(struct Enc *danyEncoder)
{
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

}

