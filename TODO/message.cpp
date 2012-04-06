#include "analogInput.h"


// Por ahora no la uso
unsigned char lowNibbleToAscci (unsigned char p)
{
  return (asciiCode[p]);
}


unsigned char getDeviceId(void)
{   
/* Device-ID is encoded on pins PB6:PA3:PB2:PB1 */
   return (deviceId); 
}


unsigned char calcCheckSum (unsigned char *buffer, unsigned int cant) 
{
  unsigned char cks;
  cks = 10;
  return (cks);
}


void buildTxMsg(void)
{
static char     msgCount, devId, devIdL, devIdH;
unsigned int    cks;

    // Comienzo de Frame
    buffer[0] = 0x3A; // ascci code ':';
    // Identificacion de dispositivo
    devId = getDeviceId();
    devIdL = devId & 0x0f;
    devIdH = (devId >> 4)&0x0f;
    buffer[1] = asciiCode[devIdH];
    buffer[2] = asciiCode[devIdL];
    // Codigo de funcion "03" transmision de registro
    buffer[3] = 0x30; // ascii code '0'
    buffer[4] = 0x33; // ascii code '3'
    // Transmito un registro por ahora
    // dispH nibble 1
    //unsigned char aux = getDispH();
    buffer[5] = asciiCode[(getDispH()>>4)&0x0f];
    // dispH nibble 0
    buffer[6] = asciiCode[getDispH()&0x0F];
    //aux = getDispL();
    // dispL nibble 1
    buffer[7] = asciiCode[(getDispL()>>4)&0x0f];
    // dispL nibble 0
    buffer[8] = asciiCode[getDispL()&0x0F];
    buffer[9] =buffer[5];
    buffer[10] =buffer[6];
    buffer[11] =buffer[7];
    buffer[12] =buffer[8];
    buffer[13] =buffer[5];
    buffer[14] =buffer[6];
    buffer[15] =buffer[7];
    buffer[16] =buffer[8];

    cks = calcCheckSum(buffer, 9);
    // Dos caracteres de cksum
    buffer[17] = 0x30;
    buffer[18] = 0x31;
    // Dos caracteres cr/lf de fin de frame
    buffer[19] = 0x0D;
    buffer[20] = 0x0A;
   
}
