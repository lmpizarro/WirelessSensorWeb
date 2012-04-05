#ifndef Dispositivo_H
#define Dispositivo_H


// Para guardar el valor de la variable fisica
// Se supone que no tiene más de 16 bits 
unsigned char dispL;
unsigned char dispH;

#define analogPin   1

void getDispValue ();

unsigned char getDispL ();
unsigned char getDispH ();

#endif
