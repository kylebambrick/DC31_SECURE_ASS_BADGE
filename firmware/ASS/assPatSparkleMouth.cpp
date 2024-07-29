#include "assPixs.h"
#include "assPatSparkleMouth.h"
#include "assG.h"

assPatSparkleMouth::assPatSparkleMouth() 
    : pixs(nullptr), red(0), green(0), blue(0) {
      for (int i = 0; i < PIXEL_MOUTH; i++)
          selectedPixels[i] = 0;
    }

void assPatSparkleMouth::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatSparkleMouth::start() {
    DONE_TIMER = millis() + DONE_TIME;
    timeToNextState = 0;
    interval = 50;
    numOfPixelsOn = 2;
    for (int i = 0; i < PIXEL_MOUTH; i++)
        selectedPixels[i] = 0;
    //debugln("SPARKLE TIME");
}

void assPatSparkleMouth::update(unsigned long time) {
    //debugln("SPARKLE UPDATE");
    if (time >= timeToNextState) {
        timeToNextState = time + interval;
        setRandomValues();
        //debugln("SPARKLE NEXT");
    }

    for (int i = 0; i < PIXEL_MOUTH; i++) {

        //debugln("SPARKLE INFO : " + String(selectedPixels[i]));
        if (selectedPixels[i] == 1) {
            pixs->getStrip().setPixelColor(i, pixs->getStrip().Color(this->red, this->green, this->blue));
        } else {
            pixs->getStrip().setPixelColor(i, pixs->getStrip().Color(0, 0, 0));
        }
    }

    if (time >= DONE_TIMER) {
        //debugln("SPARKLE DONE");
        pixs->resetPatternMouth();
    }
}

void assPatSparkleMouth::setRandomValues() {
  
  for (int i = 0; i < PIXEL_MOUTH; i++)
    selectedPixels[i] = 0;

  for (int i = 0; i < numOfPixelsOn; ) {
    // Generate a random index between PIXEL_MOUTH and PIXEL_COUNT - 1
    int randomIndex = random(PIXEL_MOUTH);
    // Check if this index has already been set to 1
    if (selectedPixels[randomIndex] == 0) {
      selectedPixels[randomIndex] = 1;
      i++;
    }
  }
}

void assPatSparkleMouth::setColor(int _red, int _green, int _blue) {
    this->red = _red;
    this->green = _green;
    this->blue = _blue;
}
