// Find wave power
// Wave power formula:  P = 0.5 height ** 2 * period // https://en.wikipedia.org/wiki/Wave_power 

#include "Wire.h"
#include "I2Cdev.h" //   Get these libraries from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino
#include "MPU6050.h" //  ^
#include <MS5611.h> // Get this library from https://github.com/jarzebski/Arduino-MS5611

MPU6050 mpu;
MS5611 baro;

long pressure;
double altitude, min_height, max_height, wave_height, mid_point, smudge_factor, wave_power;
byte escaped, started;
unsigned long period_start, period_end;
float avg_period = -1;


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
  unsigned long start_time = millis();
  pressure = baro.readPressure(true);
  altitude = baro.getAltitude(pressure);
  max_height = altitude;
  min_height = altitude;

  //  for 5 seconds
  while(millis() - start_time < 5000){
    pressure = baro.readPressure(true);
    altitude = baro.getAltitude(pressure);
    if (altitude < min_height) min_height = altitude;
    if (altitude > max_height) max_height = altitude;
  }
  mid_point = (max_height + min_height)/2.0;
  wave_height = (max_height - mid_point) / 2.0;
  smudge_factor = wave_height * 0.15;
  Serial.print("Wave Height m: "); Serial.print(wave_height);
  
  start_time = millis();
  //  for 5 seconds 
  while(millis() - start_time < 5000){
    pressure = baro.readPressure(true);
    altitude = baro.getAltitude(pressure);
    //    if within a range of 30% of wave height from the mid point
    //    start the timer else stop it
    if (altitude < mid_point + smudge_factor && altitude > mid_point - smudge_factor){
      if ( !started){
        period_start = millis();
        started = true;
      }
      else{
        if ( escaped ){
          // if it has started and escaped and is now returning
          period_end = millis();
          started = false;
          escaped = false;
          // if the variable has already been assigned
          // use its previous value and new value to work out avg
          if(avg_period != -1){
            avg_period = (avg_period + (period_end-period_start)*2)  / 2.0;
          }
          // assign it
          else{
            avg_period =  (period_end-period_start)*2; 
          }

        }
      }
    }
    else{
      escaped = true;
    } 
  }
  Serial.print("  Period s: "); Serial.print(avg_period/1000);
  wave_power = (0.5 * wave_height * wave_height * avg_period / 1000);
  Serial.print("  Wave Power kW/m: "); Serial.println(wave_power); 
}



