#ifndef ASSPATIDLE_H
#define ASSPATIDLE_H

#include "assG.h"

class assPixs;

enum class assMouthState {
    IDLE,
    ON,
    START,
    OFF
};


struct assMouthPixInfo {
    assMouthState state = assMouthState::IDLE;
    uint32_t color = 0;
    unsigned long timer = 0;
};

class assPatIdle {
public:
    assPatIdle();
    void setPixs(assPixs* pixs);
    void setColor(int red, int green, int blue);
    void update(unsigned long time);
    void talk(assMouthTalk talk);

private:
    assPixs* pixs;
    int red = 0;
    int green = 0;
    int blue = 0;
    int TIME_ON = 300;
    int TIME_OFF = 100;
    int TIME_OFF_OFF = 25;
    assMouthPixInfo pixelInfo[PIXEL_MOUTH];
};

#endif // ASSPATIDLE_H