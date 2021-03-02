#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(8, 7); // CE, CSN

struct dataStruct{
  double latitude;
  double longitude;
  unsigned long date;
  unsigned long time;
}gpsData;

void setup() {
  Serial.begin(115200);
  //  Setup receiver radio
  radio.begin();
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL);
  radio.setChannel(0x76);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  radio.enableDynamicPayloads();
  radio.powerUp();
}


void loop() {
  if (radio.available()) {
    radio.read(&gpsData, sizeof(gpsData));
    Serial.print("Location: ");
    Serial.print(gpsData.latitude, 6);
    Serial.print(", ");
    Serial.print(gpsData.longitude, 6);
    Serial.print("  Date: ");
    Serial.print(gpsData.date);
    Serial.print("  Time: ");
    Serial.print(gpsData.time);
    Serial.println();

  }
} 


