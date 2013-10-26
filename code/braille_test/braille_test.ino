class Braille
{
	public:
		Braille(byte pin, byte speed);
		void sendZero();
		void sendDot();
		//void sendMsg(char *str);
		void sendChar(char c);
};

byte _speed;	// Speed in WPM
  byte _pin;	// Pin to beep or toggle
  byte _one;	// 1 == beep to speaker, 0 == toggle pin high and low
  byte _zero;
  int _dotlen;	// Length of dot (1)
  int _zerolen; //Length of a zero (0)
  byte _brailleCodepage[] = {	// 
    01101100, //! 33
    00010000, //" 34
    01011100, //# 35
    11100100, //$ 36
    11000100, //% 37
    11101100, //& 38
    00001000, //'39
    10111100, //( 40
    01111100, //) 41
    10000100, //* 42
    01001100, //+ 43
    00000100,  //, 44    
    00001100, //- 45
    01000100, //. 46
    01001000, /// 47
    00011100, //0 48
    00100000, //1 49
    00101000, //2 50
    00110000, //3 51
    00110100, //4 52
    00100100, //5 53
    00111000, //6 54
    00111100, //7 55
    00101100, //8 56
    00011000, //9 57
    10010100, //: 58
    00010100, //; 59
    10100100, //< 60
    11111100, //= 61
    01011000, //> 62
    11010100, //? 63
    01000000, //@ 64
    10000000, //ASCII Glyph A 65
    10100000, //B 66
    11000000, //C 67
    11010000, //D 68
    10100000, //E 69
    11100000, //F 70
    11110000, //G 71
    10110000, //H 72
    01100000, //I 73
    01110000, //J 74
    10001000, //K 75
    10101000, //L 76
    11001000, //M 77
    11011000, //N 78
    10011000, //O 79
    11101000, //P 80
    11111000, //Q 81
    10111000, //R 82
    01101000, //S 83
    01111000, //T 84
    10001100, //U 85
    10101100, //V 86
    01110100, //W 87
    11001100, //X 88
    11011100, //Y 89
    10011100, //Z 90
    01100100, //[ 91
    10110100, //\92
    11110100, //] 93
    01010000, //^ 94
    01010100 //_ 95  
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
  byte mask = 1;
  
  byte tempinput;

  // Send space
  if (c == ' ') {
    //delay(_dotlen) ;
    return ;
  }
  else {
    tempinput = (byte) c;
    Serial.println(tempinput);
    _i = (tempinput - 33);
    Serial.println("Printing array offset");
    Serial.println(_i);
    _BrailleBinaryRep = _brailleCodepage[_i];
    Serial.println("Braille mapped value is  ");
    Serial.println(_BrailleBinaryRep, BIN);
    Serial.println("Hardcoded access");
    Serial.println(_brailleCodepage[33], BIN);
  }

  for (mask = 00000001; mask>0; mask <<= 1) {
    byte temp;
    int loopcount = 1;
    temp = _BrailleBinaryRep & mask;
    if (temp){
          Serial.println("loop count in mask is ");
          Serial.print(loopcount);
          Serial.println("printing out mask ");
          Serial.print(temp, BIN);
	  sendDot();
	}
	else{
	  sendZero();
	}
  }
}

Braille braille(13,4);

void setup() {
  // put your setup code here, to run once:
  // put your setup code here, to run once:
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
  // put your main code here, to run repeatedly: 
  String stringIn = "";
  char fragmentIn;

  while(Serial.available()) {
    fragmentIn = Serial.read();
    //stringIn.concat(fragmentIn);
    braille.sendChar(fragmentIn);
    Serial.println("Printing fragment ");
    Serial.print(fragmentIn);
  }  
/*
  if (stringIn != "")
  {
    braille.sendMsg(stringIn);
  }
*/    
}
