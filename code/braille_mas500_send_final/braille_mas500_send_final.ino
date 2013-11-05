class Braille
{
  public:
    Braille(byte pin, byte speed);
    void sendZero(int pinIndex);
    void sendDot(int pinIndex);
    void sendChar(char c);
};

  char debug = ' ';
  byte brailleOn[6]; //array of 'on' bits
  int OUTpin = 11; //pins IR-LED is connected to

  byte _speed;	// Speed in WPM
  byte _pin;	// Pin to beep or toggle
  byte _one;	// 1 == beep to speaker, 0 == toggle pin high and low
  byte _zero;
  int _dotlen;	// Length of dot (1)
  int _zerolen; //Length of a zero (0)
  byte _brailleCodepage[] = {	//
    B011011, //! 33
    B000100, //" 34
    B010111, //# 35
    B111001, //$ 36
    B110001, //% 37
    B111011, //& 38
    B000010, //'39
    B101111, //( 40
    B011111, //) 41
    B100001, //* 42
    B010011, //+ 43
    B000001,  //, 44    
    B000011, //- 45
    B010001, //. 46
    B010010, /// 47
    B000111, //0 48
    B001000, //1 49
    B001010, //2 50
    B001100, //3 51
    B001101, //4 52
    B001001, //5 53
    B001110, //6 54
    B001111, //7 55
    B001011, //8 56
    B000110, //9 57
    B100101, //: 58
    B000101, //; 59
    B101001, //< 60
    B111111, //= 61
    B010110, //> 62
    B110101, //? 63
    B010000, //@ 64
    B100000, //ASCII Glyph A 65
    B101000, //B 66
    B110000, //C 67
    B110100, //D 68
    B101000, //E 69
    B111000, //F 70
    B111100, //G 71
    B101100, //H 72
    B011000, //I 73
    B011100, //J 74
    B100010, //K 75
    B101010, //L 76
    B110010, //M 77
    B110110, //N 78
    B100110, //O 79
    B111010, //P 80
    B111110, //Q 81
    B101110, //R 82
    B011010, //S 83
    B011110, //T 84
    B100011, //U 85
    B101011, //V 86
    B011101, //W 87
    B110011, //X 88
    B110111, //Y 89
    B100111, //Z 90
    B011001, //[ 91
    B101101, //\92
    B111101, //] 93
    B010100, //^ 94
    B010101 //_ 95  
    };
  

Braille::Braille(byte pin, byte speed)
{
  // Save values for later use
  _pin = pin;
  _speed = speed;

  // Calculate the length of dash and dot
  _dotlen = (1200/_speed);
  _zerolen = (1200/_speed);
  //_zerolen =  (3*_dotlen);

  // Set the pin to output mode

  //}
}

void Braille::sendZero(int pin)
{
  //digitalWrite(LEDpins[pinIndex], LOW);
  noTone(pin);
}

void Braille::sendDot(int pin)
{
  //digitalWrite(LEDpins[pinIndex], HIGH);
  tone(pin, 38000);
  //noTone(LEDpins[pinIndex]);
}

void Braille::sendChar(char c)
{
  int _i = 0;
  byte _BrailleBinaryRep;
  byte userInput;
  byte mask = B100000;

  // Send space
  if (c == ' ') {
    return ;
  }
  else {
    userInput = (byte) c;
    Serial.print(userInput);
    if (userInput >= 97 && userInput <= 122) {
      userInput -= 32;  
    }

    _i = (userInput - 33);
    _BrailleBinaryRep = _brailleCodepage[_i];
    //Serial.print(_BrailleBinaryRep);
    Serial.write(_BrailleBinaryRep);
    delay(1000);
    //Serial.print(_BrailleBinaryRep);
  }

  /*for (int j = 0; j < 6; j++) {
    int k = -(j) + 5;
    //int LED = k;
    
    brailleOn[k] = (_BrailleBinaryRep & (mask >> j)) != 0;
    Serial.print(brailleOn[k]);
    Serial.write(brailleOn[k]);
    delay(1000);*/
    /*if (debug == 'X') {
      //Serial.print("the bit mask result is: ");
      //Serial.println(_BrailleBinaryRep & (mask >> j));
      //Serial.print("the value of j is: ");
      //Serial.println(j);
      //Serial.print("the value of k is: ");
      //Serial.println(k); 
    }   
    if (brailleOn[k] == 1) {
      if (debug == 'X') {
          //Serial.print("LED #: ");
          //Serial.println(k);
      }    
          if (debug == 'X') {
            //Serial.print("1");
          }
	  sendDot(OUTpin);
    } else {
          if (debug == 'X') {
            //Serial.print("0");
          }
	  sendZero(OUTpin);
    }*/
 // }  
}

Braille braille(OUTpin, 3);
char i = 'A';
void setup() {

  Serial.begin(1200);
    pinMode(OUTpin, OUTPUT);
    tone(11,38000);  
  
}

void loop() {
  char fragmentIn;
  
  while(Serial.available()) {
    fragmentIn = Serial.read();
    //i++;
    //if (debug == 'X') {
      //Serial.print("You entered: ");
      //Serial.print(fragmentIn);
    //}
    braille.sendChar(fragmentIn);
    
  }
}

    

