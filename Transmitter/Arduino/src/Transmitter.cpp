#include <Arduino.h>
#include <SoftwareSerial.h>

#include "Message.cpp"

#include "dht11.h"
#include "dht11.cpp"

#define analogPinSeed   0
#define analogPin   1

//SoftwareSerial mySerial(2, 3);

dht11 DHT11;
Message msg = Message ();

#define DHT11PIN 4

void setup()  
{
  /*  Para comunicarse por USB */
  Serial.begin(9600);
  //Serial.println("Goodnight moon!");
  //Serial.println(buffer);

  // set the data rate for the SoftwareSerial port
  //mySerial.begin(4800);
  
  // Inicializa el generador de numeros aleatorios con una lectura
  // a un conversor analogico sin conectar.
  randomSeed(analogRead(analogPinSeed));
}

void loop() // run over and over
{
    long randNumber;
   
    int chk = DHT11.read(DHT11PIN);

   // Adquire el valor del registro
   // Arma el mensaje
   msg.buildTxMsg(254,analogRead(analogPin));
   
  // Envia el mensaje
   Serial.write(msg.buffer,21);


   //
   //mySerial.write(buffer,16);
   //


   //
   // genera aleatoriamente un tiempo de espera para retransmitir
   //
   randNumber = random(5000,10000);
   // Retardo 
   delay (randNumber); 
   // Nueva semilla de numero aleatorio
   randomSeed(analogRead(0));
}
