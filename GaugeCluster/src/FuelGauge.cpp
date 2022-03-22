#include <Arduino.h>
#include "FuelGauge.h"
#include "SwitecX12.h"

#define FUEL_PIN A2
#define FUEL_RREF 100
#define FUEL_RMAX 90
#define FUEL_RMIN 0

SwitecX12 fuel(STEPS, D_STEP, D_DIR);

FuelGauge::FuelGauge() {
}

void FuelGauge::setup() {
    fuel.zero();
}

void FuelGauge::loop() {
    if (fuel.stopped) {
        uint16_t x = analogRead(FUEL_PIN);
        int resistance = (FUEL_RREF * x) / (1024.0 - x);
        double fuelPercentage;
        if (resistance <= FUEL_RMIN)
        {
            fuelPercentage = 0;
        }
        else if (resistance >= FUEL_RMAX)
        {
            fuelPercentage = 1;
        }
        else {
            fuelPercentage = resistance / FUEL_RMAX;
        }

        int position = STEPS * fuelPercentage;
        fuel.setPosition(position);
    }

    fuel.update();
}
