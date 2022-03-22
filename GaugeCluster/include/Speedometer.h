#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H
#define PULSES_PER_FOOT 16
#define STEPS 3780
#define A_STEP 8
#define A_DIR 9
#define F_STEP 20
#define F_DIR 21
#define INITIAL_MILEAGE_ADDRESS 0
#define EEPROM_WRITE_INDEX sizeof(long)

class Speedometer {
    public:
        Speedometer();
        void setup();
        void loop();
    private:
        void incrementOdometer();
        void indicateSpeed(double);
        void indicateRPM(double);
        long getCurrentMileage();
        void inititalizeEEPROM(long);
};

#endif