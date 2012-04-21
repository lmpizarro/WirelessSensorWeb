
#define assignTXByte(X) ((X) > (9) ? (X + 55) : (X + 48))

static const char asciiCode [16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

//unsigned int TXByte;    // Value sent over UART when Transmit() is called
unsigned int ADCValue;  // Measured ADC Value
bool ADCDone;                   // ADC Done flag

#define SensorId     12
#define codFunc       3


void TransmitADCValue (){
  unsigned int cksum = 0;

  /*************************************************************/  
  // Transmitir Comienzo  de Mensaje ':'
  /*************************************************************/  
   TXByte = ':';
   cksum = cksum + TXByte;
   Transmit();

  /*************************************************************/  
  //  Transmitir el SensorId
  /*************************************************************/  

   TXByte = (SensorId >> 4) & 0x000F;
   TXByte  = asciiCode[TXByte];
   cksum = cksum + TXByte;
   Transmit();                                           // Send


  TXByte = SensorId & 0x000F;
  TXByte  = asciiCode[TXByte];
  cksum = cksum + TXByte;
  Transmit();                                           // Send


  /*************************************************************/  
  // Transmitir el codFunc 
  /*************************************************************/  
  TXByte = (codFunc >> 4) & 0x000F;
  TXByte  = asciiCode[TXByte];
  cksum = cksum + TXByte;
  Transmit();                                           // Send


  TXByte = codFunc & 0x000F;
  TXByte  = asciiCode[TXByte];
  cksum = cksum + TXByte;
  Transmit();                                           // Send


  /*************************************************************/  
  // Transmitir el valor del ADC
  /*************************************************************/
  TXByte = (ADCValue>>12) & 0x000F;
  TXByte  = asciiCode[TXByte];
  cksum = cksum + TXByte;
  Transmit();                                           // Send

  TXByte = (ADCValue>>8) & 0x000F;
  TXByte  = asciiCode[TXByte];
  cksum = cksum + TXByte;
  Transmit();                                           // Send

  TXByte = (ADCValue >> 4) & 0x000F;
  TXByte  = asciiCode[TXByte];
  cksum = cksum + TXByte;
  Transmit();                                           // Send

  TXByte = ADCValue & 0x000F;
  TXByte  = asciiCode[TXByte];
  cksum = cksum + TXByte;
  Transmit();                                           // Send


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

