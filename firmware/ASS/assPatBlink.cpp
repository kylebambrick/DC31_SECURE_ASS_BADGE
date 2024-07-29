#include "assPixs.h"
#include "assPatBlink.h"
#include "assG.h"

assPatBlink::assPatBlink() : pixs(nullptr) {}


void assPatBlink::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatBlink::start(int num, int state, int diff, bool noupdate) {
    if (noupdate || state == -1) return;

    this->isOn = false;
    if (state == 1 ) this->isOn = !this->isOn;
    
    this->timeToNextState = num + millis();

    if (diff > 19) this->onOff = diff;
    /*
    debugln("Current Last Time: " + String(this->timeToNextState) + " proposed next time " + String(num + millis()));
    int proposedValue = num + millis() - TRANSMIT_DELAY;  // Compute proposed value

    int lowerBound = this->timeToNextState * 0.95;  // Calculate 90% of current value
    int upperBound = timeToNextState * 1.05;  // Calculate 110% of current value

    // If the proposed value is outside of the 90%-110% range, update timeToNextState
    if (proposedValue < lowerBound || proposedValue > upperBound) {
        this->timeToNextState = proposedValue;
    }*/
}

void assPatBlink::update(unsigned long currentTime) {
    if (currentTime >= timeToNextState) {  // Check against timeToNextState
        timeToNextState = currentTime + this->onOff;  // Set the next state time
        isOn = !isOn;
        pixs->setPatternState(-1);//isOn ? 1 : 0);
    }
    if (isOn) {
        for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++) {
            pixs->getStrip().setPixelColor(i, this->color);
        }
    } else {
        for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++) {
            pixs->getStrip().setPixelColor(i, this->colorOff);
        }
    }
    pixs->setPatternTime(timeToNextState - currentTime);
}

void assPatBlink::setColor(uint32_t color, uint32_t colorOff) { 
    this->color = color; 
    this->colorOff = colorOff;
};