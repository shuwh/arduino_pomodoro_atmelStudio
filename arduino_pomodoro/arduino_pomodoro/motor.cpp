#include "motor.h"
#include "Arduino.h"

Motor::Motor(int pin, bool state)
{
  this->motorPin = pin;
  this->state = state;
  pinMode(this->motorPin, OUTPUT);
  digitalWrite(this->motorPin, LOW);
}

Motor::~Motor()
{
  digitalWrite(this->motorPin, LOW);
  pinMode(this->motorPin, INPUT);
}

void Motor::start()
{
  this->state = HIGH;
  digitalWrite(this->motorPin, HIGH);
}

void Motor::stop()
{
  this->state = LOW;
  digitalWrite(this->motorPin, LOW);
}

void Motor::reverse()
{
  if (this->state == HIGH)
  {
    this->stop();
  }
  else
  {
    this->start();
  }
}