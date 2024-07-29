#ifndef ASSPATHYPNO_H
#define ASSPATHYPNO_H
class assPixs;

class assPatHypno {
public:
    assPatHypno();
    void setPixs(assPixs* pixs);
    void start(int time = 0, int state = 0, int speed = 100, int direction = 1, bool noupdate = false);
    void update(unsigned long time);
    void setColor(uint32_t color, uint32_t colorOff = 0x000000, uint32_t color3 = 0xFFFFFF);
    void setSpeed(int speed) { this->speed = speed;}
    void setDirection(int dir) { this->direction = dir;}

private:
    assPixs* pixs;
    int speed = 200;
    int time = 0;
    uint32_t color = 0xFF0000;
    uint32_t colorInner = 0xFFFFFF; 
    uint32_t colorOff = 0x000000; 
    int pixSequenceOuter[9] = {6,7,10,19,18,17,16,15,13};
    int pixSequenceInner[3] = {11,12,14};
    int sequenceIndex = 0;
    int direction = 1;

};

#endif // ASSPATHYPNO_H 