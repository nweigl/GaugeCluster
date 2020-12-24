#include <Arduino.h>
#include "OilPressureGauge.h"
#include "Speedometer.h"

OilPressureGauge oilPressureGauge;
Speedometer speedometer;

void setup () {
  Serial.begin(9600);       
}

void loop () {
  double psi = oilPressureGauge.getPressure();
  int speed = speedometer.getSpeed();
  Serial.print("Oil PSI: ");
  Serial.println(psi);
  Serial.print("Speed: ");
  Serial.println(speed);
  delay(1000);
}