#include "assPixs.h"
#include "assPatRight.h"
#include "assG.h"

assPatRight::assPatRight() 
    : pixs(nullptr), red(0), green(0), blue(0), spot(0), blinks(1), startTime(0) {}


void assPatRight::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatRight::start(int n) {
    blinks = n;
    startTime = millis();
}

void assPatRight::update(unsigned long currentTime) {
    for(int i=0; i < PIXEL_MOUTH; i++) {
        pixs->getStrip().setPixelColor(i, pixs->getStrip().Color(red, green, blue));
        if (i == spot) pixs->getStrip().setPixelColor(i, pixs->getStrip().Color(0, 0, 0));
    }

    if (currentTime - startTime >= 200) {
        startTime = currentTime;
        spot++;
        if (spot > 4) {
            spot = 0;
            blinks--;
            if (blinks < 1) {
                pixs->resetPatternMouth();
            }
        }
    }
}

void assPatRight::setColor(int _red, int _green, int _blue) {
    this->red = _red;
    this->green = _green;
    this->blue = _blue;
}

void assPatRight::reset() {
    spot = 0;
    blinks = 1;
}
