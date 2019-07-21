#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "Arduino.h"

class Motor
{
private:
  int motorPin;
  bool state;

public:
  Motor(int pin, bool state = LOW);
  ~Motor();
  void start();
  void stop();
  void reverse();
};

#endif