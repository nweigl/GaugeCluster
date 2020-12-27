#include <Arduino.h>
#include "OilPressureGauge.h"
#define OIL_PRESSURE_PIN 0
#define OIL_PRESSURE_RREF 200
#define OIL_PRESSURE_RMAX 200
#define OIL_PRESSURE_RMIN 11

OilPressureGauge::OilPressureGauge() {
}

void OilPressureGauge::setup() {
}

void OilPressureGauge::loop() {
    uint16_t x = analogRead(OIL_PRESSURE_PIN);
    int resistance = (OIL_PRESSURE_RREF * x) / (1024.0 - x);
    double psi;
    if (resistance <= OIL_PRESSURE_RMIN)
    {
        psi = psiTable[0];
    }
    else if (resistance >= OIL_PRESSURE_RMAX)
    {
        psi = psiTable[OIL_PRESSURE_RMAX - OIL_PRESSURE_RMIN];
    }
    else {
        psi = psiTable[resistance - OIL_PRESSURE_RMIN];
    }
}
