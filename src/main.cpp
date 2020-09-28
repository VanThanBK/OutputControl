#include <Arduino.h>
#include "PinOutControl.h"
#include "PinInControl.h"
#include "GCodeReceiver.h"
#include "GCodeSend.h"

void setup() {
  PinOutControl.Init();
  PinInControl.Init();
  GCodeReceiver.Init();
  GCodeSend.Init();
}

void loop() {
  GCodeReceiver.Execute();
  GCodeSend.Execute();
}