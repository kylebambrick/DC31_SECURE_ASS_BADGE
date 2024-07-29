#include "assFSM.h"
#include "assButts.h"

assButts::assButts() : controller(nullptr) {}

void assButts::setController(assFSM* controller) {
  this->controller = controller;
}

void assButts::setupButtons() {
  pinMode(BUTTON_PIN_A, INPUT_PULLUP);
  pinMode(BUTTON_PIN_B, INPUT_PULLUP);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  if (digitalRead(SWITCH_PIN) == HIGH) {
      controller->setState(assStateName::STATE_S, assStates::WIFI);
  } else {
      controller->setState(assStateName::STATE_S, assStates::LORA);
  }

}

void assButts::handleButtons() {
  static bool lastStateA = HIGH;
  static bool lastStateB = HIGH;
  static bool lastStateS = HIGH;
  
  bool currentStateA = digitalRead(BUTTON_PIN_A);
  bool currentStateB = digitalRead(BUTTON_PIN_B);
  bool currentStateS = digitalRead(SWITCH_PIN);

  // Button A
  if (currentStateA == LOW && lastStateA == HIGH && (millis() - DEBOUNCE_A > DEBOUNCE_TIME)) {
    DEBOUNCE_A = millis();
    controller->setState(assStateName::STATE_A, assStates::PUSHED);
    controller->hello();
    //debugln("Button A pressed");
  }
  lastStateA = currentStateA;

  // Button B
  if (currentStateB == LOW && lastStateB == HIGH && (millis() - DEBOUNCE_B > DEBOUNCE_TIME)) {
    DEBOUNCE_B = millis();
    controller->setState(assStateName::STATE_B, assStates::PUSHED);
    controller->hello();
    //debugln("Button B pressed");
  }
  lastStateB = currentStateB;

  // Switch
  if (currentStateS != lastStateS && (millis() - DEBOUNCE_S > DEBOUNCE_TIME)) {
    DEBOUNCE_S = millis();
    if (currentStateS == HIGH) {
      controller->setState(assStateName::STATE_S, assStates::WIFI);
      controller->hello();
      //debugln("Switch state: Wifi");
    } else {
      controller->setState(assStateName::STATE_S, assStates::LORA);
      controller->hello();
      //debugln("Switch state: LoRa");
    }
  }
  lastStateS = currentStateS;
}
