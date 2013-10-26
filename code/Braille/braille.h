#ifndef Braille_h
#define Braille_h

#include "Arduino.h"

class Braille
{
	public:
		Braille(byte pin, byte speed);
		void sendZero();
		void sendDot();
		void sendMsg(char *str);
		void sendChar(char c);
};
#endif