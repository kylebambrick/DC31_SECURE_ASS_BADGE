#ifndef ASSFSM_H
#define ASSFSM_H

#include <Arduino.h>
#include <cstring>
#include <vector>

#include "assG.h"
#include "assWifi.h"
#include "assLoRa.h"
#include "assData.h"
#include "assPixs.h"
#include "assButts.h"

class assWifi;
class assLoRa;
class assData;
class assPixs;
class assButts;

class assFSM {
public:
    assFSM(assWifi* wifi, assLoRa* lora, assData* data, assPixs* pixs, assButts* butts);
    void init();
    void refresh();
    void setState(assStateName state_name, assStates state);
    void setFriend(const char* new_friend);
    bool getMode();
    //void nextPatternEyes();
    //void previousPatternEyes();
    bool setPatternWeb(String id);
    void nextCategory();
    void nextInLine();
    void leadChange(int pat, int time, int state, bool noupdate);
    void setCurrentEyePattern(assPatternEyes pattern, int time = 0, int state = 0, bool noupdate = false);
    void setPatternEyes(assPatternEyes pattern, int num, int state, bool noupdate = false);
    void setEyesInit(int pattern);
    static std::vector<assPatternEyes> unlockedPatternsEyes;
    int getPatInt(assPatternEyes pat);
    int getPatIndexCat(assPatternEyes pat);
    int getPatIndexPlace(assPatternEyes pat);
    assPatternEyes getPatEnum(int num);
    assPatternEyes getPatEnumFromNums(int cat, int place);
    int getPatIntCurrent() { return getPatInt(PATTERN_EYE_CURRENT); };
    int getPatIntAnon() { return getPatInt(PATTERN_EYE_SELECT); };
    int getPatternState();
    int getPatternTime();
    void setPatternMouth(assPatternMouth pattern);
    String getName() { return this->info.name; };
    void setName(bool ran=false);
    bool isUnlocked(assUnlocks unlock);
    String getNameFromUnlock(assUnlocks unlock);
    int getValueFromUnlock(assUnlocks unlock);
    int getUnlockedCount();
    assUnlocks getUnlockFromName(String name);
    bool addUnlock(assUnlocks unlock);
    void removeUnlock(assUnlocks unlock);
    int sumUnlockValues();
    bool addSwarmName(const String& name);
    int sumSwarmNames();
    void cleanSwarmNames();
    bool isValidName(const String& name);
    double getLevel(bool set=true);
    void setLevel();
    bool unlockThing(assUnlocks unlock, bool init=false);
    void talk(assMouthTalk talk);
    int countUp(int up = 1);
    bool bored() { return this->BORED; }
    void hello();
    String getFile(const char* path);
    String* getPatternInfo();
    String getCurrentPatternName();

    
private:
    assStates STATE;
    assStates STATE_S;

    bool BORED = false;
    unsigned long BORED_TIME = 0;
    unsigned long GET_BORED = 200321;

    double LEVEL = 0;
    int LEVEL_INIT = 0;

    bool SAVE = false;
    unsigned long AUTOSAVE = 300000;
    unsigned long SAVE_TIME = 0;

    char FRIEND[50];

    int PATTERN_PREVIOUS = 0;
    assPatternEyes PATTERN_EYE_CURRENT = assPatternEyes::NONE;
    assPatternEyes PATTERN_EYE_SELECT = assPatternEyes::NONE;
    assPatternEyes PATTERN_EYE_SWARM = assPatternEyes::NONE;
    int MAX_CAT = 9;
    int MAX_LINE[10] = {8,7,7,6,4,6,6,5,6,7};

    assWifi *wifi;
    assLoRa *lora;
    assData *data;
    assPixs *pixs;
    assButts *butts;

    assInfo info;
    std::vector<assUnlock> allUnlocks;
    std::vector<assPat> allPats;

};

#endif // ASSFSM_H
