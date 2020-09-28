#ifndef _PINOUTCONTROL_h
#define _PINOUTCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "pin.h"
#include <Servo.h>

class PinOutControlClass
{
private:
    /* data */
public:
    void Init();

    void RL_ON(uint8_t index);
    void RL_OFF(uint8_t index);

    void Digital_ON(uint8_t index);
    void Digital_OFF(uint8_t index);

    void Pwm_Write(uint8_t index, uint16_t pwmValue);
    void Analog_Write(uint8_t index, uint8_t pwmValue);

    void Servo_Write(uint8_t index, uint8_t servoValue);

    void RL_Reset();
    void Digital_Reset();
    void Pwm_Reset();
    void Servo_Reset();
private:
    Servo Servo_1;
    Servo Servo_2;
};

extern PinOutControlClass PinOutControl;

#endif