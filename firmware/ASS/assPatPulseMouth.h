#ifndef ASSPATPULSEMOUTH_H
#define ASSPATPULSEMOUTH_H

class assPixs;

class assPatPulseMouth {
public:
    assPatPulseMouth();
    void setPixs(assPixs* pixs);
    void start(int bliks);
    void update(unsigned long time);
    void setColor(int red, int green, int blue);

private:
    assPixs* pixs;
    int red, green, blue;
    int blinks = 2;
    double pulseBrightness = 100;
    int pulseDirection = 1;
    int PULSE_TIME = 10;
    unsigned long PULSE_TIMER = 0;
    double pulseMultiplier = 1;
};

#endif // ASSPATPULSEMOUTH_H