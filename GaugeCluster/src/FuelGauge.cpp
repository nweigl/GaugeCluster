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

void FuelGauge::indicateFuel(int fuelPercentage) {
    if (fuel.stopped) {
        if (fuelPercentage > 100) {
            fuelPercentage = 100;
        }
        
        if (fuelPercentage < 0) {
            fuelPercentage = 0;
        }
        
        int position = STEPS * fuelPercentage/100;
        fuel.setPosition(position);
    }

    fuel.update();
}
