#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 7); // CE, CSN

void setup_radio(){
  radio.begin();
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.openReadingPipe(1, 0xE8E8F0F0E1LL);
  radio.setChannel(0x76);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(4,15);
  radio.stopListening();
  radio.enableDynamicPayloads();
  radio.powerUp();
  Serial.println("setup radio");
}


void send_data(){
  //  we can only send 32 bytes at a time so we have to split up 
  // the measurements
  radio.write(&measurement_1, sizeof(measurement_1);
  radio.write(&measurement_2, sizeof(measurement_2);
}

