#ifndef ASSPATBLINKMOUTH_H
#define ASSPATBLINKMOUTH_H

class assPixs;

class assPatBlinkMouth {
public:
    assPatBlinkMouth();
    void setPixs(assPixs* pixs);
    void start(int bliks);
    void update(unsigned long currentTime);
    void reset();
    void setColor(int red, int green, int blue);
    void setTimeOnOff(unsigned long timeOn, unsigned long timeOff);

private:
    assPixs* pixs;
    int red, green, blue;
    bool isOn;
    int blinks;
    unsigned long timeToNextState;  // time to the next state change
    unsigned long timeOn;  // time that the LED is on
    unsigned long timeOff;  // time that the LED is off
};

#endif // ASSPATBLINKMOUTH_H