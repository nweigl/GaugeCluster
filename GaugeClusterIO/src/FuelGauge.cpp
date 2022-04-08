#include <Arduino.h>
#include "FuelGauge.h"

#define FUEL_PIN A2
#define FUEL_RREF 100
#define FUEL_RMAX 90
#define FUEL_RMIN 0

FuelGauge::FuelGauge() {
}

int FuelGauge::getValue() {
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

    return fuelPercentage * 100;
}
