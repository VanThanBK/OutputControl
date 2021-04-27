#ifndef _GCODESEND_h
#define _GCODESEND_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define TEENSY_PORT Serial1

#include "PinInControl.h"

class GCodeSendClass
{

public:
   void Init();
   void Execute();
   uint32_t f_feedback_A[4];
   bool IsAutoFeedback_A[4];
   bool IsAutoFeedback_D[10];
private:
    bool Last_DInAray[10];

    uint32_t lastTime_A[4];
};

extern GCodeSendClass GCodeSend;
#endif