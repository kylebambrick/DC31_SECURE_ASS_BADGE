#include "assPixs.h"
#include "assPatPulse.h"
#include "assG.h"

assPatPulse::assPatPulse() 
    : pixs(nullptr), red(0), green(0), blue(0) {}


void assPatPulse::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatPulse::start(int num, int state, int diff, bool noupdate) {
    //debugln("PULSE START");
    if (noupdate || state == -1) return;

    this->pulseDirection = 1;
    if (state < 10) state = 10;
    if (state > 100) {
        state -= 100;
        this->pulseDirection = -1;
    }
    this->pulseBrightness = state;
    //debugln("PULSE SET");
    
    this->timeToNextState = num + millis();

    if (diff > 0) this->pulseInterval = diff;

    /*Doesn't matter given the tiny time between iterations. Might as well be 0.
    unsigned long time = millis();

    debugln("Current Last Time: " + String(this->timeToNextState) + " proposed next time " + String(num + millis()));
    int proposedValue = num - TRANSMIT_DELAY;  // Compute proposed value

    double lowerBound = (this->timeToNextState - time) * 0.95;  // Calculate 90% of current value
    double upperBound = (this->timeToNextState - time) * 1.05;  // Calculate 110% of current value

    // If the proposed value is outside of the 90%-110% range, update timeToNextState
    if (proposedValue < lowerBound || proposedValue > upperBound) {
        this->timeToNextState = proposedValue + time;
    }*/
    //debugln("PULSE SET TIME");
}

void assPatPulse::update(unsigned long time) {
    if (time >= this->timeToNextState) {  // Check against timeToNextState
        //debugln("PULSE UPDATE");
        this->pulseBrightness += this->pulseDirection;

        if(this->pulseBrightness > 100) {
            this->pulseDirection = -1;
            this->pulseBrightness = 100;
        }
        if(this->pulseBrightness < 10) {
            this->pulseDirection = 1;
            this->pulseBrightness = 10;
        }

        this->pulseMultiplier = this->pulseBrightness / 100;

        this->timeToNextState = time + this->pulseInterval;

        if(this->pulseDirection == -1) pixs->setPatternState(int(100 + this->pulseBrightness));
        else pixs->setPatternState(int(this->pulseBrightness));

    }

    for(int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++) {
        pixs->getStrip().setPixelColor(i, pixs->getStrip().Color(int(red * pulseMultiplier), int(green * pulseMultiplier), int(blue * pulseMultiplier)));
    }

    pixs->setPatternTime(timeToNextState - time);
}

void assPatPulse::setColor(uint32_t color) { 
    this->red =     (color >> 16) & 0xFF;
    this->green =   (color >> 8) & 0xFF;
    this->blue =     color & 0xFF;
};
