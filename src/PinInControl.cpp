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
    // Collect a small moving window of samples to smooth noise.
    const uint8_t WINDOW = 8; // number of samples to average
    const uint16_t STABLE_THRESHOLD = 6; // minimal change to accept new stable value
    uint16_t raw = (uint16_t)analogRead(a_pin_array[index]);
    analog_accum[index] += raw;
    analog_sample_count[index]++;
    if (analog_sample_count[index] >= WINDOW) {
        uint16_t avg = (uint16_t)(analog_accum[index] / WINDOW);
        // Debounce: only update last_stable if difference exceeds threshold
        uint16_t prev = analog_last_stable[index];
        uint16_t diff = (avg > prev) ? (avg - prev) : (prev - avg);
        if (diff >= STABLE_THRESHOLD) {
            analog_last_stable[index] = avg;
        }
        analog_accum[index] = 0;
        analog_sample_count[index] = 0;
    }
    return analog_last_stable[index];
}

PinInControlClass PinInControl;