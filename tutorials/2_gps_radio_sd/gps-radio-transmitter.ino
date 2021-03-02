#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

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
  
  Serial.println("Setting up radio");
  //  Setup transmitter radio
  radio.begin();
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.setChannel(0x76);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  radio.enableDynamicPayloads();
  radio.powerUp();
  Serial.println("Starting to send");
}


void loop() {
  while (ss.available() > 0){
    if (gps.encode(ss.read())){
      getInfo();
      radio.write(&gpsData, sizeof(gpsData));
    }
  }
} 



void getInfo(){
  if (gps.location.isValid()){
    gpsData.longitude = gps.location.lng();
    gpsData.latitude = gps.location.lat();
  }
  else{
    gpsData.longitude = 0.0;
    gpsData.latitude = 0.0;
  }
  if (gps.date.isValid()){
    gpsData.date = gps.date.value();
  }
  else{
    gpsData.date = 0;
  }
  if (gps.time.isValid()){
    gpsData.time = gps.time.value();
  }
  else{
    gpsData.time = 0;
  }
}



