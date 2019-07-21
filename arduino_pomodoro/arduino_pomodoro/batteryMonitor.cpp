#include "batteryMonitor.h"
#include "param.h"
#include "Arduino.h"

BatteryMonitor::BatteryMonitor(byte batteryEnablePin, byte batteryMonitorPin, byte batteryLEDPin, unsigned long monitorPeriod)
{
  this->batteryEnablePin = batteryEnablePin;
  this->batteryMonitorPin = batteryMonitorPin;
  this->batteryLEDPin = batteryLEDPin;
  pinMode(batteryEnablePin, OUTPUT);
  pinMode(batteryMonitorPin, INPUT);
  pinMode(batteryLEDPin, OUTPUT);
  digitalWrite(this->batteryEnablePin, HIGH);
  digitalWrite(this->batteryLEDPin, LOW);
  this->prevTime = millis();
  this->startOfPeriod = this->prevTime;
  this->monitorPeriod = monitorPeriod;
  this->isMonitoring = false;
}

BatteryMonitor::~BatteryMonitor()
{
}

void BatteryMonitor::checkBatteryStatus()
{
  unsigned long curtTime = millis();
  if (curtTime - this->prevTime > monitorPeriod)
  {
    digitalWrite(this->batteryEnablePin, LOW);
    if (!this->isMonitoring)
    {
      this->isMonitoring = true;
      this->startOfPeriod = millis();
    }
    if (curtTime - this->startOfPeriod > 20)
    {
      bool batteryStat = digitalRead(this->batteryMonitorPin);
      if (batteryStat == LOW)
      {
        digitalWrite(this->batteryLEDPin, HIGH);
      }
      else
      {
        digitalWrite(this->batteryLEDPin, LOW);
      }
      digitalWrite(this->batteryEnablePin, HIGH);
      this->prevTime = millis();
      this->isMonitoring = false;
    }
  }
}