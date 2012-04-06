#ifndef MESSAGE_H
#define MESSAGE_H

class Message 
{
public:

    //static const char  MAX_BUFFER = 32;
    static const unsigned  char  max_buffer = 32;

    unsigned char cantChar;
    unsigned char lowNibbleToAscii (unsigned char p);
    unsigned char calcCheckSum ();
    void buildTxMsg(unsigned char id, unsigned int value);
    
    // buffer de transmision
    unsigned char    buffer[max_buffer];

};
#endif
