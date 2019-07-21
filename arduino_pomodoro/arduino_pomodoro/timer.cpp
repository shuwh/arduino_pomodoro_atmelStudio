#include "timer.h"
#include "param.h"
#include "Arduino.h"

Timer::Timer(unsigned int threshold, unsigned int step)
{
  this->timer = 0;
  this->threshold = threshold;
  this->step = step;
  this->prevTime = millis();
}

Timer::~Timer()
{
}

unsigned int Timer::getTimer()
{
  return this->timer;
}

void Timer::setTimer(unsigned int timer)
{
  this->timer = timer;
}

unsigned int Timer::getThreshold()
{
  return this->threshold;
}

void Timer::setThreshold(unsigned int threshold)
{
  this->threshold = threshold;
}

void Timer::run()
{
  unsigned long curtTime = millis();
  if (curtTime - this->prevTime >= this->step)
  {
    this->timer++;
    this->prevTime = curtTime;
  }
}

void Timer::reset()
{
  this->setTimer(0);
}

void Timer::readTimeSetting(int timePin)
{
  bool timePinState = digitalRead(timePin);
  if (timePinState == HIGH)
  {
    this->setThreshold(WORKINGTIME1);
  }
  else
  {
    this->setThreshold(WORKINGTIME2);
  }
}

bool Timer::isOvertime()
{
  this->run();
  return this->getTimer() >= this->getThreshold();
}

bool Timer::isThresholdChanged(int timePin)
{
  unsigned int old = this->getThreshold();
  this->readTimeSetting(timePin);
  return old != this->getThreshold();
}
