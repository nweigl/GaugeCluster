#include <Arduino.h>
#include "OilPressureGauge.h"
#include "Speedometer.h"

OilPressureGauge oilPressureGauge;
Speedometer speedometer;

void setup () {
  Serial.begin(9600); 
  speedometer.setup();
  oilPressureGauge.setup();      
}

void loop () {
  speedometer.loop();
  oilPressureGauge.loop();
}