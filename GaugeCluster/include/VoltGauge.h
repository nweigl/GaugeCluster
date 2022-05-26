#ifndef VOLTGAUGE_H
#define VOLTGAUGE_H

#define E_STEPS 1100
#define E_STEP 8
#define E_DIR 9

class VoltGauge {
    public:
        VoltGauge();
        void setup();
        void indicateVoltage(int volts);
    private:
};

#endif