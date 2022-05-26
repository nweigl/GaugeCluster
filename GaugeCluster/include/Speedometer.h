#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#define A_STEPS 3050
#define A_STEP 4
#define A_DIR 5
class Speedometer {
    public:
        Speedometer();
        void setup();
        void indicateSpeed(int);
        void indicateMileage(long);
    private:
};

#endif