#include "GCodeSend.h"

void GCodeSendClass::Init()
{
    for (uint8_t i = 0; i < 8; i++)
    {
        Last_DInAray[i] = PinInControl.Digital_Read(i);
        TEENSY_PORT.print("I");
		TEENSY_PORT.print(String(i) + " ");
		TEENSY_PORT.println(Last_DInAray[i]);
        delayMicroseconds(100);

        IsAutoFeedback_D[i] = true;
    }

    for (uint8_t i = 0; i < 4; i++)
    {
        uint16_t a_Read;
        a_Read = PinInControl.Analog_Read(i);
        TEENSY_PORT.print("A");
		TEENSY_PORT.print(String(i) + " ");
		TEENSY_PORT.println(a_Read);
        delayMicroseconds(100);

        IsAutoFeedback_A[i] = true;
        lastTime_A[i] = micros();
        f_feedback_A[i] = 10000;
    }
}

void GCodeSendClass::Execute()
{
    for (uint8_t i = 0; i < 10; i++)
    {
        if (!IsAutoFeedback_D[i]) continue;

        if (PinInControl.Digital_Read(i) != Last_DInAray[i])
        {
            Last_DInAray[i] = PinInControl.Digital_Read(i);
            TEENSY_PORT.print("J");
		    TEENSY_PORT.print(String(i) + " ");
		    TEENSY_PORT.println(Last_DInAray[i]);
        }
    }

    for (uint8_t i = 0; i < 4; i++)
    {
        if (!IsAutoFeedback_A[i]) continue;

        if (micros() - lastTime_A[i] > f_feedback_A[i])
        {
            lastTime_A[i] = micros();
            uint16_t a_Read;
            a_Read = PinInControl.Analog_Read(i);
            TEENSY_PORT.print("B");
		    TEENSY_PORT.print(String(i) + " ");
		    TEENSY_PORT.println(a_Read);
        }
    }
}

GCodeSendClass GCodeSend;