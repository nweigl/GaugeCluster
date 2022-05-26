#ifndef FUELGAUGE_H
#define FUELGAUGE_H

#define D_STEPS 1100
#define D_STEP 1
#define D_DIR 0

class FuelGauge {
    public:
        FuelGauge();
        void setup();
        void indicateFuel(int fuelPercentage);
    private:
};

#endif