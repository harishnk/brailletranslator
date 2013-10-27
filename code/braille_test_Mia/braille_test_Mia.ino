class Braille
{
  public:
    Braille(byte pin, byte speed);
    void sendZero();
    void sendDot();
    //void sendMsg(char *str);
    void sendChar(char c);
};

  //array of 'on' bits
  char brailleOn[8];
  int LEDpins [] = {3, 5, 9, 10, 11, 13};

  byte _speed;	// Speed in WPM
  byte _pin;	// Pin to beep or toggle
  byte _one;	// 1 == beep to speaker, 0 == toggle pin high and low
  byte _zero;
  int _dotlen;	// Length of dot (1)
  int _zerolen; //Length of a zero (0)
  byte _brailleCodepage[] = {	// 
    B01101100, //! 33
    B00010000, //" 34
    B01011100, //# 35
    B11100100, //$ 36
    B11000100, //% 37
    B11101100, //& 38
    B00001000, //'39
    B10111100, //( 40
    B01111100, //) 41
    B10000100, //* 42
    B01001100, //+ 43
    B00000100,  //, 44    
    B00001100, //- 45
    B01000100, //. 46
    B01001000, /// 47
    B00011100, //0 48
    B00100000, //1 49
    B00101000, //2 50
    B00110000, //3 51
    B00110100, //4 52
    B00100100, //5 53
    B00111000, //6 54
    B00111100, //7 55
    B00101100, //8 56
    B00011000, //9 57
    B10010100, //: 58
    B00010100, //; 59
    B10100100, //< 60
    B11111100, //= 61
    B01011000, //> 62
    B11010100, //? 63
    B01000000, //@ 64
    B10000000, //ASCII Glyph A 65
    B10100000, //B 66
    B11000000, //C 67
    B11010000, //D 68
    B10100000, //E 69
    B11100000, //F 70
    B11110000, //G 71
    B10110000, //H 72
    B01100000, //I 73
    B01110000, //J 74
    B10001000, //K 75
    B10101000, //L 76
    B11001000, //M 77
    B11011000, //N 78
    B10011000, //O 79
    B11101000, //P 80
    B11111000, //Q 81
    B10111000, //R 82
    B01101000, //S 83
    B01111000, //T 84
    B10001100, //U 85
    B10101100, //V 86
    B01110100, //W 87
    B11001100, //X 88
    B11011100, //Y 89
    B10011100, //Z 90
    B01100100, //[ 91
    B10110100, //\92
    B11110100, //] 93
    B01010000, //^ 94
    B01010100 //_ 95  
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
  pinMode(_pin, OUTPUT);
}

void Braille::sendZero()
{
  digitalWrite(_pin, LOW);
  delay(300);
  //digitalWrite(_pin, LOW);
  //delay(_dotlen);
}

void Braille::sendDot()
{
  digitalWrite(_pin, HIGH);
  delay(300);
  digitalWrite(_pin, LOW);
  delay(300);
}

void Braille::sendChar(char c)
{
  int _i = 0;
  byte _BrailleBinaryRep;
  byte tempinput;
  byte mask = B1;

  // Send space
  if (c == ' ') {
    //delay(_dotlen) ;
    return ;
  }
  else {
    tempinput = (byte) c;
    if (tempinput >= 97 && tempinput <= 122) {
      tempinput -= 32;  
    }

    _i = (tempinput - 33);
    _BrailleBinaryRep = _brailleCodepage[_i];
    Serial.println("Braille mapped value is  ");
    Serial.println(_BrailleBinaryRep, BIN);

  }


  for (int j = 0; j < 8; j++) {
    int k = -(j) + 8;
    int LED = k;
    
    brailleOn[k] = (_BrailleBinaryRep & (mask << j)) != 0;

    if (brailleOn[k] == 1) {
          Serial.print("LED #: ");
          Serial.println(k);
	  sendDot();
    } else {
	  sendZero();
    }
  }
}

Braille braille(LEDpins[2], 3);

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
    braille.sendChar(fragmentIn);
  }
}

    

