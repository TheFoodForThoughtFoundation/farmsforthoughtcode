#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H
#include <Arduino.h>
#include <WiFiNINA.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


void wifi_setup();
void wifi_tick();
int get_current_time(); 
void printCurrentNet();
void printWifiData();

#endif