#ifndef _BATTERYMONITOR_H_
#define _BATTERYMONITOR_H_

#include "Arduino.h"
#include "led.h"

class BatteryMonitor
{
private:
  unsigned long prevTime;
  unsigned long monitorPeriod;
  unsigned long startOfPeriod;
  byte batteryEnablePin;
  byte batteryMonitorPin;
  byte batteryLEDPin;
  bool isMonitoring;

public:
  BatteryMonitor(byte batteryEnablePin, byte batteryMonitorPin, byte batteryLEDPin, unsigned long monitorPeriod = 1000);
  ~BatteryMonitor();
  void checkBatteryStatus();
};

#endif