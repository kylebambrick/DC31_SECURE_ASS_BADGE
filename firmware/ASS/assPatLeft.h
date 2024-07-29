#ifndef ASSPATLEFT_H
#define ASSPATLEFT_H

class assPixs;

class assPatLeft {
public:
    assPatLeft();
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

#endif // ASSPATLEFT_H