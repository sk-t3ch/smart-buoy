#include <onewire.h>
#include <dallastemperature.h>

OneWire oneWire(6);
DallasTemperature sensors(&oneWire);
float water_temperature;

void setup() {
  Serial.begin(115200);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  water_temperature = sensors.getTempCByIndex(0);  
  Serial.print("Water temperature C "); Serial.println(water_temperature);
  delay(200);
}