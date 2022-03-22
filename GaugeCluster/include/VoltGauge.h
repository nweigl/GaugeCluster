#ifndef VOLTGAUGE_H
#define VOLTGAUGE_H

#define STEPS 3780
#define E_STEP 18
#define E_DIR 19

class VoltGauge {
    public:
        VoltGauge();
        void setup();
        void loop();
    private:
};

#endif