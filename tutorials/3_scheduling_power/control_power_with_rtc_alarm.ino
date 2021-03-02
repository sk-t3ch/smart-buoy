#include <DS3232RTC.h>
#include <Wire.h> 

int led = LED_BUILTIN; 

void setup() {
  Serial.begin(115200);
  Wire.begin();
  pinMode(led, OUTPUT);
}

void loop() {
  
  digitalWrite(led, HIGH);
  delay(3000);
  reset_alarm();
}

void reset_alarm(){
    Wire.beginTransmission(0x70);
  Wire.write(1 << 6);
  Wire.endTransmission();
  RTC.alarmInterrupt(ALARM_1, true); // alarm is an output trigger
  RTC.squareWave(SQWAVE_NONE);
  //      0h 0m 0s 
  setTime(0, 0, 0, 1, 1, 1970); 
  RTC.set(now());
  // set new alarm
  RTC.setAlarm(ALM1_MATCH_SECONDS, 15, 0, 0, 1);
  // clear old alarm flag - turning off system
  RTC.alarm(ALARM_1);
}



