#include "assPixs.h"
#include "assPatRandoFill.h"
#include "assG.h"

assPatRandoFill::assPatRandoFill() : pixs(nullptr)  {}

void assPatRandoFill::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatRandoFill::start(int time, int speed, bool noupdate) {
    if (noupdate) return;
    
    this->time = time + millis();

    if (speed > 0) this->speed = speed; 
}

void assPatRandoFill::update(unsigned long time) {
    if (time >= this->time) {
        this->time = time + this->speed;
        int empty_pixels[PIXEL_COUNT];
        int empty_count = 0;
        int filled_pixels[PIXEL_COUNT];
        int filled_count = 0;
        // Gather indices for zeros and ones
        for(int i = PIXEL_MOUTH; i < PIXEL_COUNT; ++i) {
            if (pixels[i] == 0) empty_pixels[empty_count++] = i;
            else filled_pixels[filled_count++] = i;
        }

        switch(state) {
            case assFillState::FILL:
                if (empty_count > 0) {
                    int index = empty_pixels[random(empty_count)];
                    pixels[index] = 1;
                } else {
                    state = assFillState::UNFILL;
                }
                break;
            case assFillState::UNFILL:
                if (filled_count > 0) {
                    int index = filled_pixels[random(filled_count)];
                    pixels[index] = 0;
                } else {
                    state = assFillState::FILL;
                }
                break;
        }
        pixs->setPatternState(1);
    }

    for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++) {
        if (pixels[i] == 0) pixs->getStrip().setPixelColor(i, this->colorOff);
        else pixs->getStrip().setPixelColor(i, this->color);
    }

    pixs->setPatternTime(this->time - time);
}


void assPatRandoFill::setColor(uint32_t color, uint32_t colorOff) { 
    this->color = color;
    this->colorOff = colorOff;
}