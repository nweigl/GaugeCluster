#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H
#define PULSES_PER_FOOT 16
#define INITIAL_MILEAGE_ADDRESS 0
#define EEPROM_WRITE_INDEX sizeof(long)

class Speedometer {
    public:
        Speedometer();
        void setup();
        void loop();
        int getSpeed();
        int getRPM();
        long getCurrentMileage();
    private:
        void incrementOdometer();
        void inititalizeEEPROM(long);
};

#endif