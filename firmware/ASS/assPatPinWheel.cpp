#include "assPixs.h"
#include "assPatPinWheel.h"
#include "assG.h"

assPatPinWheel::assPatPinWheel() : pixs(nullptr)  {}

void assPatPinWheel::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatPinWheel::start(int time, int state, int speed, bool noupdate) {
    if (noupdate || state == -1) return;
    
    this->time = time + millis();

    if (speed > 0) this->speed = speed; 

    if (state >= 0 && state <= 2) {
        direction = 1;
        this->sequenceIndex = state;
    } else if (state >= 3 && state <= 5) {
        this->direction = -1;
        this->sequenceIndex = (state - 3) * -1;
    }
}

void assPatPinWheel::update(unsigned long time) {
    if (time >= this->time) {
        this->time = time + this->speed;

        this->sequenceIndex += this->direction;
        if (this->sequenceIndex > 2 || this->sequenceIndex < -2)
            this->sequenceIndex = 0;

        if (direction > 0) pixs->setPatternState(this->sequenceIndex);
        else pixs->setPatternState(this->sequenceIndex * -1 + 3 );

    }

    switch (this->sequenceIndex) {
        case 0:
            setPixels(this->colorA, this->colorB, this->colorC);
            break;

        case 1:
            setPixels(this->colorB, this->colorC, this->colorA);
            break;

        case 2:
            setPixels(this->colorC, this->colorA, this->colorB);
            break;
    
        case -1:
            setPixels(this->colorC, this->colorA, this->colorB);
            break;

        case -2:
            setPixels(this->colorB, this->colorC, this->colorA);
            break;

    }
    pixs->setPatternTime(this->time - time);
}

void assPatPinWheel::setPixels(uint32_t color1, uint32_t color2, uint32_t color3) {

    for (int i = 0; i < 5; i++)
        pixs->getStrip().setPixelColor(this->pixSequenceA[i], color1);

    for (int i = 0; i < 5; i++)
        pixs->getStrip().setPixelColor(this->pixSequenceB[i], color2);

    for (int i = 0; i < 5; i++)
        pixs->getStrip().setPixelColor(this->pixSequenceC[i], color3);
}

void assPatPinWheel::setColor(uint32_t colorA, uint32_t colorB, uint32_t colorC) {
    this->colorA = colorA;
    this->colorB = colorB;
    this->colorC = colorC;
};