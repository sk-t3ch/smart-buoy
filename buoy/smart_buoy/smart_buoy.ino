/*
 * T3chFlicks - Smart Buoy Project
 * Find full tutorial including video, schematic, and links 
 * to components at https://t3chflicks.com/shop/kit/smart-buoy/
*/

#include <Wire.h>


struct measurement{
  byte index; // 1 byte
  unsigned long date; // 4 bytes
  unsigned long time; // 4 bytes
  float val_1; // 4 bytes
  float val_2; // 4 bytes
  float val_3; // 4 bytes
  float val_4; // 4 bytes 
  int val_5; // 2 bytes .... 31 bytes in total
}measurement_1, measurement_2;

// measurement_1 = {
// i =1
// date
// time
// latitude
// longitude
// current
// voltage
// wait time
// }

// measurement_2 = {
// i =2
// date
// time
// wave height
// wave period
// water temp
// air temp
// wave power
// }

#define TCAADDR 0x70

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void setup() {
  setup_gps();
  setup_radio();
  setup_gy86();
  setup_power_control();
  setup_water_temperature();
  measurement_1.index = 1;
  measurement_2.index = 2;
}

void loop() {
  get_gps_data();
  get_wave_stats();
  get_water_temperature();
  set_new_alarm();
  send_data();
  delay(3000); // seemed to help radio communication reliability
  turn_off();
}


