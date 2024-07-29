#include "assPixs.h"
#include "assG.h"

assPixs::assPixs()
: strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800) {
    blinkPattern = new assPatBlink();
    blinkPattern->setPixs(this);
    pulsePattern = new assPatPulse();
    pulsePattern->setPixs(this);
    sparklePattern = new assPatSparkle();
    sparklePattern->setPixs(this);
    rainbowPattern = new assPatRainbow();
    rainbowPattern->setPixs(this);
    rainbowRandomPattern = new assPatRainbowRandom();
    rainbowRandomPattern->setPixs(this);
    chaserPattern = new assPatChaser();
    chaserPattern->setPixs(this);
    snakePattern = new assPatSnake();
    snakePattern->setPixs(this);
    scanPattern = new assPatScan();
    scanPattern->setPixs(this);
    hypnoPattern = new assPatHypno();
    hypnoPattern->setPixs(this);
    randoPattern = new assPatRando();
    randoPattern->setPixs(this);
    pinPattern = new assPatPinWheel();
    pinPattern->setPixs(this);
    onebyPattern = new assPatOneBy();
    onebyPattern->setPixs(this);
    fillrandoPattern = new assPatRandoFill();
    fillrandoPattern->setPixs(this);
    pulsedPattern = new assPatPulseD();
    pulsedPattern->setPixs(this);
    flagPattern = new assPatFlag();
    flagPattern->setPixs(this);
    dripPattern = new assPatDrip();
    dripPattern->setPixs(this);
    circlePattern = new assPatCircle();
    circlePattern->setPixs(this);

    idleMouthPattern = new assPatIdle();
    idleMouthPattern->setPixs(this);
    blinkMPattern = new assPatBlinkMouth();
    blinkMPattern->setPixs(this);
    pulseMPattern = new assPatPulseMouth();
    pulseMPattern->setPixs(this);
    sparkleMPattern = new assPatSparkleMouth();
    sparkleMPattern->setPixs(this);
    leftPattern = new assPatLeft();
    leftPattern->setPixs(this);
    rightPattern = new assPatRight();
    rightPattern->setPixs(this);
}

void assPixs::init() {
    strip.begin();
    strip.setBrightness(PIXEL_BRIGHTNESS);
    strip.show();

    this->PATTERN_EYE = assPatternCore::NONE;
    this->PATTERN_MOUTH = assPatternMouth::IDLE;
    this->PATTERN_MOUTH_IDLE = assPatternMouth::IDLE;
    setPatternMouth(this->PATTERN_MOUTH);
}

void assPixs::render() {
    unsigned long time = millis();
    updateEyePattern(time);
    updateMouthPattern(time);
    strip.show();
    //pixelIO();
}

int assPixs::getBrightness() { return this->PIXEL_BRIGHTNESS; }

void assPixs::setBrightness(int num) { 
    if (num > 255) num = 255;
    if (num < 1) num = 1;
    this->PIXEL_BRIGHTNESS = num; 
}

void assPixs::pixelIO() {
    if (this->PIXEL_IO && millis() - this->PIXEL_IO_LAST_UPDATE >= PIXEL_ON) {
        this->PIXEL_IO_LAST_UPDATE = millis();
        this->PIXEL_IO = false;
        for(int i=PIXEL_MOUTH; i < PIXEL_COUNT; i++) { 
            strip.setPixelColor(i, strip.Color(0,0,0));
        }
    } else if (!this->PIXEL_IO && millis() - this->PIXEL_IO_LAST_UPDATE >= PIXEL_OFF) {
        this->PIXEL_IO_LAST_UPDATE = millis();
        this->PIXEL_IO = true;
    }

    strip.show();
}

void assPixs::eyecolor() {
    for (int i = PIXEL_MOUTH; i < PIXEL_COUNT; i++)
        strip.setPixelColor(i, this->COLOR);
}

void assPixs::mouthcolor() {
    for (int i = 0; i < PIXEL_MOUTH; i++)
        strip.setPixelColor(i, strip.Color(this->MOUTH_RED, this->MOUTH_GREEN, this->MOUTH_BLUE));
}

void assPixs::setColorMouth(int red, int green, int blue) {
    this->MOUTH_RED = red;
    this->MOUTH_GREEN = green;
    this->MOUTH_BLUE = blue;
}

void assPixs::talk(assMouthTalk talk) { idleMouthPattern->talk(talk); }

void assPixs::setPatternMouth(assPatternMouth pattern) {
    switch (pattern) {
        case assPatternMouth::LEFT:
            leftPattern->setColor(this->MOUTH_RED,this->MOUTH_GREEN,this->MOUTH_BLUE);
            leftPattern->reset();
            leftPattern->start(1);
            break;
        case assPatternMouth::RIGHT:
            rightPattern->setColor(this->MOUTH_RED,this->MOUTH_GREEN,this->MOUTH_BLUE);
            rightPattern->reset();
            rightPattern->start(1);
            break;
        case assPatternMouth::BLINK:
            blinkMPattern->setColor(this->MOUTH_RED,this->MOUTH_GREEN,this->MOUTH_BLUE);
            blinkMPattern->reset();
            blinkMPattern->start(1);
            break;
        case assPatternMouth::PULSE:
            pulseMPattern->setColor(100,0,0);
            pulseMPattern->start(1);
            break;
        case assPatternMouth::PULSELORA:
            pulseMPattern->setColor(0,0,100);
            pulseMPattern->start(1);
            break;
        case assPatternMouth::PULSEAUTON:
            pulseMPattern->setColor(0,100,0);
            pulseMPattern->start(1);
            break;
        case assPatternMouth::SPARKLE:
            sparkleMPattern->setColor(100,100,100);
            sparkleMPattern->start();
            break;
        default:
            idleMouthPattern->setColor(30,30,30);
            pattern = assPatternMouth::IDLE;
            break;
    }
    this->PATTERN_MOUTH = pattern;
}

void assPixs::updateMouthPattern(unsigned long time) {
    switch (PATTERN_MOUTH) {
        case assPatternMouth::STATIC:
            mouthcolor();
            break;
        case assPatternMouth::LEFT:
            leftPattern->update(time);
            break;
        case assPatternMouth::RIGHT:
            rightPattern->update(time);
            break;
        case assPatternMouth::BLINK:
            blinkMPattern->update(time);
            break;
        case assPatternMouth::PULSE:
            pulseMPattern->update(time);
            break;
        case assPatternMouth::PULSEAUTON:
            pulseMPattern->update(time);
            break;
        case assPatternMouth::PULSELORA:
            pulseMPattern->update(time);
            break;
        case assPatternMouth::SPARKLE:
            sparkleMPattern->update(time);
            break;
        default:
            idleMouthPattern->update(time);
            break;
    }
}

void assPixs::setCurrentEyePattern(assPatternCore pattern, uint32_t color, int diff, int time, int state, bool noupdate, uint32_t colorOff, uint32_t color3) { 
    this->PATTERN_EYE = pattern;
    this->patternTime = time;
    this->patternState = state;
    switch (pattern) { 

        case assPatternCore::NONE:
            setEyeColor(0x000000);
            break;

        case assPatternCore::COLOR:
            setEyeColor(color);
            break;
        
        case assPatternCore::PULSE:
            pulsePattern->setColor(color);
            pulsePattern->setSpeed(diff);
            pulsePattern->start(time, state, diff, noupdate);
            break;
        
        case assPatternCore::BLINK:
            blinkPattern->setColor(color, colorOff);
            blinkPattern->setSpeed(diff);
            //blinkPattern->start(time, state, diff, noupdate);
            break;

        case assPatternCore::SPARKLE:
            sparklePattern->setSpeed(diff);
            sparklePattern->setPixelsOn(5);
            sparklePattern->setColor(color, colorOff);
            //sparklePattern->start(time, diff, 50);
            break;

        case assPatternCore::SPARKLEONE:
            sparklePattern->setSpeed(diff);
            sparklePattern->setPixelsOn(1);
            sparklePattern->setColor(color, colorOff);
            //sparklePattern->start(time, diff, 50);
            break;

        case assPatternCore::SPARKLETEN:
            sparklePattern->setSpeed(diff);
            sparklePattern->setPixelsOn(10);
            sparklePattern->setColor(color, colorOff);
            //sparklePattern->start(time, diff, 50);
            break;

        case assPatternCore::CHASER:
            chaserPattern->setColor(color, colorOff);
            chaserPattern->setSpeed(diff);
            chaserPattern->setMode(1);
            //chaserPattern->start(time, state, 200, -3, noupdate);
            break;

        case assPatternCore::CHASERMINUS:
            chaserPattern->setColor(color, colorOff);
            chaserPattern->setSpeed(diff);
            chaserPattern->setMode(-1);
            //chaserPattern->start(time, state, 200, -3, noupdate);
            break;

        case assPatternCore::CHASERTHREE:
            chaserPattern->setColor(color, colorOff);
            chaserPattern->setSpeed(diff);
            chaserPattern->setMode(3);
            //chaserPattern->start(time, state, 200, -3, noupdate);
            break;

        case assPatternCore::CHASER3M:
            chaserPattern->setColor(color, colorOff);
            chaserPattern->setSpeed(diff);
            chaserPattern->setMode(-3);
            //chaserPattern->start(time, state, 200, -3, noupdate);
            break;

        case assPatternCore::SNAKE:
            snakePattern->setColor(color, colorOff);
            snakePattern->setSpeed(diff);
            //snakePattern->start(time, state, 300, noupdate);
            break;

        case assPatternCore::SCAN:
            scanPattern->setColor(color, colorOff);
            scanPattern->setSpeed(diff);
            //scanPattern->start(time, state, 200, noupdate);
            break;

        case assPatternCore::HYPNO:
            hypnoPattern->setColor(color, colorOff);
            hypnoPattern->setSpeed(diff);
            hypnoPattern->setDirection(1);
            //hypnoPattern->start(time, state, 300, 1, noupdate);
            break;

        case assPatternCore::HYPNOMINUS:
            hypnoPattern->setColor(color, colorOff);
            hypnoPattern->setSpeed(diff);
            hypnoPattern->setDirection(-1);
            //hypnoPattern->start(time, state, 300, 1, noupdate);
            break;

        case assPatternCore::RANDO:
            randoPattern->setSpeed(diff);
            //randoPattern->start(time, 200, noupdate);
            break;

        case assPatternCore::PINWHEEL:
            pinPattern->setColor(color, colorOff, color3);
            pinPattern->setSpeed(diff);
            pinPattern->setDirection(1);
            //pinPattern->start(time, state, 200, noupdate);
            break;

        case assPatternCore::PINWHEELMINUS:
            pinPattern->setColor(color, colorOff, color3);
            pinPattern->setSpeed(diff);
            pinPattern->setDirection(-1);
            //pinPattern->start(time, state, 200, noupdate);
            break;

        case assPatternCore::ONEBY:
            onebyPattern->setColor(color, colorOff);
            onebyPattern->setSpeed(diff);
            //onebyPattern->start(time, state, 200, noupdate);
            break;

        case assPatternCore::FILLRANDO:
            fillrandoPattern->setColor(color, colorOff);
            fillrandoPattern->setSpeed(diff);
            //fillrandoPattern->start(time, 200, noupdate);
            break;
        
        case assPatternCore::PULSED:
            pulsedPattern->setColor(color, colorOff);
            pulsedPattern->setSpeed(diff);
            //pulsedPattern->start(time, state, 20, noupdate);
            break;
            
        case assPatternCore::FLAG:
            //flagPattern->start(time, state, 300, noupdate);
            flagPattern->setSpeed(diff);
            flagPattern->setDirection(1);
            break;

        case assPatternCore::DRIP:
            dripPattern->setColor(color, colorOff);
            dripPattern->setSpeed(diff);
            //dripPattern->start(time, state, 300, noupdate);
            break;

        case assPatternCore::CIRCLE:
            circlePattern->setColor(color, colorOff);
            circlePattern->setSpeed(diff);
            //circlePattern->start(time, state, 200, noupdate);
            break;

        case assPatternCore::RAINBOW:
            rainbowPattern->setSpeed(diff);
            rainbowPattern->start(time, state, noupdate);
            break;

        case assPatternCore::RAINBOWRANDOM:
            //rainbowRandomPattern->start(state, noupdate);
            rainbowRandomPattern->reset();
            break;            

        default:
            setEyeColor(0x000000);
            break;

    }
}

void assPixs::updateEyePattern(unsigned long time) {
    switch (PATTERN_EYE) {

        case assPatternCore::NONE:
            eyecolor();
            break;    

        case assPatternCore::COLOR:
            eyecolor();
            break;

        case assPatternCore::SPARKLE:
            sparklePattern->update(time); 
            break;

        case assPatternCore::SPARKLEONE:
            sparklePattern->update(time); 
            break;

        case assPatternCore::SPARKLETEN:
            sparklePattern->update(time); 
            break;

        case assPatternCore::BLINK:
            blinkPattern->update(time); 
            break;

        case assPatternCore::PULSE:
            pulsePattern->update(time); 
            break;

        case assPatternCore::CHASER:
            chaserPattern->update(time); 
            break;

        case assPatternCore::CHASERMINUS:
            chaserPattern->update(time); 
            break;

        case assPatternCore::CHASERTHREE:
            chaserPattern->update(time); 
            break;

        case assPatternCore::CHASER3M:
            chaserPattern->update(time); 
            break;

        case assPatternCore::SNAKE:
            snakePattern->update(time); 
            break;

        case assPatternCore::SCAN:
            scanPattern->update(time); 
            break;

        case assPatternCore::HYPNO:
            hypnoPattern->update(time); 
            break;

        case assPatternCore::HYPNOMINUS:
            hypnoPattern->update(time); 
            break;

        case assPatternCore::RANDO:
            randoPattern->update(time); 
            break;

        case assPatternCore::PINWHEEL:
            pinPattern->update(time); 
            break;

        case assPatternCore::PINWHEELMINUS:
            pinPattern->update(time); 
            break;

        case assPatternCore::ONEBY:
            onebyPattern->update(time); 
            break;

        case assPatternCore::FILLRANDO:
            fillrandoPattern->update(time); 
            break;

        case assPatternCore::PULSED:
            pulsedPattern->update(time); 
            break;

        case assPatternCore::FLAG:
            flagPattern->update(time); 
            break;

        case assPatternCore::DRIP:
            dripPattern->update(time); 
            break;

        case assPatternCore::CIRCLE:
            circlePattern->update(time); 
            break;

        case assPatternCore::RAINBOW:
            rainbowPattern->update(time); 
            break;

        case assPatternCore::RAINBOWRANDOM:
            rainbowRandomPattern->update(time); 
            break;    

        default:
            break;
    }
}