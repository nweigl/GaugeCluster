#ifndef OILPRESSUREGAUGE_H
#define OILPRESSUREGAUGE_H

#define B_STEPS 800
#define B_STEP 20
#define B_DIR 21

class OilPressureGauge {
    public:
        OilPressureGauge();
        void setup();
        void indicatePsi(double psi);
    private:
};

#endif