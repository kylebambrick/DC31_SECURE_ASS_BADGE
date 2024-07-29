#include "assG.h"
#include "assPixs.h"
#include "assPatRainbow.h"


assPatRainbow::assPatRainbow() : pixs(nullptr) {}


void assPatRainbow::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatRainbow::start(int num, int state, bool noupdate) {
  if (noupdate || state == -1) return;
  
  this->rainbowCycle = state;
  //debugln("Updating Rainbow to : " + String(rainbowCycle));


  //debugln("Current Last Time: " + String(this->timeToNextState) + " proposed next time " + String(num + millis()));
  int proposedValue = num + millis() - TRANSMIT_DELAY;  // Compute proposed value

  int lowerBound = this->timeToNextState * 0.95;  // Calculate 90% of current value
  int upperBound = timeToNextState * 1.05;  // Calculate 110% of current value

  // If the proposed value is outside of the 90%-110% range, update timeToNextState
  if (proposedValue < lowerBound || proposedValue > upperBound) {
      this->timeToNextState = proposedValue;
  }
}

void assPatRainbow::update(unsigned long currentTime) {
    if (currentTime >= this->timeToNextState) {
      this->timeToNextState = currentTime + this->speed;
      this->rainbowCycle = (this->rainbowCycle + 1) % 256;
      wheel();
      pixs->setPatternState(this->rainbowCycle);
    }
    for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++) {
      pixs->getStrip().setPixelColor(i, pixs->getStrip().Color(this->red, this->green, this->blue));
    }
    pixs->setPatternTime(this->timeToNextState - currentTime);
    pixs->setPatternState(this->rainbowCycle);
}

void assPatRainbow::reset() {
    this->rainbowCycle = random(255);
    this->timeToNextState = 0;
    this->red = 0;
    this->green = 0;
    this->blue = 0;
}

void assPatRainbow::setSpeed(int num) {
  this->speed = num;
}

void assPatRainbow::wheel() {
  int wheel = 255 - this->rainbowCycle;
  if (wheel < 85) {
    this->red = 255 - wheel * 3; 
    this->green = 0;
    this->blue = wheel * 3;
    return;
  }
  if (wheel < 170) {
    wheel -= 85;
    this->red = 0; 
    this->green = wheel * 3;
    this->blue = 255 - wheel * 3;
    return;
  }
  wheel -= 170;
  this->red = wheel * 3; 
  this->green = 255 - wheel * 3;
  this->blue = 0;
}
