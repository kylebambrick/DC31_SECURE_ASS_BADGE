#include "assPixs.h"
#include "assPatSnake.h"
#include "assG.h"

assPatSnake::assPatSnake() : pixs(nullptr)  {}

void assPatSnake::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatSnake::start(int time, int uniqueId, int speed, bool noupdate) {
    if (noupdate || uniqueId == -1) return;
    
    this->time = time + millis();
    if (speed > 0) this->speed = speed; 

    switch(uniqueId / 16) {
        case 0: 
            this->state = assSnakeState::FILLUP;
            break;
        case 1: 
            this->state = assSnakeState::UNUP;
            break;
        case 2: 
            this->state = assSnakeState::FILLDOWN;
            break;
        case 3: 
            this->state = assSnakeState::UNDOWN;
            break;
        default:
            this->state = assSnakeState::FILLUP;
            break;
    }
    this->sequenceIndex = uniqueId % 16 + 4;
}

void assPatSnake::update(unsigned long time) {
    if (time >= this->time) {
        this->time = time + this->speed;
        int stateValue = 0;
        switch(state) {
            case assSnakeState::FILLUP:
                this->sequenceIndex++;
                if (this->sequenceIndex > 20) {
                    state = assSnakeState::UNUP;
                    this->sequenceIndex = 4;
                }
                break;
            case assSnakeState::UNUP:
                stateValue = 1;
                this->sequenceIndex++;
                if (this->sequenceIndex > 20) {
                    state = assSnakeState::FILLDOWN;
                    this->sequenceIndex = 20;
                }
                break;
            case assSnakeState::FILLDOWN:
                stateValue = 2;
                this->sequenceIndex--;
                if (this->sequenceIndex < 4) {
                    state = assSnakeState::UNDOWN;
                    this->sequenceIndex = 20;
                }
                break;
            case assSnakeState::UNDOWN:
                stateValue = 3;
                this->sequenceIndex--;
                if (this->sequenceIndex < 4) {
                    state = assSnakeState::FILLUP;
                    this->sequenceIndex = 4;
                }
                break;
        }
        pixs->setPatternState(stateValue * 16 + (this->sequenceIndex - 4));
    }

    for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++) {
        pixs->getStrip().setPixelColor(i, colorOff);
        switch(state) {
            case assSnakeState::FILLUP:
                if (i <= this->sequenceIndex) pixs->getStrip().setPixelColor(i, this->color);
                break;
            case assSnakeState::UNUP:
                if (i >= this->sequenceIndex) pixs->getStrip().setPixelColor(i, this->color);
                break;
            case assSnakeState::FILLDOWN:
                if (i >= this->sequenceIndex) pixs->getStrip().setPixelColor(i, this->color);
                break;
            case assSnakeState::UNDOWN:
                if (i <= this->sequenceIndex) pixs->getStrip().setPixelColor(i, this->color);
                break;
        }
    }

    pixs->setPatternTime(this->time - time);
}

void assPatSnake::setColor(uint32_t color, uint32_t colorOff) { 
    this->color = color;
    this->colorOff = colorOff;
};