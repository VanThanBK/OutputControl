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

#define BAUDRATE 921600
#define TEENSY_PORT Serial1
//using namespace std;

class GCodeReceiverClass
{
public:
	void Init();
	void Execute();
private:
	// New buffered reception with CRC16
	static const size_t RX_BUFFER_SIZE = 96;
	char rx_buf[RX_BUFFER_SIZE];
	size_t rx_len = 0;
	bool is_frame_complete = false;
	uint32_t last_rx_us = 0;
	void parseFrame(const char* payload, size_t len);
	void handleControlFrame(const char* payload, size_t len);
};

extern GCodeReceiverClass GCodeReceiver;

#endif

