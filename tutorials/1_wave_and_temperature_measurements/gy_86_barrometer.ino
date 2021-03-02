#include "Wire.h"
#include "I2Cdev.h" //   Get these libraries from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino
#include "MPU6050.h" //  ^
#include <MS5611.h> // Get this library from https://github.com/jarzebski/Arduino-MS5611

MPU6050 mpu;
MS5611 baro;

double temp;
long pressure;
double altitude;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Serial.println("Initializing I2C devices...");
  mpu.setI2CMasterModeEnabled(false);
  mpu.setI2CBypassEnabled(true) ;
  mpu.setSleepEnabled(false);
  mpu.initialize();
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  while (!baro.begin(MS5611_ULTRA_HIGH_RES)) {
    Serial.println("MS5611 connection unsuccessful, check wiring!");
    delay(500);
  }
}

void loop() {
  temp = baro.readTemperature(true);
  pressure = baro.readPressure(true);
  altitude = baro.getAltitude(pressure);
  printResults();
  delay(200);
}

void printResults(){
  Serial.print("Pressure hPa: "); Serial.print(pressure);
  Serial.print("  Altitude m: "); Serial.print(altitude);
  float tempC = temp / 340.00 + 36.53;
  Serial.print("  Temp °C: "); Serial.println(tempC);
}
