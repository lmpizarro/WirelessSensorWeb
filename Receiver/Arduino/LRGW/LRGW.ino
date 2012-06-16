#include <SoftwareSerial.h>


#define RXPin     2
#define TXPin     3

SoftwareSerial mySerial(RXPin, TXPin); // RX, TX


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  mySerial.begin(9600);
 
}

  //const String dilocal = "di";
  //const String dolocal = "do";
  //const String ailocal = "ai";
  //const String aolocal = "ao";
  
  
  //String dilocalt  = "#dil01!";
  //String dilocaltb = "#dil0";
  //String dolocalt  = "#dol021!";
  //String ailocalt  = "#ail03!";
  //String aolocalt  = "#aor111123!";
  const String startMsg    = "#";
  const String endMsg      = "!";

  String funcS      ="";
  String chanS      =""; 
  int remote        = 0;
  int chan          = 0;
     
//
// Verifica longitud
// Verfica Comienzo
// Verifica Fin
// Determina func
// Determina si local / remoto
// Determina Canal en String
//
int testMsg (String msg){
  if (msg.length() >= 7){
    if (msg.startsWith(startMsg)){
      if (msg.endsWith(endMsg)){
          funcS = msg.substring(1,3);
          chanS = msg.substring(4,6);
          if (msg[3]=='r') {remote = 1;}
          else {remote = 0;}
          return (1);
      }else return(-1);
    }else return(-1);
  }
  else return(-1);
}

//
//  Convierte el canal en String a numerico
//
int getChan (){
    if (isDigit(chanS[0])){
      if (isDigit(chanS[1])){
        return ((char(chanS[0])-48)*10 +(char(chanS[1])-48));
      }
      else{return(-1);}
    }else{return(-1);}
}


void doRemote (){
   Serial.print ("DoRemote ");
   Serial.println(remote);
}

void doLocal (){
 Serial.print ("Local ");
 chan = getChan();
 Serial.println(funcS);
 Serial.println(chan);
}


// Buffer de recepcion a PC
// Byte recibido
char thisChar;
// Mensaje recibido en String
String msg;
int i = 0;
void loop() {
  if (Serial.available() > 0) {
    thisChar = Serial.read();
    if (thisChar != 10){
      msg = msg + thisChar;
      i++;
    } else { // RECEIVED CHAR = LF
      msg.trim();
      if (testMsg(msg)){
        if (remote) { 
          doRemote();
          mySerial.println(msg);
        }else {
          doLocal ();chan= 0; msg = ""; i = 0;thisChar=0;
        } // DOLOCAL
      } else {chan= 0; msg = ""; i = 0;thisChar=0;}        
    }  
  } // SerialAvailable
   
} // LOOP
