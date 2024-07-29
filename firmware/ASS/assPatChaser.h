#ifndef ASSPATCHASER_H
#define ASSPATCHASER_H
class assPixs;

class assPatChaser {
public:
    assPatChaser();
    void setPixs(assPixs* pixs);
    void start(int time, int state, int speed, int mode = 1, bool noupdate = false);
    void update(unsigned long time);
    void setColor(uint32_t color, uint32_t colorOff = 0x000000);
    void setSpeed(int speed) { this->speed = speed;}
    void setMode(int mode) { this->mode = mode;}

private:
    assPixs* pixs;
    int speed = 50;
    int timeToNextState = 0;
    uint32_t color = 0xFFFFFF;
    uint32_t colorOff = 0x000000;
    int pixSequence[10] = {6,7,10,19,18,17,16,15,13};
    int sequenceIndex = 0;
    int mode = 1;

};

#endif // ASSPATCHASER_H 