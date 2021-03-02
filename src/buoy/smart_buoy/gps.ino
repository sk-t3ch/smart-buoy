#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
// Arduino -> GPS
// d4->tx, d3->rx
SoftwareSerial ss(4, 3);

void setup_gps(){
  ss.begin(9600);
}

void get_gps_data(){
  unsigned long start_time = millis();
  // try for 30 seconds and break if all is valid early
  while ( millis()-start_time < 30000 ) {
    while (ss.available() > 0) {
      if (gps.encode(ss.read())) {
        if (gps.location.isValid()){
          measurement_1.val_1 = gps.location.lat();
          measurement_1.val_2 = gps.location.lng();
        }
        if (gps.date.isValid() && gps.time.isValid()) {
            measurement_1.time = gps.time.value();
            measurement_2.time = gps.time.value();
            measurement_1.date = gps.date.value();
            measurement_2.date = gps.date.value();
        }
      }
    }
    delay(10);
    if( gps.location.isValid() && gps.date.isValid() && gps.time.isValid() ){
      break;
    }
  }
}
