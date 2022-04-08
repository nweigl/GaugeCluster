#ifndef VOLTGAUGE_H
#define VOLTGAUGE_H

#define STEPS 3780
#define E_STEP 4
#define E_DIR 5

class VoltGauge {
    public:
        VoltGauge();
        void setup();
        void indicateVoltage(int volts);
    private:
};

#endif