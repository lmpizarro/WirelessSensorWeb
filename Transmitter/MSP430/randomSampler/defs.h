#ifndef __DEFS
#define __DEFS


unsigned int TXByte;  // Value sent over UART when Transmit() is called
unsigned int ADCValue;

unsigned long int sampleTimeSec = 20;
const unsigned char deviceID = 35;
const unsigned long int minTime = 5000;
unsigned long int dlyCC1 = 60000;

#define     TXD            BIT1                      // TXD on P1.1
#define     APC220_CTL     BIT0  // P1.0 al Pin 3 Sleep del transceiver APC220


#include  "adc10.c"
#include  "serialTransmit.c"
#include  "transmitADCValue.c"

void setVloClk (void);
void setClockTrans();

#endif
