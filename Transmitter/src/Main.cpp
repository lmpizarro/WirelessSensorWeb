#include <iostream>
using namespace std;


#include "Message.h"

char TR_IDENTIF = 254;

int main (void){
 
   Message msg = Message ();
   msg.buildTxMsg(254, 1022);
   cout << msg.buffer; 
}
