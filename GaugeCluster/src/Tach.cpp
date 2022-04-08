#include <Arduino.h>
#include "Tach.h"
#include "SwitecX12.h"

SwitecX12 tach(STEPS, F_STEP, F_DIR);

Tach::Tach() {
}

void Tach::setup() {
  tach.zero();
}

void Tach::indicateRPM(int rpm) {
  if (tach.stopped) {
    if (rpm > 5000) {
      rpm = 5000;
    }

    if (rpm < 0) {
      rpm = 0;
    }
    
    int position = STEPS * rpm/5000;
    tach.setPosition(position);
  }

  tach.update();
}