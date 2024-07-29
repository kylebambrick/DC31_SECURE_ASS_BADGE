#ifndef ASSPATDRIP_H
#define ASSPATDRIP_H
#include <vector>

class assPixs;

struct node {
  int pixel;
  bool topNode;
  int aboveA;
  int aboveB;
  int aboveC;
};

class assPatDrip {
public:
    assPatDrip();
    void setPixs(assPixs* pixs);
    void start(int time, int state, int speed, bool noupdate = false);
    void update(unsigned long time);
    void setColor(uint32_t color, uint32_t colorOff = 0x000000);
    void setSpeed(int speed) { this->speed = speed;}

private:
    assPixs* pixs;
    int speed = 200;
    int time = 0;
    uint32_t color = 0xFFFFFF;
    uint32_t colorOff = 0x000000;
    int sequenceIndex = 0;
    std::vector<node> nodes;
    bool state[20] = {false};
};

#endif // ASSPATDRIP_H
