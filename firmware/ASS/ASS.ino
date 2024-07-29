#include "assG.h"
#include "assFSM.h"
#include "assWifi.h"
#include "assLoRa.h"
#include "assData.h"
#include "assPixs.h"
#include "assButts.h"

assWifi wifi; 
assLoRa lora;
assData data;
assPixs pixs;
assButts butts;

assFSM controller(nullptr, &lora, &data, &pixs, &butts);

void setup() {
  
  Serial.begin(115200);
  delay(1000);
  while (!Serial);
  Serial.setDebugOutput(true);
  delay(1000); 
  //Serial.end();

  debugln("SECURE Autonomous Surveillance Sentry");
  debugln("Initializing SECURE A.S.S. ASYNCRONOUS SECURITY SYSTEM...");
  
  randomSeed(analogRead(0));

  // Initialize
  wifi.setController(&controller);
  lora.setController(&controller);
  data.setController(&controller);
  butts.setController(&controller);
  butts.setupButtons();
  pixs.init();
  data.init();
  lora.init();
  controller.init();
  wifi.startWifi(controller.getName().c_str());

  //debugln("Initialized ASSFSM, wifi, swarm, butts, pixs, and data");
  //Serial.end();

}

void loop() {
  static unsigned long lastPrintTime = 0; // Save the last time you printed the info
  unsigned long now = millis(); // Current time

  controller.refresh();
  butts.handleButtons();
  lora.update();
  pixs.render();

  /*
  if (now - lastPrintTime >= 10000) {
    lastPrintTime = now; // Update the last print time

    Serial.print("Heap Size: ");
    Serial.println(ESP.getHeapSize());
    Serial.print("Free Heap: ");
    Serial.println(ESP.getFreeHeap());
    Serial.print("Min Free Heap: ");
    Serial.println(ESP.getMinFreeHeap());
  }*/
}