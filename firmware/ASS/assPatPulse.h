#ifndef ASSPATPULSE_H
#define ASSPATPULSE_H

class assPixs;

class assPatPulse {
public:
    assPatPulse();
    void setPixs(assPixs* pixs);
    void start(int num, int state, int diff, bool noupdate);
    void update(unsigned long time);
    void setColor(uint32_t color);
    void setSpeed(int speed) { this->pulseInterval = speed;}

private:
    assPixs* pixs;
    int red, green, blue;
    double pulseBrightness = 100;
    int pulseDirection = 1;
    int pulseInterval = 10;
    double pulseMultiplier = 1;
    unsigned long timeToNextState = 0;  // time to the next state change
};

#endif // ASSPATPULSE_H