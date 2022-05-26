#include <Arduino.h>
#include "OilPressureGauge.h"
#include "SwitecX12.h"

#define OIL_PRESSURE_PIN A0
#define OIL_PRESSURE_RREF 200
#define OIL_PRESSURE_RMAX 200
#define OIL_PRESSURE_RMIN 11

SwitecX12 oil(B_STEPS, B_STEP, B_DIR);

OilPressureGauge::OilPressureGauge() {
}

void OilPressureGauge::setup() {
    oil.zero();
}

void OilPressureGauge::indicatePsi(double psi) {    
    if (oil.stopped) {
        if (psi > 80) {
            psi = 80;
        }

        if (psi < 0) {
            psi = 0;
        }
        
        int position = B_STEPS * psi/80;
        oil.setPosition(position);
    }

    oil.update();
}
