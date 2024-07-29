#include "assPixs.h"
#include "assPatPulseMouth.h"
#include "assG.h"

assPatPulseMouth::assPatPulseMouth() 
    : pixs(nullptr), red(0), green(0), blue(0) {}


void assPatPulseMouth::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatPulseMouth::start(int bliks) {
    this->pulseBrightness = 1;
    this->pulseDirection = 1;
    this->blinks = bliks;
    this->PULSE_TIMER = 0;
    this->pulseMultiplier = 1;
}

void assPatPulseMouth::update(unsigned long time) {
    if (time >= this->PULSE_TIMER) {
        this->pulseBrightness += this->pulseDirection;
        if(this->pulseBrightness > 100) {
            this->pulseDirection = -1;
            this->pulseBrightness = 100;
        }
        if(this->pulseBrightness < 0) {
            this->pulseDirection = 1;
            this->pulseBrightness = 0;
        }

        this->pulseMultiplier = this->pulseBrightness / 100;

        this->PULSE_TIMER = time + this->PULSE_TIME;

        /*
        //debugln("time: " + String(time) +
            ", pulseBrightness: " + String(this->pulseBrightness, 6) +
            ", pulseDirection: " + String(this->pulseDirection) +
            ", pulseMultiplier: " + String(this->pulseMultiplier,6) +
            ", PULSE_TIMER: " + String(this->PULSE_TIMER));
            */

        if (this->pulseDirection == 1 && this->pulseBrightness == 0) {
            blinks--;
            if (blinks <= 0) pixs->resetPatternMouth();
        }
    }

    for(int i=0; i < PIXEL_MOUTH; i++) {
        pixs->getStrip().setPixelColor(i, pixs->getStrip().Color(int(red * pulseMultiplier), int(green * pulseMultiplier), int(blue * pulseMultiplier)));
    }

}

void assPatPulseMouth::setColor(int _red, int _green, int _blue) {
    this->red = _red;
    this->green = _green;
    this->blue = _blue;
}