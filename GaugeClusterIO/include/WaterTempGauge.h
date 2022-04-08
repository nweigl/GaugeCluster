#ifndef WATERTEMPGAUGE_H
#define WATERTEMPGAUGE_H

const int tempTable[54] = {    
    211,
    204,
    197,
    191,
    185,
    180,
    174,
    169,
    164,
    160,
    155,
    151,
    147,
    144,
    140,
    137,
    134,
    131,
    128,
    125,
    123,
    120,
    118,
    116,
    114,
    112,
    110,
    109,
    107,
    106,
    104,
    103,
    101,
    100,
    99,
    97,
    96,
    95,
    94,
    92,
    91,
    90,
    89,
    87,
    86,
    84,
    83,
    81,
    79,
    77,
    75,
    73,
    71,
    69
};

class WaterTempGauge {
    public:
        WaterTempGauge();
        int getValue();
    private:
};

#endif