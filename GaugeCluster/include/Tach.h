#ifndef TACH_H
#define TACH_H
#define STEPS 3780
#define F_STEP 16
#define F_DIR 17

class Tach {
    public:
        Tach();
        void setup();
        void indicateRPM(int);
    private:
};

#endif