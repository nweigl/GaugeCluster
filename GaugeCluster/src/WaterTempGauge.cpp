#include <Arduino.h>
#include "WaterTempGauge.h"
#include "SwitecX12.h"

#define WATER_TEMP_PIN A1
#define WATER_TEMP_RREF 680
#define WATER_TEMP_RMAX 610
#define WATER_TEMP_RMIN 80

SwitecX12 water(STEPS, C_STEP, C_DIR);

WaterTempGauge::WaterTempGauge() {
}

void WaterTempGauge::setup() {
    water.zero();
}

void WaterTempGauge::loop() {
    if (water.stopped) {
        uint16_t x = analogRead(WATER_TEMP_PIN);
        int resistance = (WATER_TEMP_RREF * x) / (1024.0 - x);
        double temp;
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

        int position = STEPS * temp/212;
        water.setPosition(position);
    }

    water.update();
}
