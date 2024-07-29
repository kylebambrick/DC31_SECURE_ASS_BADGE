#include "assG.h"
#include "assPixs.h"
#include "assPatRainbowRandom.h"


assPatRainbowRandom::assPatRainbowRandom() : pixs(nullptr) {
    for(int i = 0; i < PIXEL_COUNT; i++) {
        pixelInfo[i].speed = random(10,200);
        pixelInfo[i].position = random(0, 256);
        pixelInfo[i].color = colorWheel(pixelInfo[i].position);
        pixelInfo[i].time = 0;
    }
}


void assPatRainbowRandom::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatRainbowRandom::start(int state, bool noupdate) {
    if (noupdate || state == -1) return;

    for(int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++) {
        pixelInfo[i].speed = random(5,100);
        pixelInfo[i].position = random(0, 256);
        pixelInfo[i].color = colorWheel(pixelInfo[i].position);
        pixelInfo[i].time = 0;
    }

    pixs->setPatternTime(0);
    pixs->setPatternState(-1);
}

void assPatRainbowRandom::reset() {
    for(int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++) {
        pixelInfo[i].speed = random(5,100);
        pixelInfo[i].position = random(0, 256);
        pixelInfo[i].color = colorWheel(pixelInfo[i].position);
        pixelInfo[i].time = 0;
    }
}

void assPatRainbowRandom::update(unsigned long time) {
    for(int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++) {
        if (time >= pixelInfo[i].time) {
            pixelInfo[i].time = time + pixelInfo[i].speed;
            pixelInfo[i].position = (pixelInfo[i].position + 1) % 256;
            pixelInfo[i].color = colorWheel(pixelInfo[i].position);
        }
        for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++)
            pixs->getStrip().setPixelColor(i, pixelInfo[i].color);
    }
}

uint32_t assPatRainbowRandom::colorWheel(int position) {
  int wheel = 255 - position;
  int red = 0;
  int green = 0;
  int blue = 0;

  if (wheel < 85) {
    red = 255 - wheel * 3; 
    green = 0;
    blue = wheel * 3;
  } else if (wheel < 170) {
    wheel -= 85;
    red = 0; 
    green = wheel * 3;
    blue = 255 - wheel * 3;
  } else {
    wheel -= 170;
    red = wheel * 3; 
    green = 255 - wheel * 3;
    blue = 0;
  }

  return pixs->getStrip().Color(red, green, blue);
}

