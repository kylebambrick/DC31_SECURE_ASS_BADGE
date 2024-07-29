#ifndef ASSBUTTS_H
#define ASSBUTTS_H

#include <Arduino.h>
#include "assG.h"

class assFSM;

class assButts {
public:
  assButts();
  void setController(assFSM* controller);  
  void setupButtons();
  void handleButtons();

private:
  assFSM* controller;
  unsigned long DEBOUNCE_TIME = 50;
  unsigned long DEBOUNCE_A = 0;
  unsigned long DEBOUNCE_B = 0;
  unsigned long DEBOUNCE_S = 0;
};

#endif // ASSBUTTS_H
