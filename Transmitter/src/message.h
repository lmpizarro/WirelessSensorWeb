#ifndef Message_H
#define Message_H

unsigned char lowNibbleToAscci (unsigned char p);
unsigned char getDeviceId(void);
unsigned char calcCheckSum (unsigned char *buffer, unsigned int cant);
void buildTxMsg(void);


unsigned char asciiCode [16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

unsigned char    buffer[17];
unsigned char    deviceId = 254; //0xFE


#endif

