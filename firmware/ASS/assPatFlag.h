#ifndef ASSPATFLAG_H
#define ASSPATFLAG_H
class assPixs;

class assPatFlag {
public:
    assPatFlag();
    void setPixs(assPixs* pixs);
    void start(int time, int state, int speed, bool noupdate = false);
    void update(unsigned long time);
    void setSpeed(int speed) { this->speed = speed;}
    void setDirection(int dir) { this->direction = dir;}
    void setPixels(uint32_t colorA, uint32_t colorB, uint32_t colorC, uint32_t colorD, uint32_t colorE, uint32_t colorF);

private:
    assPixs* pixs;
    int speed = 200;
    int time = 0;
    uint32_t colorA = 0xFF0000;
    uint32_t colorB = 0xFF3200;
    uint32_t colorC = 0xFFFF00;
    uint32_t colorD = 0x00FF00;
    uint32_t colorE = 0x0000FF;
    uint32_t colorF = 0xFF00FF;
    int sequenceIndex = 0;
    int direction = 1;
    int rowA[2] = {16,15};
    int rowB[3] = {17,14,13};
    int rowC[4] = {5,6,12,18};
    int rowD[3] = {7,11,19};
    int rowE[2] = {8,10};
    int rowF[1] = {9};

};

#endif // ASSPATFLAG_H 