#ifndef ASSPATPINWHEEL_H
#define ASSPATPINWHEEL_H
class assPixs;

class assPatPinWheel {
public:
    assPatPinWheel();
    void setPixs(assPixs* pixs);
    void start(int time, int state, int speed, bool noupdate = false);
    void update(unsigned long time);
    void setColor(uint32_t color1, uint32_t color2, uint32_t color3);
    void setPixels(uint32_t color1, uint32_t color2, uint32_t color3);
    void setSpeed(int speed) { this->speed = speed;}
    void setDirection(int dir) { this->direction = dir;}

private:
    assPixs* pixs;
    int speed = 200;
    int time = 0;
    uint32_t colorA = 0xFFFFFF;
    uint32_t colorB = 0xFF0000;
    uint32_t colorC = 0x0000FF;
    int pixSequenceA[5] = {5,6,12,13,15};
    int pixSequenceB[5] = {7,8,9,10,11};
    int pixSequenceC[5] = {14,16,17,18,19};
    int sequenceIndex = 0;
    int direction = 1;

};

#endif // ASSPATPINWHEEL_H 