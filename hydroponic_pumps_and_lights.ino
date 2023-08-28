/*
Hydroponic System v1
*/
#include "wifi_config.h"

#define SECOND 167 
#define MINUTE SECOND*60

// Output Pin Numbers
// Outputs: [Pump, Lights]
int LIGHT_OUTPUT = 13;
int PUMP_OUTPUT = 14;

// Pump Vairables
// We are cycling so we will be on for X minutes and off for Y minutes
int pump_on_time = 1 * MINUTE;
int pump_off_time = 2 * MINUTE;
bool is_pump_on = false;
unsigned long last_pump_actuation_time;

// Light Variables
// Assuming lights start at early time and end at later time
// 12:00AM = 0000 and 11:59PM = 2359
int light_on_time = 700;
int light_off_time = 1502;


void setup() {
  Serial.begin(9600);

  // Wifi Setup
  wifi_setup();

  // Pump Setup
  // TODO: maybe add a button for starting the system up
  pinMode(PUMP_OUTPUT, OUTPUT);   
  turn_on_pump();

  // Lights Setup
  pinMode(LIGHT_OUTPUT, OUTPUT);
}

void loop() {
  wifi_tick();
  process_pump();
  process_lights();
  delay(100);
}

// Pump Methods
void process_pump() {
  unsigned long current_time = millis();
  if(is_pump_on && last_pump_actuation_time + pump_on_time <= current_time) {
    turn_off_pump();
  } else if (!is_pump_on && last_pump_actuation_time + pump_off_time <= current_time) {
    turn_on_pump();
  }
}

void turn_on_pump() {
  is_pump_on = true;
  digitalWrite(PUMP_OUTPUT, HIGH);
  last_pump_actuation_time = millis();
}

void turn_off_pump() {
  is_pump_on = false;
  digitalWrite(PUMP_OUTPUT, LOW);
  last_pump_actuation_time = millis();
}

// Light Methods
void process_lights() {
  // TODO: replace this number by getting actual time on the WiFi board
  int current_time = get_current_time();
  if(timeWithinRange(current_time, light_on_time, light_off_time)){
    turn_on_light();
    Serial.println("Turn lights on");
  } else {
    turn_off_light();
    Serial.println("Turn lights off");
  }
}

void turn_on_light() {
  digitalWrite(LIGHT_OUTPUT, HIGH);
}

void turn_off_light() {
  digitalWrite(LIGHT_OUTPUT, LOW);
}

// Helper Methods
bool timeWithinRange( unsigned long now, unsigned long start, unsigned long end ) {
  bool inRange = false;
  if ( start <= now and now < end ) inRange = true;
  if ( start > end ) inRange = !inRange;
  return inRange;
}