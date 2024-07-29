#ifndef ASSPATPULSED_H
#define ASSPATPULSED_H

class assPixs;

class assPatPulseD {
public:
    assPatPulseD();
    void setPixs(assPixs* pixs);
    void start(int time, int state, int speed, bool noupdate);
    void update(unsigned long time);
    void setColor(uint32_t colorA, uint32_t colorB);
    void setSpeed(int speed) { this->interval = speed;}

private:
    assPixs* pixs;
    int redA = 0;
    int greenA = 0;
    int blueA = 0;
    int redB = 0;
    int greenB = 0;
    int blueB = 0;
    double brightness = 100;
    int direction = 1;
    int interval = 10;
    double multiplier = 1;
    unsigned long time = 0;
    int pixelsA[8] = {5,8,10,12,14,16,18};
    int pixelsB[8] = {6,7,9,11,13,15,17,19};


};

#endif // ASSPATPULSED_H