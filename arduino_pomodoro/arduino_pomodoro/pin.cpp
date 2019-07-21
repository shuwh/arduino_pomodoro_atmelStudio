#include "pin.h"
// #include "button.h"
// #include "motor.h"
// #include "led.h"
#include "Arduino.h"

// Button *main_button, *snooze_button;
// Motor *motor;
// LED *led;

void hardwareSetup()
{
  pinMode(timePin, INPUT);

  // pinMode(motorPin, OUTPUT);
  // pinMode(ledPin, INPUT);

  // main_button = new Button(main_button_pin);
  // snooze_button = new Button(snooze_button_pin);

  // motor = new Motor(motorPin);

  // led = new LED(ledPin, LOW);
}
