#include <Arduino.h>
#include "VoltGauge.h"

#define VOLT_PIN A3
#define VOLT_R1 15000
#define VOLT_R2 7500

VoltGauge::VoltGauge() {
}

int VoltGauge::getValue() {
    uint16_t x = analogRead(VOLT_PIN);
    int volts = x * 5115 * ((VOLT_R1 + VOLT_R2)/VOLT_R2);   
    return volts;     
}
