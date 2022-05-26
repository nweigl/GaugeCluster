#include <Arduino.h>
#include "WaterTempGauge.h"
#include "SwitecX12.h"

SwitecX12 water(C_STEPS, C_STEP, C_DIR);

WaterTempGauge::WaterTempGauge() {
}

void WaterTempGauge::setup() {
    water.zero();
}

void WaterTempGauge::indicateTemp(int temp) {
    if (water.stopped) {
        if (temp > 212)
        {
            temp = 212;
        }
        
        if (temp < 69)
        {
            temp = 69;
        }

        int position = C_STEPS * (temp - 69)/143;
        water.setPosition(position);
    }

    water.update();
}
