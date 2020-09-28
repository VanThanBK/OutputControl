#ifndef _GCODESEND_h
#define _GCODESEND_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define TEENSY_PORT Serial

#include "PinInControl.h"

class GCodeSendClass
{
private:
    /* data */
public:
   void Init();
   void Execute();
   uint32_t f_feedback_A[2];
   bool IsAutoFeedback_A[2];
   bool IsAutoFeedback_D[6];
private:
    bool Last_DInAray[6];

    uint32_t lastTime_A[2];
};

extern GCodeSendClass GCodeSend;
#endif