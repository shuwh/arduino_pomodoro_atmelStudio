#ifndef _TIMER_H_
#define _TIMER_H_

#include "Arduino.h"

class Timer
{
private:
  unsigned int timer;
  unsigned int threshold;
  unsigned int step;
  unsigned long prevTime;

public:
  Timer(unsigned int threshold, unsigned int step = 1000); // the total threshold is threshold * step / 1000
  ~Timer();

  unsigned int getTimer();
  void setTimer(unsigned int timer);
  unsigned int getThreshold();
  void setThreshold(unsigned int threshold);
  void run();
  void reset();
  void readTimeSetting(int timePin);
  bool isOvertime();
  bool isThresholdChanged(int timePin);
};

#endif