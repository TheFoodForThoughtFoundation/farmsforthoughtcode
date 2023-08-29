#include "water_temperature_sensor.h"

OneWire oneWire(WATER_TEMPERATURE_INPUT);
DallasTemperature water_temperature_sensor(&oneWire);

void water_temperature_sensor_setup(){
  water_temperature_sensor.begin();
}

float get_water_temperature(){
  water_temperature_sensor.requestTemperatures();
  return water_temperature_sensor.getTempFByIndex(0);
}