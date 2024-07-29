#include "assPixs.h"
#include "assPatScan.h"
#include "assG.h"

assPatScan::assPatScan() : pixs(nullptr)  {}

void assPatScan::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatScan::start(int time, int state, int speed, bool noupdate) {
    if (noupdate || state == -1) return;
    
    this->time = time + millis();

    if (speed > 0) this->speed = speed; 

    if (state >= 0 && state <= 5) this->sequenceIndex = state;
}

void assPatScan::update(unsigned long time) {
    if (time >= this->time) {  // Check against timeToNextState
        this->time = time + this->speed;  // Set the next state time

        this->sequenceIndex += direction;

        if (sequenceIndex == 0) direction = 1;
        if (sequenceIndex == 5) direction = -1;

        pixs->setPatternState(this->sequenceIndex);
    }

    for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++)
        pixs->getStrip().setPixelColor(i, this->colorOff);

    switch (sequenceIndex) {
        case 0:
            pixs->getStrip().setPixelColor(5, this->color);
            pixs->getStrip().setPixelColor(13, this->color);
            pixs->getStrip().setPixelColor(15, this->color);
            break;
        case 1:
            pixs->getStrip().setPixelColor(6, this->color);
            pixs->getStrip().setPixelColor(16, this->color);
            break;
        case 2:
            pixs->getStrip().setPixelColor(12, this->color);
            pixs->getStrip().setPixelColor(14, this->color);
            break;
        case 3:
            pixs->getStrip().setPixelColor(7, this->color);
            pixs->getStrip().setPixelColor(11, this->color);
            pixs->getStrip().setPixelColor(17, this->color);
            break;
        case 4:
            pixs->getStrip().setPixelColor(8, this->color);
            pixs->getStrip().setPixelColor(18, this->color);
            break;
        case 5:
            pixs->getStrip().setPixelColor(9, this->color);
            pixs->getStrip().setPixelColor(10, this->color);
            pixs->getStrip().setPixelColor(19, this->color);
            break;
    }

    pixs->setPatternTime(this->time - time);
}

void assPatScan::setColor(uint32_t color, uint32_t colorOff) { 
    this->color = color;
    this->colorOff = colorOff;
};