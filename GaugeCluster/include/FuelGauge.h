#ifndef FUELGAUGE_H
#define FUELGAUGE_H

#define STEPS 1100
#define D_STEP 2
#define D_DIR 3

class FuelGauge {
    public:
        FuelGauge();
        void setup();
        void indicateFuel(int fuelPercentage);
    private:
};

#endif