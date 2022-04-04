#include "PinOutControl.h"

void PinOutControlClass::Init()
{
    for (uint8_t i = 0; i < 8; i++)
    {
        pinMode(d_pin_array[i], OUTPUT);
        Digital_OFF(i);
    }
}

void PinOutControlClass::Digital_ON(uint8_t index)
{
    digitalWrite(d_pin_array[index], 1);
}

void PinOutControlClass::Digital_OFF(uint8_t index)
{
    digitalWrite(d_pin_array[index], 0);
}

void PinOutControlClass::Pwm_Write(uint8_t index, uint16_t pwmValue)
{
    if (d_pin_pwm_array[index] == 255)
        return;
    pwmWrite(d_pin_pwm_array[index], pwmValue);
}

void PinOutControlClass::Analog_Write(uint8_t index, uint8_t pwmValue)
{
    if (d_pin_pwm_array[index] == 255)
        return;
    analogWrite(d_pin_pwm_array[index], pwmValue);
}

void PinOutControlClass::Digital_Reset()
{
    for (uint8_t i = 0; i < 8; i++)
    {
        Digital_OFF(i);
    }
}

void PinOutControlClass::Pwm_Reset()
{
    for (uint8_t i = 0; i < 8; i++)
    {
        Pwm_Write(i, 0);
    }
}

PinOutControlClass PinOutControl;