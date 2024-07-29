#ifndef ASSDATA_H
#define ASSDATA_H

#include "FS.h"
#include "FFat.h"
#include "assG.h"

class assFSM;

class assData {
public:
    assData();
    void setController(assFSM* controller);
    void init();
    void update();
    assInfo loadInfo();
    void saveInfo(assInfo info);
    String read(const char* path);

private:
    assFSM *controller;
    fs::FS& fs;

    //std::vector<assUnlock> unlocks;

    bool write(const char* path, const char* message);
    void listDir(const char* dirname, uint8_t levels);
    void listAllFiles(const char* dirname, uint8_t levels);
    //void initUnlock();
};

#endif // ASSDATA_H