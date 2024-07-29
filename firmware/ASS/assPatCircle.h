#ifndef ASSPATCIRCLE_H
#define ASSPATCIRCLE_H
class assPixs;


enum class assCircleState {
  FILLUP,UNUP,FILLDOWN,UNDOWN
};

class assPatCircle {
public:
    assPatCircle();
    void setPixs(assPixs* pixs);
    void start(int time, int uniqueID, int speed, bool noupdate = false);
    void update(unsigned long time);
    void setColor(uint32_t color, uint32_t colorOff = 0xFF000000);
    void setSpeed(int speed) { this->speed = speed;}

private:
    assPixs* pixs;
    int speed = 200;
    int time = 0;
    uint32_t color = 0xFFFFFF;
    uint32_t colorOff = 0xFF0000;
    int pixSequence[10] = {17,16,15,13,6,7,10,19,18};
    int sequenceIndex = 0;
    int uniqueID = 0;
    assCircleState state = assCircleState::FILLUP;

};

#endif // ASSPATCIRCLE_H 