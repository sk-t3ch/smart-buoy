#include "Wire.h"
#include "I2Cdev.h" //   Get these libraries from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino
#include "MPU6050.h" //  ^
#include "HMC5883L.h" // ^
 
MPU6050 mpu;
HMC5883L mag;

int16_t mx, my, mz;

// Find the declination where you are from http://www.magnetic-declination.com
//                  -14°     59'            
float declination = (-14.0 - (59.0 / 60.0)) * (PI/180); 

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Serial.println("Initializing I2C devices...");
  mpu.setI2CMasterModeEnabled(false);
  mpu.setI2CBypassEnabled(true) ;
  mpu.setSleepEnabled(false);
  mpu.initialize();
  mag.initialize();
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  Serial.println(mag.testConnection() ? "HMC5883L connection successful" : "HMC5883L connection failed");

}

void loop() {
  mag.getHeading(&mx, &my, &mz);
  printResults();
  delay(200);
}

void printResults(){
  float heading = atan2(my, mx);
  heading += declination;
  if (heading < 0) heading += 2 * PI;
  if (heading > 2 * PI) heading -= 2 * PI;
  heading *= 180/M_PI;
  
  Serial.print("Heading °:"); 
  Serial.println(heading);
}


