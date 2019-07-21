#ifndef _LED_H_
#define _LED_H_

#include "Arduino.h"

class LED
{
private:
  byte ledPin;
  unsigned long prevBlinkTime;
  byte blinkCount;

  unsigned long prevPeriod;
  unsigned int period;

public:
  LED(byte pin, bool state);
  LED(byte pin, bool state, unsigned int pulseWidth, unsigned int period, byte blinkTimes = 1);
  ~LED();
  byte getPin();
  void on();
  void off();
  bool getState();
  void disattach();
  void blink(unsigned int pulseWidth, byte blinkTimes);
  void resetBlink();
  void periodBlink(unsigned int pulseWidth, byte blinkTimes, unsigned int period);
  // the minimum pulseWidth is 100ms, period should larger than pulseWidth*blinkTimes*2

  void powerOn();
  void powerOff();
  void timerRunning();
  void snoozed();
  void walking();
};

#endif
