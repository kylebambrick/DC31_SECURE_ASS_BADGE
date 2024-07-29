#include "assPixs.h"
#include "assPatFlag.h"
#include "assG.h"

assPatFlag::assPatFlag() : pixs(nullptr)  {}

void assPatFlag::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatFlag::start(int time, int state, int speed, bool noupdate) {
    if (noupdate || state == -1) return;
    
    this->time = time + millis();

    if (speed > 0) this->speed = speed; 

    if (state >= 0 && state <= 5) {
        this->sequenceIndex = state;
        this->direction = 1;
    }
    if (state >= 6 && state <= 12) {
        this->sequenceIndex = state - 6;
        this->direction = -1;
    }

}

void assPatFlag::update(unsigned long time) {
    if (time >= this->time) {  // Check against timeToNextState
        this->time = time + this->speed;  // Set the next state time

        this->sequenceIndex += this->direction;

        if (this->sequenceIndex < 0) this->sequenceIndex = 5;
        if (this->sequenceIndex > 5) this->sequenceIndex = 0;

        
        if (this->direction == 1) pixs->setPatternState(this->sequenceIndex);
        else pixs->setPatternState(this->sequenceIndex + 6);
        //debugln("Updated sequenceIndex to " + String(sequenceIndex));
    }

    switch (sequenceIndex) {
        case 0:
            setPixels(this->colorA, this->colorB, this->colorC, this->colorD, this->colorE, this->colorF);
            break;
        case 1:
            setPixels(this->colorF, this->colorA, this->colorB, this->colorC, this->colorD, this->colorE);
            break;
        case 2:
            setPixels(this->colorE, this->colorF, this->colorA, this->colorB, this->colorC, this->colorD);
            break;
        case 3:
            setPixels(this->colorD, this->colorE, this->colorF, this->colorA, this->colorB, this->colorC);
            break;
        case 4:
            setPixels(this->colorC, this->colorD, this->colorE, this->colorF, this->colorA, this->colorB);
            break;
        case 5:
            setPixels(this->colorB, this->colorC, this->colorD, this->colorE, this->colorF, this->colorA);
            break;
    }

    pixs->setPatternTime(this->time - time);
}

void assPatFlag::setPixels(uint32_t colorA, uint32_t colorB, uint32_t colorC, uint32_t colorD, uint32_t colorE, uint32_t colorF) {
    for (int i = 0; i < 2; i++) pixs->getStrip().setPixelColor(rowA[i], colorA);
    for (int i = 0; i < 3; i++) pixs->getStrip().setPixelColor(rowB[i], colorB);
    for (int i = 0; i < 4; i++) pixs->getStrip().setPixelColor(rowC[i], colorC);
    for (int i = 0; i < 3; i++) pixs->getStrip().setPixelColor(rowD[i], colorD);
    for (int i = 0; i < 2; i++) pixs->getStrip().setPixelColor(rowE[i], colorE);
    for (int i = 0; i < 1; i++) pixs->getStrip().setPixelColor(rowF[i], colorF);
}