#ifndef OILPRESSUREGAUGE_H
#define OILPRESSUREGAUGE_H

#define STEPS 3780
#define B_STEP 11
#define B_DIR 12

class OilPressureGauge {
    public:
        OilPressureGauge();
        void setup();
        void indicatePsi(double psi);
    private:
};

#endif