// assPatDrip.cpp
#include "assPixs.h"
#include "assPatDrip.h"
#include "assG.h"
#include <algorithm>
#include <cstdlib>

assPatDrip::assPatDrip() : pixs(nullptr) {
    nodes.push_back({5,      false,      6,      13,        0});
    nodes.push_back({6,      false,      12,     13,        0});
    nodes.push_back({7,      false,      11,     12,        0});
    nodes.push_back({8,      false,      10,     7,         0});
    nodes.push_back({9,      false,      8,      10,        0});
    nodes.push_back({10,     false,      11,     19,        0});
    nodes.push_back({11,     false,      17,     19,        14});
    nodes.push_back({12,     false,      11,     15,        0});
    nodes.push_back({13,     false,      14,     15,        0});
    nodes.push_back({14,     false,      15,     16,        17});
    nodes.push_back({15,     false,      16,     0,         0});
    nodes.push_back({16,     true,       0,      0,         0});
    nodes.push_back({17,     true,       0,      0,         0});
    nodes.push_back({18,     true,       0,      0,         0});
    nodes.push_back({19,     false,      18,     0,         0});
}

void assPatDrip::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatDrip::start(int time, int state, int speed, bool noupdate) {
    if (noupdate || state == -1) return;
    
    this->time = time + millis();

    if (speed > 0) this->speed = speed; 
}

void assPatDrip::update(unsigned long time) {
    if (time >= this->time) {
        this->time = time + this->speed;
        if (state[4] == false) state[4] = true; // Causes one cycle of all off
        else {
            std::vector<int> eligibleNodes;;
            for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++) {
                if (!state[i]) {
                    for (const auto& n : nodes) {
                        if (n.pixel == i) {
                            if (state[n.aboveA] || state[n.aboveB] || state[n.aboveC] || n.topNode)
                                eligibleNodes.push_back(i);
                            break;
                        }
                    }
                }
            }
            if (eligibleNodes.empty()) // All 15 on so turn them off
                for (int i = 0; i < PIXEL_COUNT; i++) state[i] = false; 
            else {
                int randomIndex = random(eligibleNodes.size()); // choose a random index
                int randomNode = eligibleNodes[randomIndex];
                state[randomNode] = true;
            }
        }
    }

    for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++) {
        if (state[i]) pixs->getStrip().setPixelColor(i, color);
        else pixs->getStrip().setPixelColor(i, colorOff);
    }

    pixs->setPatternTime(this->time - time);
}

void assPatDrip::setColor(uint32_t color, uint32_t colorOff) { 
    this->color = color;
    this->colorOff = colorOff;
}