#include <Arduino.h>
#include "VoltGauge.h"
#include "SwitecX12.h"

#define VOLT_PIN A3
#define VOLT_R1 200
#define VOLT_R2 200
#define VOLT_MAX 15

SwitecX12 volt(STEPS, E_STEP, E_DIR);

VoltGauge::VoltGauge() {
}

void VoltGauge::setup() {
    volt.zero();
}

void VoltGauge::loop() {
    if (volt.stopped) {
        uint16_t x = analogRead(VOLT_PIN);
        double volts = x * 5115 * ((VOLT_R1 + VOLT_R2)/VOLT_R2);
        int position = STEPS * volts/VOLT_MAX;
        volt.setPosition(position);
    }

    volt.update();
}
