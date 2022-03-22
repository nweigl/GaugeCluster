#ifndef DATADISPLAY_H
#define DATADISPLAY_H
#include <stdint.h>

class DataDisplay {
    public:
        DataDisplay();
        void setup();
        void drawOdometer(long);        
        void drawBowtie();
    private:
};

#endif