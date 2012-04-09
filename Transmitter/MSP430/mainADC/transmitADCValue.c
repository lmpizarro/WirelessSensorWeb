
#define assignTXByte(X) ((X) > (9) ? (X + 55) : (X + 48))

char asciiCode [16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
char bufferTX [32];

unsigned int TXByte;    // Value sent over UART when Transmit() is called
unsigned int ADCValue;  // Measured ADC Value
bool ADCDone;                   // ADC Done flag

#define SensorId     12
#define codFunc       3


void TransmitADCValue (){
  unsigned char cksum = 0;

  /*************************************************************/  
 // Transmitir Comienzo  de Mensaje '!'
  /*************************************************************/  
   TXByte = ':';
   Transmit();
   cksum = cksum + TXByte;

  /*************************************************************/  
  //  Transmitir el SensorId
  /*************************************************************/  

  TXByte = (SensorId >> 4) & 0x000F;
  TXByte  = asciiCode[TXByte];
  Transmit();                                           // Send
  cksum = cksum + TXByte;


  TXByte = SensorId & 0x000F;
  TXByte  = asciiCode[TXByte];
  Transmit();                                           // Send
  cksum = cksum + TXByte;


  /*************************************************************/  
  // Transmitir el codFunc 
  /*************************************************************/  
  TXByte = (codFunc >> 4) & 0x000F;
  TXByte  = asciiCode[TXByte];
  Transmit();                                           // Send
  cksum = cksum + TXByte;


  TXByte = codFunc & 0x000F;
  TXByte  = asciiCode[TXByte];
  Transmit();                                           // Send
  cksum = cksum + TXByte;


  /*************************************************************/  
  // Transmitir el valor del ADC
  /*************************************************************/
  TXByte = (ADCValue>>12) & 0x000F;
  TXByte  = asciiCode[TXByte];
  Transmit();                                           // Send
  cksum = cksum + TXByte;

  TXByte = (ADCValue>>8) & 0x000F;
  TXByte  = asciiCode[TXByte];
  Transmit();                                           // Send
  cksum = cksum + TXByte;

  TXByte = (ADCValue >> 4) & 0x000F;
  TXByte  = asciiCode[TXByte];
  Transmit();                                           // Send
  cksum = cksum + TXByte;

  TXByte = ADCValue & 0x000F;
  TXByte  = asciiCode[TXByte];
  Transmit();                                           // Send
  cksum = cksum + TXByte;


  /*************************************************************/  
  // Transmitir el cksum
  /*************************************************************/  

  TXByte = (cksum >> 4) & 0x000F;
  TXByte  = asciiCode[TXByte];
  Transmit();                                           // Send

  TXByte = cksum & 0x000F;
  TXByte  = asciiCode[TXByte];
  Transmit();                                           // Send

  /*************************************************************/  
   // Transmitir Fin de Mensaje '!'
  /*************************************************************/  
   TXByte = '!';
   Transmit();
}

