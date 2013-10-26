#include <braille.h>

Braille braille(3,1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
  String stringIn = "";
  char fragmentIn;

  while(Serial.available()) {
    fragmentIn = Serial.read();
    stringIn.concat(fragmentIn);
    braille.sendChar(fragmentIn);
  }
/*
  if (stringIn != "")
  {
    braille.sendMsg(stringIn);
  }
*/  
}
