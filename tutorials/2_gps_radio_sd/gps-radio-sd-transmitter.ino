#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SD.h>

TinyGPSPlus gps;


SoftwareSerial ss(4, 3);
RF24 radio(8, 7); // CE, CSN

struct dataStruct{
  double latitude;
  double longitude;
  unsigned long date;
  unsigned long time;
}gpsData;

void setup() {
  Serial.begin(115200);
  ss.begin(9600);

  //  Setup transmitter radio
  radio.begin();
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.setChannel(0x76);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  radio.enableDynamicPayloads();
  radio.powerUp();

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
      sendInfo();
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

void sendInfo(){
  radio.write(&gpsData, sizeof(gpsData));
}


