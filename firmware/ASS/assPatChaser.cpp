#include "assPixs.h"
#include "assPatChaser.h"
#include "assG.h"

assPatChaser::assPatChaser() : pixs(nullptr)  {}

void assPatChaser::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatChaser::start(int time, int state, int speed, int mode, bool noupdate) {
    if (noupdate || state == -1) return;
    
    this->timeToNextState = time + millis();

    if (speed > 0) this->speed = speed; 

    if (mode == 1 || mode == 3 || mode == -1 || mode == -3) this->mode = mode;

    if (state >= 0 && state <= 8) this->sequenceIndex = state;
}

void assPatChaser::update(unsigned long time) {
    if (time >= this->timeToNextState) {  // Check against timeToNextState
        this->timeToNextState = time + this->speed;  // Set the next state time

        if (mode > 0 ) this->sequenceIndex++;
        else  this->sequenceIndex--;

        switch (mode) {
            case 1:
                if (this->sequenceIndex > 8) this->sequenceIndex = 0;
                break;
            case 3:
                if (this->sequenceIndex > 2) this->sequenceIndex = 0;
                break;
            case -1:
                if (this->sequenceIndex < 0) this->sequenceIndex = 8;
                break;
            case -3:
                if (this->sequenceIndex < 0) this->sequenceIndex = 2;
                break;
        }

        pixs->setPatternState(this->sequenceIndex);
        //debugln("Chasing Index: " + String(sequenceIndex) + " pixel: " + String(pixSequence[sequenceIndex]));
    }

    for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++)
        pixs->getStrip().setPixelColor(i, 0x000000);

    for (int i = 0; i < 10; i++) 
        pixs->getStrip().setPixelColor(this->pixSequence[i], this->colorOff);

    if (mode == 1 || mode == -1)
        pixs->getStrip().setPixelColor(this->pixSequence[this->sequenceIndex], this->color);
    else if (mode == 3 || mode == -3) {
        pixs->getStrip().setPixelColor(this->pixSequence[this->sequenceIndex], this->color);
        pixs->getStrip().setPixelColor(this->pixSequence[this->sequenceIndex + 3], this->color);
        pixs->getStrip().setPixelColor(this->pixSequence[this->sequenceIndex + 6], this->color);
    }

    pixs->setPatternTime(this->timeToNextState - time);
}

void assPatChaser::setColor(uint32_t color, uint32_t colorOff) { 
    this->color = color; 
    this->colorOff = colorOff;
};