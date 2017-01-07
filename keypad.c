#include "keypad.h"

char keypad(struct Key *klaw) 
 {
	klaw->result=0;
	KB_DIR =0b11110000; //wymuszenie zer dla wszystkich kolumn
	KB_PORT=0b00001111;
	_delay_ms(100);
	klaw->result = KB_PIN;

	//odczyt wierszy
	KB_DIR =0b00001111; //wymuszenie zer dla wszystkich wierszy
	KB_PORT=0b11110000;
	_delay_ms(100);
	klaw->result |= KB_PIN; 

	return klaw->result; //ostatnio wcisniety
}

void keypad_proc(struct Key *klaw)
{

	switch (klaw->result) // akcja dla ostanio wcisnietego klawisza
	{
		//klawisze funkcyjne
		
		//case 0b01111110     : ; break; //A - potwierdzenie (accept)
		case 0b01111101     : klaw->flags |= KB_NEW; break; //B - wprowadzanie nowego obiektu
		case 0b01111011     : klaw->flags |= KB_CAL ; break; //C - kalibracja (calibration)

		case 0b11100111     : { //* H
			if(!(klaw->flags & KB_H))
				klaw->buf[klaw->i]='H';
			klaw->flags |= KB_H;

		} break; 
		case 0b10110111     :{ //# M
			if(!(klaw->flags & KB_M))
				klaw->buf[klaw->i]='M';
			klaw->flags |= KB_M;
	
		}break; 

		case 0b01110111     : { //D - czyszczenie
			for(int i=0;i<16;i++) //czyszczenie bufora
				klaw->buf[i]='\0'; 
			//czyszczenie flag
			klaw->flags &= ~KB_H;
			klaw->flags &= ~KB_M;
			//czyszczenie wskaznika buforu
			klaw->i = 0;
		}; break; 
		
		
		//klawisz numeryczny     
		case 0b11101110     : klaw->buf[klaw->i]='1'; break; //1
		case 0b11011110     : klaw->buf[klaw->i]='2'; break; //2
		case 0b10111110     : klaw->buf[klaw->i]='3'; break; //3
		case 0b11101101     : klaw->buf[klaw->i]='4'; break; //4
		case 0b11011101     : klaw->buf[klaw->i]='5'; break; //5
		case 0b10111101     : klaw->buf[klaw->i]='6'; break; //6
		case 0b11101011     : klaw->buf[klaw->i]='7'; break; //7
		case 0b11011011     : klaw->buf[klaw->i]='8'; break; //8
		case 0b10111011     : klaw->buf[klaw->i]='9'; break; //9
		case 0b11010111     : klaw->buf[klaw->i]='0'; break; //0
		//default:
	}
	klaw->i=0;
	klaw->result=0xFF;

}