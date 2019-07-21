#include "led.h"
#include "Arduino.h"

LED::LED(byte pin, bool state)
{
  this->ledPin = pin;
  pinMode(this->ledPin, OUTPUT);
  digitalWrite(this->ledPin, state);

  unsigned long curtTime = millis();
  this->blinkCount = 0;
  this->prevBlinkTime = curtTime;

  this->prevPeriod = curtTime;
}

LED::~LED()
{
  disattach();
}

void LED::on()
{
  digitalWrite(this->ledPin, HIGH);
}

void LED::off()
{
  digitalWrite(this->ledPin, LOW);
}

bool LED::getState()
{
  return digitalRead(this->ledPin);
}

void LED::disattach()
{
  digitalWrite(this->ledPin, LOW);
  pinMode(this->ledPin, INPUT);
}

void LED::blink(unsigned int pulseWidth, byte blinkTimes)
{
  if (this->blinkCount < blinkTimes)
  {
    unsigned long curTime = millis();
    if (curTime - this->prevBlinkTime > pulseWidth)
    {
      if (this->getState() == LOW)
      {
        this->on();
      }
      else
      {
        this->off();
        this->blinkCount++;
      }
      this->prevBlinkTime = curTime;
    }
  }
}

void LED::resetBlink()
{
  this->blinkCount = 0;
}

void LED::periodBlink(unsigned int pulseWidth, byte blinkTimes, unsigned int period)
{
  pulseWidth = pulseWidth < 100 ? 100 : pulseWidth;
  period = period < pulseWidth * blinkTimes * 2 ? pulseWidth * blinkTimes * 2 : period;
  unsigned long curtTime = millis();
  if (curtTime - this->prevPeriod > period)
  {
    this->resetBlink();
    this->prevPeriod = curtTime;
    this->prevBlinkTime = curtTime - (pulseWidth + 10); // sync  on/off period with blink period
  }
  this->blink(pulseWidth, blinkTimes);
}

void LED::powerOn()
{
  this->on();
}

void LED::powerOff()
{
  this->off();
}

void LED::timerRunning()
{
  this->periodBlink(200, 1, 400);
}

void LED::walking()
{
  this->periodBlink(400, 1, 800);
}

void LED::snoozed()
{
  this->periodBlink(200, 2, 2500);
}
