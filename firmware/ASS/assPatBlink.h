#ifndef ASSPATBLINK_H
#define ASSPATBLINK_H

class assPixs;

class assPatBlink {
public:
    assPatBlink();
    void setPixs(assPixs* pixs);
    void start(int num, int state, int diff, bool noupdate);
    void update(unsigned long currentTime);
    void setColor(uint32_t color, uint32_t colorOff = 0x000000);
    void setSpeed(int speed) { this->onOff = speed;}

private:
    assPixs* pixs;
    uint32_t color = 0xFF0000;
    uint32_t colorOff = 0x000000;
    bool isOn = false;
    unsigned long timeToNextState = 0;  // time to the next state change
    int onOff = 750;
};

#endif // ASSPATBLINK_H