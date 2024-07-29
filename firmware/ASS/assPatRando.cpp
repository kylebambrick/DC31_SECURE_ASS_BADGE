#include "assPixs.h"
#include "assPatRando.h"
#include "assG.h"

assPatRando::assPatRando() : pixs(nullptr)  {
}

void assPatRando::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatRando::start(int time, int speed, bool noupdate) {
    if (noupdate) return;
    
    this->time = time + millis();

    if (speed > 0) this->speed = speed; 
}

void assPatRando::update(unsigned long time) {
    if (time >= this->time) {
        this->time = time + this->speed;

        for(int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++)
            this->colors[i] = pixs->getStrip().Color(random(0,256),random(0,256),random(0,256));

        pixs->setPatternState(0);
    }

    for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++)
        pixs->getStrip().setPixelColor(i, this->colors[i]);

    pixs->setPatternTime(this->time - time);
}