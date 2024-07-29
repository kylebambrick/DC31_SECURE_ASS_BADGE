#include "assG.h"
#include "assPixs.h"
#include "assPatIdle.h"

assPatIdle::assPatIdle() 
    : pixs(nullptr), red(0), green(0), blue(0) {}

void assPatIdle::setPixs(assPixs* pixs) {
  this->pixs = pixs;
}

void assPatIdle::setColor(int red, int green, int blue) {
    this->red = red;
    this->blue = blue;
    this->green = green;
}

void assPatIdle::update(unsigned long time) {
    for(int i = 0; i < PIXEL_MOUTH; i++) {
        switch(pixelInfo[i].state) {
            case assMouthState::START:
                pixs->getStrip().setPixelColor(i, pixs->getStrip().Color(0, 0, 0));
                //debugln(("START " + String(time) + " " + String(pixelInfo[i].timer)));
                if (time >= pixelInfo[i].timer) {
                    pixelInfo[i].state = assMouthState::ON;
                    pixelInfo[i].timer = time + TIME_ON;
                }
                break;
            case assMouthState::ON:
                //debugln(("ON " + String(time) + " " + String(pixelInfo[i].timer)));
                pixs->getStrip().setPixelColor(i, pixelInfo[i].color);
                if (time >= pixelInfo[i].timer) {
                    pixelInfo[i].state = assMouthState::OFF;
                    pixelInfo[i].timer = time + TIME_OFF_OFF;
                }
                break;
            case assMouthState::OFF:
                //debugln(("OFF " + String(time) + " " + String(pixelInfo[i].timer)));
                pixs->getStrip().setPixelColor(i, pixs->getStrip().Color(0, 0, 0));
                if (time >= pixelInfo[i].timer) {
                    pixelInfo[i].state = assMouthState::IDLE;
                    pixelInfo[i].timer = 0;
                    pixelInfo[i].color = pixs->getStrip().Color(this->red, this->green, this->blue);
                }
                break;
            default:
                //debugln(("DEFAULT " + String(i)));
                pixs->getStrip().setPixelColor(i, pixs->getStrip().Color(this->red, this->green, this->blue));
                break;
        }
    }
}

void assPatIdle::talk(assMouthTalk talk) {
    int idlePixels[PIXEL_MOUTH];
    int idleCount = 0;

    for(int i = 0; i < PIXEL_MOUTH; i++) {
        if(pixelInfo[i].state == assMouthState::IDLE) {
            idlePixels[idleCount] = i;
            idleCount++;
        }
    }
    if(idleCount <= 0) return;
    int randomPixel = idlePixels[random(idleCount)];
    pixelInfo[randomPixel].state = assMouthState::START;
    pixelInfo[randomPixel].timer = millis() + TIME_OFF;

    switch(talk) {
        case assMouthTalk::WIFI_200:
            //debugln("Talking about WIFI_200");
            pixelInfo[randomPixel].color = pixs->getStrip().Color(20, 20, 100);
            break;
        case assMouthTalk::WIFI_404:
            pixelInfo[randomPixel].color = pixs->getStrip().Color(10, 30, 60);
            break;
        case assMouthTalk::WIFI_200POST:
            //debugln("Talking about WIFI_200POST");
            pixelInfo[randomPixel].color = pixs->getStrip().Color(0, 40, 60);
            break;
        case assMouthTalk::WIFI_CONNECT:
            pixelInfo[randomPixel].color = pixs->getStrip().Color(0, 0, 60);
            break;
        case assMouthTalk::WIFI_HAXOR:
            pixelInfo[randomPixel].color = pixs->getStrip().Color(0, 60, 100);
            break;
        case assMouthTalk::LORA_BADPACKET:
            //debugln("Talking about LORA_BADPACKET");
            pixelInfo[randomPixel].color = pixs->getStrip().Color(100, 20, 20);
            break;
        case assMouthTalk::LORA_RECEIPT:
            //debugln("Talking about LORA_RECEIPT");
            pixelInfo[randomPixel].color = pixs->getStrip().Color(20, 100, 20);
            break;
        case assMouthTalk::LORA_LEADCHANGE:
            //debugln("Talking about LORA_LEADCHANGE");
            pixelInfo[randomPixel].color = pixs->getStrip().Color(0, 60, 40);
            break;
        case assMouthTalk::NEWFRIEND:
            pixelInfo[randomPixel].color = pixs->getStrip().Color(0, 60, 20);
            break;
        case assMouthTalk::UNLOCK:
            pixelInfo[randomPixel].color = pixs->getStrip().Color(100, 80, 0);
            break;
        case assMouthTalk::BORED:
            pixelInfo[randomPixel].color = pixs->getStrip().Color(20, 20, 20);
            break;
        case assMouthTalk::TALK:
            pixelInfo[randomPixel].color = pixs->getStrip().Color(100, 100, 100);
            break;
        case assMouthTalk::FREAK:
            pixelInfo[randomPixel].color = pixs->getStrip().Color(100, 100, 100);
            break;
        default:
            break;
    }
}