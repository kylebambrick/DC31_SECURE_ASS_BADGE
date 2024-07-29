#ifndef ASSPATRANDO_H
#define ASSPATRANDO_H

class assPixs;

class assPatRando {
public:
    assPatRando();
    void setPixs(assPixs* pixs);
    void start(int time = 0, int speed = 100, bool noupdate = false);
    void update(unsigned long time);
    void setSpeed(int speed) { this->speed = speed;}

private:
    assPixs* pixs;
    int speed = 200;
    int time = 0;
    uint32_t colors[20];
};

#endif // ASSPATRANDO_H 