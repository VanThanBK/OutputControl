#ifndef _PININCONTROL_h
#define _PININCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "pin.h"

class PinInControlClass
{
private:
    /* data */
public:
    void Init();
    bool Digital_Read(uint8_t index);
    uint16_t Analog_Read(uint8_t index);

private:

};

extern PinInControlClass PinInControl;
#endif