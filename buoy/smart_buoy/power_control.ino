#include <DS3232RTC.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void setup_power_control(){
  Wire.begin();
  ina219.begin();
  ina219.setCalibration_32V_1A();
}

void set_new_alarm(){
  int wait_time = get_wait_time_from_voltage();
  measurement_1.val_5 = wait_time;
  
  tcaselect(4);
  RTC.alarmInterrupt(ALARM_1, true);
  RTC.squareWave(SQWAVE_NONE);
  setTime(0, 0, 0, 1, 1, 1970);
  RTC.set(now());
  
  // set new alarm
  RTC.setAlarm(ALM1_MATCH_MINUTES, 0, wait_time, 0, 1);
}

int get_wait_time_from_voltage(){
  float shuntvoltage = ina219.getShuntVoltage_mV();
  float busvoltage = ina219.getBusVoltage_V();
  float loadvoltage = busvoltage + (shuntvoltage / 1000);
  measurement_1.val_3 = ina219.getCurrent_mA();
  measurement_1.val_4 = loadvoltage;

  // Samsung 18650 % capacity at a given voltage
  // batt_voltages            0.0, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 4.1, 4.2, 4.5
  // batt_percentages           0,   0,   9,  22,  52,  64,  75,  84,  93, 100, 100
  int wait_time;
  if (loadvoltage < 3.6) wait_time = 15;
  else if (loadvoltage < 3.8) wait_time = 10;
  else if (loadvoltage < 4.0) wait_time = 6;
  else if (loadvoltage < 4.1) wait_time = 3;
  else wait_time = 2;
  
  return wait_time;
}

void turn_off(){
  // clear old alarm flag - turning off system
  RTC.alarm(ALARM_1);
}

