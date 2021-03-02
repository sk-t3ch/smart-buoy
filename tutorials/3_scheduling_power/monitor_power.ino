#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;
float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float power_mW = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
      delay(1);
  }
  ina219.begin();
  ina219.setCalibration_32V_1A();
}

void loop() {
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA);  Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW);    Serial.println(" mW");
  Serial.println();
  delay(1000);
}
