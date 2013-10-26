#include "Arduino.h"
#include "Braille.h"

  byte _speed;	// Speed in WPM
  byte _pin;	// Pin to beep or toggle
  byte _one;	// 1 == beep to speaker, 0 == toggle pin high and low
  byte _zero;
  int _dotlen;	// Length of dot (1)
  int _zerolen; //Length of a zero (0)
  byte _brailleCodepage[] = {	// 
    011011, //! 33
    000100, //" 34
    010111, //# 35
    111001, //$ 36
    110001, //% 37
    111011, //& 38
    000010, //'39
    101111, //( 40
    011111, //) 41
    100001, //* 42
    010011, //+ 43
    000001,  //, 44    
    000011, //- 45
    010001, //. 46
    010010, /// 47
    000111, //0 48
    001000, //1 49
    001010, //2 50
    001100, //3 51
    001101, //4 52
    001001, //5 53
    001110, //6 54
    001111, //7 55
    001011, //8 56
    000110, //9 57
    100101, //: 58
    000101, //; 59
    101001, //< 60
    111111, //= 61
    010110, //> 62
    110101, //? 63
    010000, //@ 64
    100000, //ASCII Glyph A 65
    101000, //B 66
    110000, //C 67
    110100, //D 68
    101000, //E 69
    111000, //F 70
    111100, //G 71
    101100, //H 72
    011000, //I 73
    011100, //J 74
    100010, //K 75
    101010, //L 76
    110010, //M 77
    110110, //N 78
    100110, //O 79
    111010, //P 80
    111110, //Q 81
    101110, //R 82
    011010, //S 83
    011110, //T 84
    100011, //U 85
    101011, //V 86
    011101, //W 87
    110011, //X 88
    110111, //Y 89
    100111, //Z 90
    011001, //[ 91
    101101, //\92
    111101, //] 93
    010100, //^ 94
    010101, //_ 95  
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
  delay(_zerolen);
  //digitalWrite(_pin, LOW);
  //delay(_dotlen);
}

void Braille::sendDot()
{
  digitalWrite(_pin, HIGH);
  delay(_dotlen);
  //digitalWrite(_pin, LOW);
  //delay(_dotlen);
}

void Braille::sendChar(char c)
{
  int _i = 0;
  byte _BrailleBinaryRep;
  byte mask = 1;

  // Send space
  if (c == ' ') {
    delay(_dotlen) ;
    return ;
  }
  else {
    _i = ((byte) c) - 33;
    _BrailleBinaryRep = _brailleCodepage[_i];
  }

  for (mask = 00000001; mask>0; mask <<= 1) {
    if (_BrailleBinaryRep & mask){
	  sendDot();
	}
	else{
	  sendZero();
	}
  }
}

void Braille::sendMsg(char *str)
{
  while (*str) {
    sendChar(*str++);
  }
}
 