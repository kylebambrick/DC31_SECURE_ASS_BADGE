#ifndef ASSPATRAINBOW_H
#define ASSPATRAINBOW_H

class assPixs;

class assPatRainbow {
public:
    assPatRainbow();
    void setPixs(assPixs* pixs);
    void start(int num, int state, bool noupdate = false);
    void update(unsigned long currentTime);
    void setSpeed(int num);
    void reset();

private:
    assPixs* pixs;
    int rainbowCycle = 0;
    int speed = 100;
    int timeToNextState = 0;

    int red = 0;
    int green = 0;
    int blue = 0;

    void wheel();
};

#endif // ASSPATRAINBOW_H