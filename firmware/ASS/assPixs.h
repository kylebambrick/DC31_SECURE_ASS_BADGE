#ifndef ASSPIXS_H
#define ASSPIXS_H

#include <Adafruit_NeoPixel.h>

#include "assFSM.h"
#include "assG.h"

#include "assPatBlink.h"
#include "assPatSparkle.h"
#include "assPatRainbow.h"
#include "assPatChaser.h"
#include "assPatSnake.h"
#include "assPatPulse.h"
#include "assPatRainbowRandom.h"
#include "assPatScan.h"
#include "assPatHypno.h"
#include "assPatRando.h"
#include "assPatPinWheel.h"
#include "assPatOneBy.h"
#include "assPatRandoFill.h"
#include "assPatPulseD.h"
#include "assPatFlag.h"
#include "assPatDrip.h"
#include "assPatCircle.h"

#include "assPatBlinkMouth.h"
#include "assPatPulseMouth.h"
#include "assPatSparkleMouth.h"
#include "assPatLeft.h"
#include "assPatRight.h"
#include "assPatIdle.h"

enum class assPatternEyes;
enum class assPatternMouth;

class assPixs {
        
public:
    assPixs();
    void init();
    void render();
    void setPatternMouth(assPatternMouth pattern);
    void setPatternMouthDefault(assPatternMouth pattern) { this->PATTERN_MOUTH_IDLE = pattern; };
    void resetPatternMouth() { this->PATTERN_MOUTH = this->PATTERN_MOUTH_IDLE; };
    void setColorMouth(int red, int green, int blue);
    void setCurrentEyePattern(assPatternCore pattern, uint32_t color = 0xFFFFFF, int diff = 200, int time = 0, int state = -1, bool noupdate = true, uint32_t colorOff = 0x000000, uint32_t color3 = 0x00FF00);
    void updateEyePattern(unsigned long currentTime);
    void updateMouthPattern(unsigned long currentTime);
    Adafruit_NeoPixel& getStrip() { return this->strip; };
    int getPatternState() { return this->patternState; };
    int getPatternTime() { return this->patternTime; };
    void setPatternState(int state) { this->patternState = state; };
    void setPatternTime(int time) { this->patternTime = time; };
    void talk(assMouthTalk talk);
    int getBrightness();
    void setBrightness(int num);

private:
    Adafruit_NeoPixel strip;

    assPatBlink *blinkPattern;
    assPatPulse *pulsePattern;
    assPatSparkle *sparklePattern;
    assPatRainbow *rainbowPattern;
    assPatRainbowRandom *rainbowRandomPattern;
    assPatChaser *chaserPattern;
    assPatSnake *snakePattern;
    assPatScan *scanPattern;
    assPatHypno *hypnoPattern;
    assPatRando *randoPattern;
    assPatPinWheel *pinPattern;
    assPatOneBy *onebyPattern;
    assPatRandoFill *fillrandoPattern;
    assPatPulseD *pulsedPattern;
    assPatFlag *flagPattern;
    assPatDrip *dripPattern;
    assPatCircle *circlePattern;
    
    assPatBlinkMouth *blinkMPattern;
    assPatPulseMouth *pulseMPattern;
    assPatSparkleMouth *sparkleMPattern;
    assPatLeft *leftPattern;
    assPatRight *rightPattern;
    assPatIdle *idleMouthPattern;

    assPatternCore PATTERN_EYE;
    assPatternMouth PATTERN_MOUTH;
    assPatternMouth PATTERN_MOUTH_IDLE;

    int patternState = 0;
    int patternTime = 0;

    int MOUTH_RED = 20;
    int MOUTH_GREEN = 20;
    int MOUTH_BLUE = 20;

    uint32_t COLOR = 0x000000;

    bool PIXEL_IO = true;
    int PIXEL_IO_LAST_UPDATE = 0;
    int PIXEL_ON = 7; // duration in ms the pixels should stay ON
    int PIXEL_OFF = 1; // duration in ms the pixels should stay OFF
    int PIXEL_BRIGHTNESS = 25;  // adjust as necessary, range from 0 to 255

    void pixelIO();
    void eyecolor();
    void mouthcolor();
    void setEyeColor(uint32_t color) { this->COLOR = color; }
    
};

#endif // ASSPIXS_H
