// GCodeReceiver.h

#ifndef _GCODERECEIVER_h
#define _GCODERECEIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GCodeSend.h"
#include "PinOutControl.h"
#include "PinInControl.h"

#define BAUDRATE 115200
#define TEENSY_PORT Serial
//using namespace std;

class GCodeReceiverClass
{
public:
	void Init();
	void Execute();
private:
	String gcodeCommand;
	String receiveString;
	bool isStringComplete;
	char keyValue;
	int keyIndex;
	float Value;

	void executeCommand();
	void keyReset();
};

extern GCodeReceiverClass GCodeReceiver;

#endif

