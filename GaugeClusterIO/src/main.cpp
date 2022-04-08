#include <Arduino.h>
#include "OilPressureGauge.h"
#include "FuelGauge.h"
#include "WaterTempGauge.h"
#include "VoltGauge.h"
#include "Speedometer.h"


OilPressureGauge oilPressureGauge;
FuelGauge fuelGauge;
WaterTempGauge waterTempGauge;
VoltGauge voltGauge;
Speedometer speedometer;

void setup () {
  Serial.begin(9600);
  speedometer.setup();   
}

void loop () {
  speedometer.loop();
  int speed = speedometer.getSpeed();
  int rpm = speedometer.getRPM();
  long mileage = speedometer.getCurrentMileage();
  double oil = oilPressureGauge.getValue();
  int water = waterTempGauge.getValue();
  int fuel = fuelGauge.getValue();
  int volts = voltGauge.getValue();
  char buffer[34];

  sprintf(buffer, "%d,%ld,%d,%d,%f,%d,%d\n",speed, mileage, rpm, fuel, oil, water, volts);

  Serial.write(buffer);
}