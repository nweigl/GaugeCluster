#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H
#define PULSES_PER_FOOT 16

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