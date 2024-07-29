#ifndef ASSPATSNAKE_H
#define ASSPATSNAKE_H

class assPixs;

enum class assSnakeState {
  FILLUP,UNUP,FILLDOWN,UNDOWN
};

class assPatSnake {
public:
    assPatSnake();
    void setPixs(assPixs* pixs);
    void start(int time, int uniqueId, int speed, bool noupdate = false);
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
    assSnakeState state = assSnakeState::FILLUP;

};

#endif // ASSPATSNAKE_H 