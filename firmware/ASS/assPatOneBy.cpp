#include "assPixs.h"
#include "assPatOneBy.h"
#include "assG.h"

assPatOneBy::assPatOneBy() : pixs(nullptr)  {}

void assPatOneBy::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatOneBy::start(int time, int uniqueId, int speed, bool noupdate) {
    if (noupdate || uniqueId == -1) return;
    
    this->time = time + millis();

    if (speed > 0) this->speed = speed; 

    switch(uniqueId / 16) {
        case 0: 
            this->state = assOneState::UP;
            break;
        case 1: 
            this->state = assOneState::DOWN;
            break;
    }

    this->sequenceIndex = uniqueId % 16 + 4;
}

void assPatOneBy::update(unsigned long time) {
    if (time >= this->time) {
        this->time = time + this->speed;
        int stateValue = 0;
        switch(state) {
            case assOneState::UP:
                this->sequenceIndex++;
                if (this->sequenceIndex > 20) {
                    state = assOneState::DOWN;
                    this->sequenceIndex = 20;
                }
                break;
            case assOneState::DOWN:
                stateValue = 1;
                this->sequenceIndex--;
                if (this->sequenceIndex < 4) {
                    state = assOneState::UP;
                    this->sequenceIndex = 4;
                }
                break;
        }
        pixs->setPatternState(stateValue * 16 + (this->sequenceIndex - 4));
    }

    for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++)
        pixs->getStrip().setPixelColor(i, this->colorOff);
    
    pixs->getStrip().setPixelColor(this->sequenceIndex, this->color);

    pixs->setPatternTime(this->time - time);
}

void assPatOneBy::setColor(uint32_t color, uint32_t colorOff) { 
    this->color = color;
    this->colorOff = colorOff;
}