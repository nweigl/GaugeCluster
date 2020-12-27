#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H
#define PULSES_PER_FOOT 16
#define STEPS 3780
#define A_STEP 8
#define A_DIR 9
#define RESET 10

class Speedometer {
    public:
        Speedometer();
        void setup();
        void loop();
    private:
        void incrementOdometer(double);
        void indicateSpeed(double);
};

#endif