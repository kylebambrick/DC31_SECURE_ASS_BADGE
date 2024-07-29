#ifndef ASSPATRANDOFILL_H
#define ASSPATRANDOFILL_H

class assPixs;

enum class assFillState {
  FILL,UNFILL
};

class assPatRandoFill {
public:
    assPatRandoFill();
    void setPixs(assPixs* pixs);
    void start(int time, int speed = 200, bool noupdate = false);
    void update(unsigned long time);
    void setColor(uint32_t color, uint32_t colorOff = 0x000000);
    void setSpeed(int speed) { this->speed = speed;}


private:
    assPixs* pixs;
    int speed = 100;
    int time = 0;
    uint32_t color = 0xFFFFFF;
    uint32_t colorOff = 0x000000;
    assFillState state = assFillState::FILL;
    int pixels[PIXEL_COUNT] = {0}; 

};

#endif // ASSPATRANDOFILL_H 