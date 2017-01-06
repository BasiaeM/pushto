#include "keypad.h"

char i;
unsigned char result;
char keypad(void) 
 {
result=0;
KB_DIR =0b11110000; //wymuszenie zer dla wszystkich kolumn
KB_PORT=0b00001111;
_delay_ms(200);
result=KB_PIN;

//odczyt wierszy
KB_DIR =0b00001111; //wymuszenie zer dla wszystkich wierszy
KB_PORT=0b11110000;
_delay_ms(200);
result = result | KB_PIN; 

//uzyskanie kodu skanowania 
switch
( result) {
case 0b11101110     : i= 1; break; //1
case 0b11011110     : i= 2 ; break; //2
case 0b10111110     : i= 3; break; //3
case 0b01111110     : i= 4; break; //A
case 0b11101101     : i= 5; break; //4
case 0b11011101     : i= 6; break; //5
case 0b10111101     : i= 7; break; //6
case 0b01111101     : i= 8; break; //B
case 0b11101011     : i= 9; break; //7
case 0b11011011     : i= 10; break; //8
case 0b10111011     : i= 11; break; //9
case 0b01111011     : i= 12; break; //C
case 0b11100111     : i= 13; break; //*
case 0b11010111     : i= 14; break; //0
case 0b10110111     : i= 15; break; //#
case 0b01110111     : i= 16; break; //D
default:              
     i= 0;
}
return i;
}