#include "assPixs.h"
#include "assPatBlinkMouth.h"
#include "assG.h"

assPatBlinkMouth::assPatBlinkMouth() 
    : pixs(nullptr), red(0), green(0), blue(0), isOn(false), timeToNextState(0), timeOn(500), timeOff(500), blinks(2) {}


void assPatBlinkMouth::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatBlinkMouth::start(int bliks) {
    timeToNextState = 0;  // Set the time to the next state
    isOn = false;
    for(int i=0; i < PIXEL_MOUTH; i++) {
        pixs->getStrip().setPixelColor(i, pixs->getStrip().Color(0, 0, 0));
    }
    blinks = bliks * 2;
}

void assPatBlinkMouth::update(unsigned long currentTime) {
    if (currentTime >= timeToNextState) {  // Check against timeToNextState
        timeToNextState = currentTime + (isOn ? timeOff : timeOn);  // Set the next state time
        isOn = !isOn;
        blinks--;
        if (blinks < 0) pixs->resetPatternMouth();
    }
    if (isOn) {
        for(int i=0; i < PIXEL_MOUTH; i++) {
            pixs->getStrip().setPixelColor(i, pixs->getStrip().Color(red, green, blue));
        }
    } else {
        for(int i=0; i < PIXEL_MOUTH; i++) {
            pixs->getStrip().setPixelColor(i, pixs->getStrip().Color(0, 0, 0));
        }
    }
}

void assPatBlinkMouth::setColor(int _red, int _green, int _blue) {
    this->red = _red;
    this->green = _green;
    this->blue = _blue;
}

void assPatBlinkMouth::setTimeOnOff(unsigned long _timeOn, unsigned long _timeOff) {
    this->timeOn = _timeOn;
    this->timeOff = _timeOff;
}

void assPatBlinkMouth::reset() {
    isOn = false;
    timeToNextState = 0;  // Reset time to the next state
    timeOn = 500;  // Reset time that the LED is on
    timeOff = 500;  // Reset time that the LED is off
    blinks = 2;
}

/*
int pulseRed;
int pulseGreen;
int pulseBlue;
int pulseBrightness;
int pulseDirection = -1;  // 1 for increasing brightness, -1 for decreasing
void pulse(int red, int green, int blue, int n) {
    unsigned long currentMillis = millis();

    if (!isPatternInitializedMouth) {
        isPatternInitializedMouth = true;
        blinks = n;
        pulseBrightness = PIXEL_BRIGHTNESS;
        pulseRed = red;
        pulseGreen = green;
        pulseBlue = blue;
    }

    if (currentMillis - PATTERN_STEP_START_TIME_MOUTH >= 10) {
        pulseBrightness += pulseDirection;
        if(pulseBrightness >= PIXEL_BRIGHTNESS) pulseDirection = -1;
        if(pulseBrightness <= 0) pulseDirection = 1;

        PATTERN_STEP_START_TIME_MOUTH = currentMillis;

        if (pulseDirection == 1 && pulseBrightness == 0) {
            blinks--;
            if (blinks < 0) PIXEL_CYCLE_DONE_MOUTH = true;
        }
    }

    for(int i=0; i < PIXEL_MOUTH; i++) {
        // scale the RGB values by the brightness level
        strip.setPixelColor(i, strip.Color((pulseRed * pulseBrightness) / PIXEL_BRIGHTNESS, 
                                           (pulseGreen * pulseBrightness) / PIXEL_BRIGHTNESS, 
                                           (pulseBlue * pulseBrightness) / PIXEL_BRIGHTNESS));
    }
}
*/