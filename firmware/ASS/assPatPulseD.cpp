#include "assPixs.h"
#include "assPatPulseD.h"
#include "assG.h"

assPatPulseD::assPatPulseD() : pixs(nullptr) {}


void assPatPulseD::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatPulseD::start(int time, int state, int speed, bool noupdate) {
    if (noupdate || state == -1) return;

    this->direction = 1;
    if (state < 10) state = 10;
    if (state > 100) {
        state -= 100;
        this->direction = -1;
    }
    this->brightness = state;
    
    this->time = time + millis();

    if (speed > 0) this->interval = speed;
}

void assPatPulseD::update(unsigned long time) {
    if (time >= this->time) {
        this->brightness += this->direction;

        if(this->brightness > 100) {
            this->direction = -1;
            this->brightness = 100;
        }
        if(this->brightness < 10) {
            this->direction = 1;
            this->brightness = 10;
        }

        this->multiplier = this->brightness / 100.0;

        this->time = time + this->interval;

        if(this->direction == -1) pixs->setPatternState(int(100 + this->brightness));
        else pixs->setPatternState(int(this->brightness));

    }

    double inverseMultiplier = 1.0 - this->multiplier;

    for(int i = 0; i < 8; i++) {
        int pixelA = this->pixelsA[i];
        int pixelB = this->pixelsB[i];

        uint32_t colorA = pixs->getStrip().Color(int(redA * multiplier), int(greenA * multiplier), int(blueA * multiplier));
        uint32_t colorB = pixs->getStrip().Color(int(redB * inverseMultiplier), int(greenB * inverseMultiplier), int(blueB * inverseMultiplier));

        pixs->getStrip().setPixelColor(pixelA, colorA);
        pixs->getStrip().setPixelColor(pixelB, colorB);
    }

    pixs->setPatternTime(this->time - time);
}


void assPatPulseD::setColor(uint32_t colorA, uint32_t colorB) {
    this->redA =     (colorA >> 16) & 0xFF;
    this->greenA =   (colorA >> 8) & 0xFF;
    this->blueA =     colorA & 0xFF;
    this->redB =     (colorB >> 16) & 0xFF;
    this->greenB =   (colorB >> 8) & 0xFF;
    this->blueB =     colorB & 0xFF;
}