#ifndef ASSPATONEBY_H
#define ASSPATONEBY_H

class assPixs;

enum class assOneState {
  UP,DOWN
};

class assPatOneBy {
public:
    assPatOneBy();
    void setPixs(assPixs* pixs);
    void start(int time, int uniqueId = 4, int speed = 200, bool noupdate = false);
    void update(unsigned long time);
    void setColor(uint32_t color, uint32_t colorOff = 0x000000);
    void setSpeed(int speed) { this->speed = speed;}

private:
    assPixs* pixs;
    int speed = 100;
    int time = 0;
    uint32_t color = 0xFFFFFF;
    uint32_t colorOff = 0x000000;
    int sequenceIndex = 4;
    int mode = 1;
    assOneState state = assOneState::UP;

};

#endif // ASSPATONEBY_H 