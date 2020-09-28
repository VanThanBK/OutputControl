#include "PinInControl.h"

void PinInControlClass::Init()
{
    pinMode(DIGITAL_IN_1_PIN, INPUT);
    pinMode(DIGITAL_IN_2_PIN, INPUT);
    pinMode(DIGITAL_IN_3_PIN, INPUT);
    pinMode(DIGITAL_IN_4_PIN, INPUT);
    pinMode(DIGITAL_IN_5_PIN, INPUT);
    pinMode(DIGITAL_IN_6_PIN, INPUT);

    pinMode(ANALOG_IN_1_PIN, INPUT_ANALOG);
    pinMode(ANALOG_IN_2_PIN, INPUT_ANALOG);
}

bool PinInControlClass::Digital_Read(uint8_t index)
{
    switch (index)
    {
    case 0:
        return digitalRead(DIGITAL_IN_1_PIN);
        break;
    case 1:
        return digitalRead(DIGITAL_IN_2_PIN);
        break;
    case 2:
        return digitalRead(DIGITAL_IN_3_PIN);
        break;
    case 3:
        return digitalRead(DIGITAL_IN_4_PIN);
        break;
    case 4:
        return digitalRead(DIGITAL_IN_5_PIN);
        break;
    case 5:
        return digitalRead(DIGITAL_IN_6_PIN);
        break;
    default:
        return false;
        break;
    }
}

uint16_t PinInControlClass::Analog_Read(uint8_t index)
{
    switch (index)
    {
    case 0:
        return analogRead(ANALOG_IN_1_PIN);
        break;
    case 1:
        return analogRead(ANALOG_IN_2_PIN);
        break;
    default:
        return 0;
        break;
    }
}

PinInControlClass PinInControl;