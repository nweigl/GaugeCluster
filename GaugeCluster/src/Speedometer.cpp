#include <Arduino.h>
#include "DataDisplay.h"
#include "Speedometer.h"
#include "SwitecX12.h"

SwitecX12 speedo(STEPS, A_STEP, A_DIR);
DataDisplay dataDisplay;

Speedometer::Speedometer() {
}

void Speedometer::setup() {
  speedo.zero();
  dataDisplay.setup();
}

void Speedometer::indicateSpeed(int speed) {
  if (speedo.stopped) {
    if (speed > 100) {
      speed = 100;
    }
    
    if (speed < 0) {
      speed = 0;
    }
    
    int position = STEPS * speed/100;
    speedo.setPosition(position);
  }

  speedo.update();
}

void Speedometer::indicateMileage(long mileage) {
  dataDisplay.drawOdometer(mileage);
}