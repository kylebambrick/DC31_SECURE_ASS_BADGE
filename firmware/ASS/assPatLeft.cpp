#include "assPixs.h"
#include "assPatLeft.h"
#include "assG.h"

assPatLeft::assPatLeft() 
    : pixs(nullptr), red(0), green(0), blue(0), spot(4), blinks(1), startTime(0) {}


void assPatLeft::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatLeft::start(int n) {
    blinks = n;
    startTime = millis();
}

void assPatLeft::update(unsigned long currentTime) {
    for(int i=0; i < PIXEL_MOUTH; i++) {
        pixs->getStrip().setPixelColor(i, pixs->getStrip().Color(red, green, blue));
        if (i == spot) pixs->getStrip().setPixelColor(i, pixs->getStrip().Color(0, 0, 0));
    }

    if (currentTime - startTime >= 200) {
        startTime = currentTime;
        spot--;
        if (spot < 0) {
            spot = 4;
            blinks--;
            if (blinks < 1) {
                pixs->resetPatternMouth();
            }
        }
    }
}

void assPatLeft::setColor(int _red, int _green, int _blue) {
    this->red = _red;
    this->green = _green;
    this->blue = _blue;
}

void assPatLeft::reset() {
    spot = 4;
    blinks = 1;
}
