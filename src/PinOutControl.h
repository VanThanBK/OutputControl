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
public:
    void Init();

    void Digital_ON(uint8_t index);
    void Digital_OFF(uint8_t index);

    void Pwm_Write(uint8_t index, uint16_t pwmValue);
    void Analog_Write(uint8_t index, uint8_t pwmValue);

    void Digital_Reset();
    void Pwm_Reset();
    
private:
    Servo Servo_1;
    Servo Servo_2;

    uint8_t d_pin_array[16] = {D_0_PIN, D_1_PIN, D_2_PIN, D_3_PIN, D_4_PIN, D_5_PIN, D_6_PIN, D_7_PIN, D_8_PIN, D_9_PIN, D_10_PIN, D_11_PIN, D_12_PIN, D_13_PIN, D_14_PIN, D_15_PIN};
    uint8_t d_pin_pwm_array[16] = {D_0_PWM_PIN, D_1_PWM_PIN, D_2_PWM_PIN, D_3_PWM_PIN, D_4_PWM_PIN, D_5_PWM_PIN, D_6_PWM_PIN, D_7_PWM_PIN, D_8_PWM_PIN, D_9_PWM_PIN, D_10_PWM_PIN, D_11_PWM_PIN, D_12_PWM_PIN, D_13_PWM_PIN, D_14_PWM_PIN, D_15_PWM_PIN};
};

extern PinOutControlClass PinOutControl;

#endif