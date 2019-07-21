# Arduino-Pomodoro

## To-do List:

- [x] Finished LED module
- [x] Test each part of existing module
- [x] Connect all modules to work together
- [x] Run simple test to see the functionality
- [x] Run a complete Test
- [x] Battery Monitor Circuit
- [ ] Crystal frequency change to 1MHz, need to modify millis() function

## Flash Light
1. Power On: LED on
2. Power off: LED off
3. Working: LED flash once per 400 ms
4. Walking: LED flash once per 800 ms
5. Snoozed: LED flash twice per 2500 ms

## Time:
1. Working: 20 mins
- worktime in Arduino-Pomodoro.ino and readTimeSetting function in timer.cpp
2. Snoozed: 5 mins
- snoozetime in Arduino-Pomodoro.ino
3. Vibrate Overtime: 1 min
- vibratetime in Arduino-Pomodoro.ino

## Test Procedure
1. test work period for multiple time. Check each time the working period is achieved as setting
2. test snooze period for multiple time. Check each time the snooze period is achieved as setting
3. test overtime period for multiple time. Check each time the overtime period is achieved as setting
4. check working flow is running as described in flow chart
5. check working time change button can work as setting

