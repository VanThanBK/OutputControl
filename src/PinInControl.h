#ifndef _PININCONTROL_h
#define _PININCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "pin.h"
#include "elapsedMillis.h"

class PinInControlClass
{
public:
    void Init();
    bool Digital_Read(uint8_t index);
    uint16_t Analog_Read(uint8_t index);

private:
    elapsedMicros last_time_estop;
    uint8_t i_pin_array[6] = {I_0_PIN, I_1_PIN, I_2_PIN, I_3_PIN, E_STOP1_PIN, E_STOP2_PIN};
    uint8_t a_pin_array[2] = {A_0_PIN, A_1_PIN};
};

extern PinInControlClass PinInControl;
#endif