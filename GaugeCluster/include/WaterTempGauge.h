#ifndef WATERTEMPGAUGE_H
#define WATERTEMPGAUGE_H

#define STEPS 3780
#define C_STEP 6
#define C_DIR 7

class WaterTempGauge {
    public:
        WaterTempGauge();
        void setup();
        void indicateTemp(int temp);
    private:
};

#endif