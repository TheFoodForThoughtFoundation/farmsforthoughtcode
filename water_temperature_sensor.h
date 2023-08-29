#ifndef WATER_TEMPERATURE_SENSOR_H
#define WATER_TEMPERATURE_SENSOR_H
#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#define WATER_TEMPERATURE_INPUT 4

void water_temperature_sensor_setup();
float get_water_temperature();

#endif
