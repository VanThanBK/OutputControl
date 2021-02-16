#include <Arduino.h>
#include "PinOutControl.h"
#include "PinInControl.h"
#include "GCodeReceiver.h"
#include "GCodeSend.h"

void setup() {
  disableDebugPorts();
  PinOutControl.Init();
  PinInControl.Init();
  GCodeReceiver.Init();
  //GCodeSend.Init();
  TEENSY_PORT.println("R0 0");
}

void loop() {
  GCodeReceiver.Execute();
  GCodeSend.Execute();
}