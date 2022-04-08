#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H
#define STEPS 3780
#define A_STEP 8
#define A_DIR 9
class Speedometer {
    public:
        Speedometer();
        void setup();
        void indicateSpeed(int);
        void indicateMileage(long);
    private:
};

#endif