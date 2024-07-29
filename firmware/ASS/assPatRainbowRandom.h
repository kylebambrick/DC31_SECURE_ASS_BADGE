#ifndef ASSPATRAINBOWRANDOM_H
#define ASSPATRAINBOWRANDOM_H

#include "assG.h"

class assPixs;

struct assPixInfo {
    int speed;
    uint32_t color;
    int position;
    unsigned long time;
};

class assPatRainbowRandom {
public:
    assPatRainbowRandom();
    void setPixs(assPixs* pixs);
    void start(int state, bool noupdate = false);
    void reset();
    void update(unsigned long time);
    uint32_t colorWheel(int position);

private:
    assPixs* pixs;
    int timeToNextState = 0;

    void wheel();
    assPixInfo pixelInfo[PIXEL_COUNT];
};

#endif // ASSPATRAINBOWRANDOM_H 