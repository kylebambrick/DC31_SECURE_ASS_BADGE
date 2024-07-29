#ifndef ASSPATSCAN_H
#define ASSPATSCAN_H
class assPixs;

class assPatScan {
public:
    assPatScan();
    void setPixs(assPixs* pixs);
    void start(int time, int state, int speed, bool noupdate = false);
    void update(unsigned long time);
    void setColor(uint32_t color, uint32_t colorOff = 0x000000);
    void setSpeed(int speed) { this->speed = speed;}

private:
    assPixs* pixs;
    int speed = 50;
    int time = 0;
    uint32_t color = 0xFFFFFF;
    uint32_t colorOff = 0x000000;
    int sequenceIndex = 0;
    int direction = 1;

};

#endif // ASSPATSCAN_H 