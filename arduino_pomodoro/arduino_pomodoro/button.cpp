#include "button.h"
#include "Arduino.h"

Button::Button(byte pin, bool lastButtonState, bool buttonState)
{
	this->pin = pin;
	this->lastButtonState = lastButtonState;
	this->buttonState = buttonState;
	this->lastDebounceTime = 0;
}

Button::~Button()
{
	disattach();
}

void Button::disattach()
{
	digitalWrite(pin, LOW);
	pinMode(pin, INPUT);
}

bool Button::isRiseEdge()
{
	bool res = false;
	unsigned long debounceDelay = 50;
	int reading = digitalRead(pin);

	if (reading != lastButtonState)
	{
		lastDebounceTime = millis();
	}

	if (abs(millis() - lastDebounceTime) > debounceDelay)
	{
		if (reading != buttonState)
		{
			buttonState = reading;
			if (buttonState == HIGH)
			{
				res = true;
			}
		}
	}
	lastButtonState = reading;
	return res;
}

bool Button::isFallEdge()
{
	bool res = false;
	unsigned long debounceDelay = 50;
	int reading = digitalRead(pin);

	if (reading != lastButtonState)
	{
		lastDebounceTime = millis();
	}

	if (abs(millis() - lastDebounceTime) > debounceDelay)
	{
		if (reading != buttonState)
		{
			buttonState = reading;
			if (buttonState == LOW)
			{
				res = true;
			}
		}
	}
	lastButtonState = reading;
	return res;
}