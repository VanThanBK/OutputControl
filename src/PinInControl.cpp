#include "PinInControl.h"

void PinInControlClass::Init()
{
    for (uint8_t i = 0; i < 10; i++)
    {
        pinMode(i_pin_array[i], INPUT);
    }

    pinMode(E_STOP1_PIN, INPUT);
    pinMode(E_STOP2_PIN, INPUT);

    for (uint8_t i = 0; i < 4; i++)
    {
        pinMode(a_pin_array[i], INPUT_ANALOG);
    }
}

bool PinInControlClass::Digital_Read(uint8_t index)
{
    return digitalRead(i_pin_array[index]);
}

uint16_t PinInControlClass::Analog_Read(uint8_t index)
{
    return analogRead(a_pin_array[index]);
}

PinInControlClass PinInControl;