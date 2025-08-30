#ifndef _GCODESEND_h
#define _GCODESEND_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define TEENSY_PORT Serial1

#include "PinInControl.h"
#include "CRC16.h"

class GCodeSendClass
{

public:
   void Init();
   void Execute();
   uint32_t f_feedback_A[2];
   bool IsAutoFeedback_A[2];
   bool IsAutoFeedback_D[6];
private:
    bool Last_DInAray[6];

    uint32_t lastTime_A[2];
public:
    // retransmission buffer for last telemetry frame
    char last_tx_payload[48];
    int last_tx_len = 0;
    uint8_t last_tx_retry = 0;
};

extern GCodeSendClass GCodeSend;
#endif