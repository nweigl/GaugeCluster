#include <Arduino.h>
#include "OilPressureGauge.h"
#include "FuelGauge.h"
#include "WaterTempGauge.h"
#include "VoltGauge.h"
#include "Speedometer.h"
#include "DataDisplay.h"

#define RESET 10


OilPressureGauge oilPressureGauge;
FuelGauge fuelGauge;
WaterTempGauge waterTempGauge;
VoltGauge voltGauge;
Speedometer speedometer;

void setup () {
  Serial.begin(9600);
  digitalWrite(RESET, HIGH);
  speedometer.setup();
  oilPressureGauge.setup();
  waterTempGauge.setup();
  fuelGauge.setup();
  voltGauge.setup();    
}

void loop () {
  speedometer.loop();
  oilPressureGauge.loop();
  waterTempGauge.loop();
  fuelGauge.loop();
  voltGauge.loop();
}