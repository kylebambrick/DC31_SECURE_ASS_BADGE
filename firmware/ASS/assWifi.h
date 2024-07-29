#ifndef ASSWIFI_H
#define ASSWIFI_H

#include "assG.h"
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>

class assFSM;

class assWifi {
public:
  assWifi();
  void setController(assFSM* controller);
  void startWifi(const String& ssid);
  void stopWifi();
  bool getApRunningStatus() const;
  void saySomething(const String& param = "/");
  bool containsXSS(String input);
  int isBadSQL(String input);
  int isBadANSI(String input);
  
private:
  char* _ssid;
  char* _password;
  bool _isApRunning;
  AsyncWebServer _server;

  assFSM* controller;

  String BEST_FRIEND = "NONE";

  void handleRoot(AsyncWebServerRequest *request);
  void handleRobots(AsyncWebServerRequest *request);
  void handleIndex(AsyncWebServerRequest *request);
  void handleStyle(AsyncWebServerRequest *request);
  void handleHomeStyle(AsyncWebServerRequest *request);
  void handleHomeScript(AsyncWebServerRequest *request);
  void handleReadMe(AsyncWebServerRequest *request);
  void handleUnlock(AsyncWebServerRequest *request);
  void handlePattern(AsyncWebServerRequest *request);
  void handleFlag(AsyncWebServerRequest *request);
  void handleBFF(AsyncWebServerRequest *request);
  void handleSubmit(AsyncWebServerRequest *request);
  void handleSubmitPost(AsyncWebServerRequest *request);
  void handleLoginGET(AsyncWebServerRequest *request);
  void handleLoginPOST(AsyncWebServerRequest *request);
  void handleADMIN(AsyncWebServerRequest *request);
  void handleSearchPost(AsyncWebServerRequest *request);

  String generateHome();
  String generateInfo();
  String generatePatterns();
};

#endif // ASSWIFI_H
