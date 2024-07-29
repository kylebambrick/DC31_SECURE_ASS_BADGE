#include "assPixs.h"
#include "assPatHypno.h"
#include "assG.h"

assPatHypno::assPatHypno() : pixs(nullptr)  {}

void assPatHypno::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatHypno::start(int time, int state, int speed, int direction, bool noupdate) {
    if (noupdate || state == -1) return;
    
    this->time = time + millis();

    if (speed > 0) this->speed = speed; 

    if (direction == 1 || direction == -1) this->direction = direction;

    if (state >= 0 && state <= 2) this->sequenceIndex = state;
}

void assPatHypno::update(unsigned long time) {
    if (time >= this->time) {  // Check against timeToNextState
        this->time = time + this->speed;  // Set the next state time

        this->sequenceIndex += this->direction;

        if (this->sequenceIndex > 2) this->sequenceIndex = 0;
        if (this->sequenceIndex < 0) this->sequenceIndex = 2;

        pixs->setPatternState(this->sequenceIndex);
    }

    for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++)
        pixs->getStrip().setPixelColor(i, this->colorOff);

    pixs->getStrip().setPixelColor(this->pixSequenceInner[this->sequenceIndex], this->colorInner);
    pixs->getStrip().setPixelColor(this->pixSequenceOuter[this->sequenceIndex], this->color);
    pixs->getStrip().setPixelColor(this->pixSequenceOuter[this->sequenceIndex + 3], this->color);
    pixs->getStrip().setPixelColor(this->pixSequenceOuter[this->sequenceIndex + 6], this->color);

    pixs->setPatternTime(this->time - time);
}

void assPatHypno::setColor(uint32_t color, uint32_t colorOff, uint32_t color3) { 
    this->color = color;
    this->colorInner = color3;
    this->colorOff = colorOff;
}