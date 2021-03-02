/*
  SD card datalogger
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)
 */

#include <SPI.h>
#include <SD.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;

SoftwareSerial ss(4, 3);

struct dataStruct{
  double latitude;
  double longitude;
  unsigned long date;
  unsigned long time;
}gpsData;


void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  
  if (!SD.begin(5)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");

  File dataFile = SD.open("gps_data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Latitude, Longitude, Date, Time");
    dataFile.close();
  }
  else{
    Serial.println("nope cant open file");
  }
}


void loop() {
  while (ss.available() > 0){
    if (gps.encode(ss.read())){
      getInfo();
      printResults(); 
      saveInfo();
    }
  }
}


void getInfo(){
  if (gps.location.isValid()){
    gpsData.latitude = gps.location.lat();
    gpsData.longitude = gps.location.lng();
  }
  else{
    Serial.println("Invalid location");
  }
  if (gps.date.isValid()){
    gpsData.date = gps.date.value();
  }
  else{
    Serial.println("Invalid date");
  }
  if (gps.time.isValid()){
    gpsData.time = gps.time.value();
  }
  else{
    Serial.println("Invalid time");
  }
}


void printResults(){
  Serial.print("Location: ");
  Serial.print(gpsData.latitude, 6); Serial.print(", "); Serial.print(gpsData.longitude, 6);
  Serial.print("  Date: ");
  Serial.print(gpsData.date);
  Serial.print("  Time: ");
  Serial.print(gpsData.time);
  Serial.println();
}

void saveInfo(){
 File dataFile = SD.open("gps_data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.print(gpsData.latitude);
    dataFile.print(", ");
    dataFile.print(gpsData.longitude);
    dataFile.print(", ");
    dataFile.print(gpsData.date);
    dataFile.print(", ");
    dataFile.println(gpsData.time); 
    dataFile.close();
  }
  else{
    Serial.println("nope no datafile");
  }
}


