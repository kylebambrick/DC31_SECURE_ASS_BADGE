#ifndef ASSPATSPARKLE_H
#define ASSPATSPARKLE_H

class assPixs;

class assPatSparkle {
public:
    assPatSparkle();
    void setPixs(assPixs* pixs);
    void start(unsigned long num, int numOfPixelsOn, int _interval);
    void update(unsigned long currentTime);
    void setColor(uint32_t color, uint32_t colorOff = 0x000000);
    void setSpeed(int speed) { this->interval = speed;}
    void setPixelsOn(int num) { this->numOfPixelsOn = num;}

private:
    assPixs* pixs;
    uint32_t color = 0xFFFFFF;
    uint32_t colorOff = 0x000000;
    unsigned long timeToNextState = 0;
    unsigned long interval = 500;
    int numOfPixelsOn = 5;
    int selectedPixels[PIXEL_COUNT];

    void setRandomValues();
};

#endif // ASSPATSPARKLE_H
