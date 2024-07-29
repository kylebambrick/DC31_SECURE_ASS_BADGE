#ifndef ASSPATSPARKLEMOUTH_H
#define ASSPATSPARKLEMOUTH_H

class assPixs;

class assPatSparkleMouth {
public:
    assPatSparkleMouth();
    void setPixs(assPixs* pixs);
    void start();
    void update(unsigned long time);
    void setColor(int red, int green, int blue);

private:
    assPixs* pixs;
    int red, green, blue;
    unsigned long timeToNextState = 0;
    unsigned long interval = 50;
    unsigned long DONE_TIME = 2000;
    unsigned long DONE_TIMER = 0;
    int numOfPixelsOn = 2;
    int selectedPixels[PIXEL_MOUTH];

    void setRandomValues();
};

#endif // ASSPATSPARKLEMOUTH_H
