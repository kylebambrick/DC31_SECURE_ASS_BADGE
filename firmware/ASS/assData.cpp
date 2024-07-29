#include "assFSM.h"
#include "assData.h"
#include "ArduinoJson.h"

assData::assData()
: controller(nullptr), fs(FFat) { }

void assData::setController(assFSM* controller) {
  this->controller = controller;
}


void assData::update() {

}

void assData::init() { 
  if(!FFat.begin()){
    debugln(".");
    delay(500);
  }
}

assInfo assData::loadInfo() {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, read("/info"));

    assInfo info {
        doc["NAME"].as<String>() != nullptr ? doc["NAME"].as<String>() : "NULL",
        doc["PATTERN"] | 0,
        doc["COUNT"] | 0
    };

    for(JsonVariant v : doc["UNLOCKS"].as<JsonArray>()) info.unlocks.push_back(v.as<String>());
    for(JsonVariant v : doc["SWARM"].as<JsonArray>()) info.swarm.push_back(v.as<String>());

    return info;
}


void assData::saveInfo(assInfo info) {
    DynamicJsonDocument doc(1024);
    doc["NAME"] = info.name;
    doc["PATTERN"] = info.pattern;  
    doc["COUNT"] = info.count;

    for (const String &unlockName : info.unlocks) doc["UNLOCKS"].add(unlockName);
    for (const String &swarmName : info.swarm) doc["SWARM"].add(swarmName);

    String output;
    serializeJson(doc, output);
    write("/info", output.c_str());
}


String assData::read(const char* path) {
    File file = fs.open(path);
    if(!file || file.isDirectory()) return String();
  
    String result;
    const size_t bufSize = 1024;
    char buf[bufSize];
  
    while(file.available()) {
        size_t len = file.readBytes(buf, bufSize);
        result += String(buf).substring(0, len);
    }
    file.close();
    return result;
}

bool assData::write(const char* path, const char* message) {
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        return false;
    }
    if(file.print(message)){
        debug(" ");
    } else {
        return false;
    }
    file.close();
    return true;
}


void assData::listDir(const char* dirname, uint8_t levels) {
    File root = fs.open(dirname);
    if(!root){
        debugln("- failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        debugln(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            debug("  DIR : ");
            debugln(file.name());
            if(levels){
                listDir(file.path(), levels -1);
            }
        } else {
            debug("  FILE: ");
            debug(file.name());
            debug("\tSIZE: ");
            debugln(file.size());
        }
        file = root.openNextFile();
    }
}

void assData::listAllFiles(const char* dirname = "/", uint8_t levels = 0) {
    listDir(dirname, levels);
}
