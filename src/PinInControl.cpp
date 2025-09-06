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
        delayMicroseconds(3); // widened to better space samples
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
    // Read multiple times in one call to smooth noise and return a fresh value.
    const uint8_t SAMPLES = 10;            // how many readings per call

    uint32_t sum = 0;
    for (uint8_t i = 0; i < SAMPLES; ++i) {
        sum += (uint16_t)analogRead(a_pin_array[index]);
        delayMicroseconds(3); // short spacing between conversions
    }
    uint16_t avg = (uint16_t)(sum / SAMPLES);
    return avg;
}

PinInControlClass PinInControl;