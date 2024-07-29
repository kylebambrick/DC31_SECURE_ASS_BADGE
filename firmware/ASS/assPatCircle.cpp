#include "assPixs.h"
#include "assPatCircle.h"
#include "assG.h"

assPatCircle::assPatCircle() : pixs(nullptr)  {}

void assPatCircle::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatCircle::start(int time, int uniqueID, int speed, bool noupdate) {
    if (noupdate || uniqueID == -1) return;
    
    this->time = time + millis();
    if (speed > 0) this->speed = speed; 

    switch(uniqueID / 16) {
        case 0: 
            this->state = assCircleState::FILLUP;
            break;
        case 1: 
            this->state = assCircleState::UNUP;
            break;
        case 2: 
            this->state = assCircleState::FILLDOWN;
            break;
        case 3: 
            this->state = assCircleState::UNDOWN;
            break;
        default:
            this->state = assCircleState::FILLUP;
            break;
    }
    this->sequenceIndex = uniqueID % 16 + 4;
}

void assPatCircle::update(unsigned long time) {
    if (time >= this->time) {  // Check against timeToNextState
        this->time = time + this->speed;  // Set the next state time
        int stateValue = 0;

        switch(state) {
            case assCircleState::FILLUP:
                this->sequenceIndex++;
                if (this->sequenceIndex > 10) {
                    state = assCircleState::UNUP;
                    this->sequenceIndex = -1;
                }
                break;
            case assCircleState::UNUP:
                stateValue = 1;
                this->sequenceIndex++;
                if (this->sequenceIndex > 10) {
                    state = assCircleState::FILLDOWN;
                    this->sequenceIndex = 10;
                }
                break;
            case assCircleState::FILLDOWN:
                stateValue = 2;
                this->sequenceIndex--;
                if (this->sequenceIndex < -1) {
                    state = assCircleState::UNDOWN;
                    this->sequenceIndex = 10;
                }
                break;
            case assCircleState::UNDOWN:
                stateValue = 3;
                this->sequenceIndex--;
                if (this->sequenceIndex < -1) {
                    state = assCircleState::FILLUP;
                    this->sequenceIndex = -1;
                }
                break;
        }

        pixs->setPatternState(this->sequenceIndex);
    }

    for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++)
        pixs->getStrip().setPixelColor(i, 0x000000);

    for (int i = 0; i < 10; i++) {
        switch(state) {
            case assCircleState::FILLUP:
                //debugln("FILLUP " + String(i));
                if (i > this->sequenceIndex) pixs->getStrip().setPixelColor(pixSequence[i], this->colorOff);
                else pixs->getStrip().setPixelColor(pixSequence[i], this->color);
                break;
            case assCircleState::UNUP:
                //debugln("UNUP " + String(i));
                if (i >= this->sequenceIndex) pixs->getStrip().setPixelColor(pixSequence[i], this->color);
                else pixs->getStrip().setPixelColor(pixSequence[i], this->colorOff);
                break;
            case assCircleState::FILLDOWN:
                //debugln("FILLDOWN " + String(i));
                if (i < this->sequenceIndex) pixs->getStrip().setPixelColor(pixSequence[i], this->colorOff);
                else pixs->getStrip().setPixelColor(pixSequence[i], this->color);
                pixs->getStrip().setPixelColor(pixSequence[0], this->color);
                break;
            case assCircleState::UNDOWN:
                //debugln("UNDOWN " + String(i));
                if (i <= this->sequenceIndex) pixs->getStrip().setPixelColor(pixSequence[i], this->color);
                else pixs->getStrip().setPixelColor(pixSequence[i], this->colorOff);
                pixs->getStrip().setPixelColor(pixSequence[0], this->colorOff);
                break;
        }
    }

    pixs->setPatternTime(this->time - time);
}

void assPatCircle::setColor(uint32_t color, uint32_t colorOff) { 
    this->color = color;
    this->colorOff = colorOff;
};