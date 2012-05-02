/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 2 (connect to TX of other device)
 * TX is digital pin 3 (connect to RX of other device)
 
 created back in the mists of time
 by Tom Igoe
 based on Mikal Hart's example
 
 This example code is in the public domain.
 
 */

#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3


SoftwareSerial mySerial(rxPin, txPin);

void setup()  
{
  Serial.begin(57600);
  Serial.println("Goodnight moon!");
  
  // define pin modes for tx, rx:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  //mySerial.println("Hello, world?");
}

void loop() // run over and over
{
  if (mySerial.available())
    Serial.write(mySerial.read());
 // if (Serial.available())
 //   mySerial.write(Serial.read());
}
