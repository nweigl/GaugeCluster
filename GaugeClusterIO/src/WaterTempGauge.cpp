#include <Arduino.h>
#include "WaterTempGauge.h"

#define WATER_TEMP_PIN A1
#define WATER_TEMP_RREF 680
#define WATER_TEMP_RMAX 610
#define WATER_TEMP_RMIN 8

WaterTempGauge::WaterTempGauge() {
}

int WaterTempGauge::getValue() {
    uint16_t x = analogRead(WATER_TEMP_PIN);
    int resistance = (WATER_TEMP_RREF * x) / (1024.0 - x);
    int temp;
    if (resistance >= WATER_TEMP_RMAX)
    {
        temp = tempTable[53];
    }
    else if (resistance <= WATER_TEMP_RMIN)
    {
        temp = tempTable[0];
    }
    else {
        int index = (resistance - 80)  / 10;
        temp = tempTable[index];
    }

    return temp;
}
