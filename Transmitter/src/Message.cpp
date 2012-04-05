#include "Message.h"

// 0x30-0x39  '0' a '9' 0x41-0x46  'A'-'F'
unsigned char Message::lowNibbleToAscii (unsigned char p)
{
  p = p & 0x0F;

  if (p<10)
     return (p+ 0x30);
  else
     return (p - 0x0A + 0x41);
}

unsigned char Message::calcCheckSum () 
{
  unsigned char cks;
  cks = 0;
  for (unsigned char i = 0; i < cantChar  ; i++)
    cks = cks + buffer[i];
  return (cks);
}

void Message::buildTxMsg(unsigned char id, unsigned int value)
{
    static char     msgCount, devId, devIdL, devIdH;
    unsigned int    cks;


    char dispL = value & 0x00FF ; 
    char dispH = (value >> 8) & 0x00FF;

    // Comienzo de Frame
    buffer[0] = 0x3A; // ascci code ':';
    // Identificacion de dispositivo
    devIdL = id;
    devIdH = id >> 4;
    buffer[1] = lowNibbleToAscii(devIdH);
    buffer[2] = lowNibbleToAscii(devIdL);
    // Codigo de funcion "03" transmision de registro
    buffer[3] = 0x30; // ascii code '0'
    buffer[4] = 0x33; // ascii code '3'
    // Transmito un registro por ahora
    // dispH nibble 1
    buffer[5] = lowNibbleToAscii(dispH>>4);
    // dispH nibble 0
    buffer[6] = lowNibbleToAscii(dispH);
    //aux = getDispL();
    // dispL nibble 1
    buffer[7] = lowNibbleToAscii(dispL>>4);
    // dispL nibble 0
    buffer[8]  = lowNibbleToAscii(dispL);
    buffer[9]  = buffer[5];
    buffer[10] = buffer[6];
    buffer[11] = buffer[7];
    buffer[12] = buffer[8];
    buffer[13] = buffer[5];
    buffer[14] = buffer[6];
    buffer[15] = buffer[7];
    buffer[16] = buffer[8];
    cantChar = 17;
    cks = calcCheckSum();
    // Dos caracteres de cksum
    buffer[17] = lowNibbleToAscii(cks>>4);
    buffer[18] = lowNibbleToAscii(cks);
    // Dos caracteres cr/lf de fin de frame
    buffer[19] = 0x0D;
    buffer[20] = 0x0A;
   
}
