#include "assPixs.h"
#include "assPatSparkle.h"
#include "assG.h"

assPatSparkle::assPatSparkle() : pixs(nullptr) {
  for (int i = 0; i < PIXEL_COUNT; i++)
      selectedPixels[i] = 0;
}

void assPatSparkle::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatSparkle::start(unsigned long num, int _numOfPixelsOn, int _interval) {
    timeToNextState = num;
    numOfPixelsOn = _numOfPixelsOn;
    interval = _interval;
}

void assPatSparkle::update(unsigned long currentTime) {
    if (currentTime >= timeToNextState) {
        timeToNextState = currentTime + interval;
        setRandomValues();
    }

    for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++) {
        if (selectedPixels[i] == 1) {
            pixs->getStrip().setPixelColor(i, this->color);
        } else {
            pixs->getStrip().setPixelColor(i, this->colorOff);
        }
    }
}

void assPatSparkle::setRandomValues() {
  for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++)
    selectedPixels[i] = 0;

  for (int i = 0; i < numOfPixelsOn; ) {
    // Generate a random index between PIXEL_MOUTH and PIXEL_COUNT - 1
    int randomIndex = random(PIXEL_COUNT - PIXEL_MOUTH) + PIXEL_MOUTH;
    // Check if this index has already been set to 1
    if (selectedPixels[randomIndex] == 0) {
      selectedPixels[randomIndex] = 1;
      i++;
    }
  }
}

void assPatSparkle::setColor(uint32_t color, uint32_t colorOff) { 
    this->color = color;
    this->colorOff = colorOff;
}
