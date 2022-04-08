#include <Arduino.h>
#include "VoltGauge.h"
#include "SwitecX12.h"

SwitecX12 volt(STEPS, E_STEP, E_DIR);

VoltGauge::VoltGauge() {
}

void VoltGauge::setup() {
    volt.zero();
}

void VoltGauge::indicateVoltage(int volts) {    
    if (volt.stopped) {
        if (volts > 15) {
            volts = 15;
        }

        if (volts < 8) {
            volts = 8;
        }
        
        int position = STEPS * volts/15;
        volt.setPosition(position);
    }

    volt.update();
}
