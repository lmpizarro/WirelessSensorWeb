

void readAI(){
   int aR;

   
   aR = analogRead(analogPin); 
   
   
   dispL = aR & 0x00FF ; 
   dispH = (aR >> 8) & 0x00FF;

   //dispL = 0xD4;
   //dispH = 0xF5;

}

unsigned char getDispL (){
  return (dispL);
}

unsigned char getDispH (){
  return (dispH);
}
