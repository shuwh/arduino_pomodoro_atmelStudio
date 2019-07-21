#ifndef _BUTTON_H__
#define _BUTTON_H__

#include "Arduino.h"

class Button {
	private:
		byte pin;
		bool lastButtonState;
		bool buttonState;
		unsigned long lastDebounceTime;

	public:
		Button(byte pin, bool lastButtonState=LOW, bool buttonState=LOW);
		
		~Button();

		bool isRiseEdge();

		bool isFallEdge();

		void disattach();
};

#endif