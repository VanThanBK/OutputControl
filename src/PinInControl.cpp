#include "PinInControl.h"

void PinInControlClass::Init()
{
    for (uint8_t i = 0; i < 6; i++)
    {
        pinMode(i_pin_array[i], INPUT_PULLDOWN);
    }

    pinMode(E_STOP1_PIN, INPUT_PULLDOWN);
    pinMode(E_STOP2_PIN, INPUT_PULLDOWN);

    for (uint8_t i = 0; i < 2; i++)
    {
        pinMode(a_pin_array[i], INPUT_ANALOG);
    }
}

bool PinInControlClass::Digital_Read(uint8_t index)
{
    int __counter = 0;
    for (int i = 0; i < 10; i++)
    {
        if (digitalRead(i_pin_array[index]) == 1)
        {
            __counter++;
        }
        delayMicroseconds(1);
    }

    if (__counter >= 5)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint16_t PinInControlClass::Analog_Read(uint8_t index)
{
    return analogRead(a_pin_array[index]);
}

PinInControlClass PinInControl;