#include "Wire.h"
#include "I2Cdev.h" //   Get these libraries from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino
#include "MPU6050.h" //  ^


MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Serial.println("Initializing MP6050...");
  mpu.initialize();
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  printResults();
  delay(10);
}

void printResults(){
  Serial.print("Acc (x,y,z) m/s/s: "); 
  Serial.print(ax); Serial.print(" "); 
  Serial.print(ay); Serial.print(" "); 
  Serial.print(az);
  Serial.print(" Gyro(x,y,z) °/s: "); 
  Serial.print(gx); Serial.print(" "); 
  Serial.print(gy); Serial.print(" "); 
  Serial.println(gz);
}
