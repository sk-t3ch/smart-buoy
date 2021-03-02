#include <DS3232RTC.h>
#include <Adafruit_INA219.h>
#include <Wire.h> 

int led = LED_BUILTIN; 

// INA219 - Power Monitor
Adafruit_INA219 ina219;

  
void setup() {
  Wire.begin();
  pinMode(led, OUTPUT);
  
  // initialise INA219 - Power Monitor
  ina219.begin();
  ina219.setCalibration_32V_1A();
}

void loop() {
  digitalWrite(led, HIGH);
  delay(3000);
  reset_alarm();
}

void reset_alarm(){
  RTC.alarmInterrupt(ALARM_1, true);
  RTC.squareWave(SQWAVE_NONE);
  setTime(0, 0, 0, 0, 0, 1970); 
  RTC.set(now());
  int wait_time = get_wait_time_from_voltage();
  // set new alarm
  RTC.setAlarm(ALM1_MATCH_MINUTES, 0, wait_time, 0, 0);
  // clear old alarm flag - turning off system
  RTC.alarm(ALARM_1);
}


int get_wait_time_from_voltage(){
  float shuntvoltage = ina219.getShuntVoltage_mV();
  float busvoltage = ina219.getBusVoltage_V();
  float loadvoltage = busvoltage + (shuntvoltage / 1000);

  // Samsung 18650 % capacity at a given voltage
  // batt_voltages            0.0, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 4.1, 4.2, 4.5
  // batt_percentages           0,   0,   9,  22,  52,  64,  75,  84,  93, 100, 100
  int wait_time;
  if (loadvoltage < 3.6) wait_time = 55;
  else if (loadvoltage < 3.8) wait_time = 25;
  else if (loadvoltage < 4.0) wait_time = 15;
  else if (loadvoltage < 4.1) wait_time = 10;
  else wait_time = 3;
  
  return wait_time;
}
