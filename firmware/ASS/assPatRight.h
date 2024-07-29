#ifndef ASSPATRIGHT_H
#define ASSPATRIGHT_H

class assPixs;

class assPatRight {
public:
    assPatRight();
    void setPixs(assPixs* pixs);
    void start(int n);
    void update(unsigned long currentTime);
    void setColor(int red, int green, int blue);
    void reset();
private:
    assPixs* pixs;
    int red, green, blue;
    int spot, blinks;
    unsigned long startTime;
};

#endif // ASSPATRIGHT_H