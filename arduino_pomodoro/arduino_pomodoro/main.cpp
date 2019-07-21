// include all the required files
// #include "condition.h"


// #define _DEBUG_

#include "Arduino.h"
#include "pin.h"
#include "button.h"
#include "led.h"
#include "motor.h"
#include "param.h"
#include "timer.h"
#include "batteryMonitor.h"

int state;

const int worktime = WORKINGTIME1; // seconds
const int vibratetime = VIBRATINGTIME;
const int snoozetime = SNOOZINGTIME;

Timer *workTimer;
Timer *vibrateTimer;
Timer *snoozeTimer;

Button *main_button;
Button *snooze_button;

Motor *motor;

LED *led;

BatteryMonitor *batteryMonitor;

bool is_start_button_pressed()
{
	return main_button->isRiseEdge();
}

bool is_pause_button_pressed()
{
	return main_button->isRiseEdge();
}

bool is_preset_time_reached()
{
	return workTimer->isOvertime();
}

bool is_time_setting_changed()
{
	return workTimer->isThresholdChanged(timePin);
}

bool is_walk_button_pressed()
{
	return main_button->isRiseEdge();
}

bool is_snooze_button_pressed()
{
	return snooze_button->isRiseEdge();
}

bool is_vibrating_overtime()
{
	return vibrateTimer->isOvertime();
}

bool is_snoozed_time_reached()
{
	return snoozeTimer->isOvertime();
}

void setup()
{
	// Library Setup
	hardwareSetup();

	#ifdef _DEBUG_
	// Serial Initialize
	Serial.begin(9600);
	Serial.println("Initialize Counter");
	#endif

	// State initialize
	state = IDLE;

	workTimer = new Timer(worktime, 1000);
	vibrateTimer = new Timer(vibratetime, 1000);
	snoozeTimer = new Timer(snoozetime, 1000);

	main_button = new Button(main_button_pin, LOW, LOW);
	snooze_button = new Button(snooze_button_pin, LOW, LOW);

	motor = new Motor(motorPin);

	led = new LED(ledPin, LOW);

	batteryMonitor = new BatteryMonitor(batteryEnablePin, batteryMonitorPin, batteryLEDPin, batteryMonitorPeriod);
}

void loop()
{
	switch (state)
	{
		case IDLE:
		#ifdef _DEBUG_
		Serial.println("IDLE");
		#endif
		led->powerOn();
		workTimer->readTimeSetting(timePin);
		batteryMonitor->checkBatteryStatus();
		if (is_start_button_pressed())
		{
			state = TIME_RUNNING;
		}
		break;
		case TIME_RUNNING:
		#ifdef _DEBUG_
		Serial.println("TIME_RUNNING");
		Serial.print("    Timer/Threshold: ");
		Serial.print(workTimer->getTimer());
		Serial.print("/");
		Serial.println(workTimer->getThreshold());
		#endif
		led->timerRunning();
		workTimer->run();
		if (is_pause_button_pressed())
		{
			state = IDLE;
		}
		else if (is_preset_time_reached())
		{
			state = VIBRATING;
		}
		else if (is_time_setting_changed())
		{
			state = IDLE;
		}
		else
		{
			state = TIME_RUNNING;
		}
		break;
		case VIBRATING:
		#ifdef _DEBUG_
		Serial.println("VIBRATING");
		Serial.print("    Timer/Threshold: ");
		Serial.print(vibrateTimer->getTimer());
		Serial.print("/");
		Serial.println(vibrateTimer->getThreshold());
		#endif
		led->powerOff();
		motor->start();
		vibrateTimer->run();
		if (is_walk_button_pressed())
		{
			state = WALKING;
		}
		else if (is_snooze_button_pressed())
		{
			state = SNOOZING;
		}
		else if (is_vibrating_overtime())
		{
			state = WALKING;
		}
		else
		{
			state = VIBRATING;
		}
		break;
		case WALKING:
		#ifdef _DEBUG_
		Serial.println("WALKING");
		#endif
		led->walking();
		motor->stop();
		workTimer->reset();
		vibrateTimer->reset();
		state = IDLE;
		break;
		case SNOOZING:
		#ifdef _DEBUG_
		Serial.println("SNOOZING");
		#endif
		motor->stop();
		snoozeTimer->reset();
		vibrateTimer->reset();
		state = SNOOZED;
		break;
		case SNOOZED:
		#ifdef _DEBUG_
		Serial.println("SNOOZED");
		Serial.print("    Timer/Threshold: ");
		Serial.print(snoozeTimer->getTimer());
		Serial.print("/");
		Serial.println(snoozeTimer->getThreshold());
		#endif
		led->snoozed();
		snoozeTimer->run();
		if (is_snoozed_time_reached())
		{
			state = VIBRATING;
		}
		else if (is_walk_button_pressed())
		{
			state = WALKING;
		}
		else
		{
			state = SNOOZED;
		}
		break;
	}
}


