#ifndef _ASSLORA_H_
#define _ASSLORA_H_

#include <LoRa.h>
#include "assG.h"

#define PASSWORD "SuperS3cretP@ssword"

struct Device {
    String name; 
    double powerlevel;
    unsigned long lastupdatebyme;
    int pattern;
    int patternState;
    int patternTime;
    int stamp;

    Device(String name = "null", 
           float powerlevel = 0.42,
           unsigned long lastupdatebyme = 0,
           int pattern = -1,
           int stamp = 0) {
        this->name = "null";
        this->powerlevel = powerlevel;
        this->pattern = pattern;
        this->lastupdatebyme = lastupdatebyme;
        this->patternState = 0;
        this->patternTime = 0;
        this->stamp = 0;
    }
};

class assFSM;

class assLoRa {
public:
    assLoRa();
    void setController(assFSM* controller);
    void init();
    void update();
    void sendData();
    void receiveData();
    void parseData(String message);
    String craftMessage();
    Device getLeader();
    void updateStuff();
    void updateState(assStates state);
    void updateDevice();
    bool verifyName(String str);
    bool verifyLevel(float level, String str);
    bool verifyStamp(int number, String name);
    int generateStamp(String name, int p1);
    int retrieveNewParam(long number);
    int replaceNewParam(int number, int newParam);
    int alphabetNumberSum(String name);
    String XOR(String input, String key);
    byte hexToByte(String hex);
    String xorDecrypt(String input, String key);

private:
    assFSM* controller;
    Device deviceList[3]; 
    Device thisDevice;

    String currentLeader = "me";
    String previousLeader = "me";
    int previousPattern = 0;
    int packetCount = 0;

    assStates STATE;

    int TRANSMIT = 6000;
    unsigned long LAST_TRANSMIT = 0;
    int TRANSMIT_SLOW = 9000;
    int TRANSMIT_MED = 6000;
    int TRANSMIT_FAST = 3000;
    int LAST_UPDATE = 6000;
    int DROP = 20000;

    unsigned long MULTIPLIER = 1000000;
};

#endif // _ASSLORA_H_
