//
//
//

#include "GCodeReceiver.h"

void GCodeReceiverClass::Init()
{
	TEENSY_PORT.begin(BAUDRATE);
	TEENSY_PORT.setTimeout(100);
	receiveString.reserve(100);

	isStringComplete = false;
	receiveString = "";
	keyReset();
}

void GCodeReceiverClass::Execute()
{
	while (TEENSY_PORT.available())
	{
		char inChar = (char)TEENSY_PORT.read();

		if (inChar == '\n')
		{
			isStringComplete = true;
			break;
		}

		if (inChar != '\r')
		{
			receiveString += inChar;
		}
	}

	if (!isStringComplete)
		return;

	uint8_t index_buffer = receiveString.indexOf(' ');

	if (index_buffer >= 0)
	{
		keyValue = receiveString[0];
		keyIndex = receiveString.substring(1, index_buffer).toInt();
		Value = receiveString.substring(index_buffer + 1).toFloat();
	}
	else
	{
		keyValue = receiveString[0];
		keyIndex = receiveString.substring(1).toInt();
	}

	executeCommand();
	keyReset();

	receiveString = "";
	isStringComplete = false;
}

void GCodeReceiverClass::executeCommand()
{
	switch (keyValue)
	{
	case 'T':
		if (Value == 1)
		{
			switch (keyIndex)
			{
			case 1:
				PinOutControl.Digital_Reset();
				break;
			case 2:
				PinOutControl.Pwm_Reset();
				break;
			default:
				break;
			}
		}
		break;
	case 'D':
		if (Value == 0)
		{
			PinOutControl.Digital_OFF(keyIndex);
		}
		else
		{
			PinOutControl.Digital_ON(keyIndex);
		}
		break;
	case 'P':
		if (Value >= 0)
		{
			uint8_t value = (uint8_t)Value;
			PinOutControl.Analog_Write(keyIndex, value);
		}
		break;
	case 'Q':
		if (Value >= 0)
		{
			uint16_t value = (uint16_t)Value;
			PinOutControl.Pwm_Write(keyIndex, value);
		}
		break;
	case 'I':
		bool value_I;
		value_I = PinInControl.Digital_Read(keyIndex);
		TEENSY_PORT.print("I");
		TEENSY_PORT.print(String(keyIndex) + " ");
		TEENSY_PORT.println(value_I);
		break;
	case 'J':
		GCodeSend.IsAutoFeedback_D[keyIndex] = Value;
		break;
	case 'A':
		uint16_t value_A;
		value_A = PinInControl.Analog_Read(keyIndex);
		TEENSY_PORT.print("A");
		TEENSY_PORT.print(String(keyIndex) + " ");
		TEENSY_PORT.println(value_A);
		break;
	case 'B':
		if (Value > 100)
		{
			GCodeSend.f_feedback_A[keyIndex] = Value;
			GCodeSend.IsAutoFeedback_A[keyIndex] = true;
		}
		else
		{
			GCodeSend.IsAutoFeedback_A[keyIndex] = false;
		}
		break;
	default:
		break;
	}
}

void GCodeReceiverClass::keyReset()
{
	keyValue = ' ';
	keyIndex = 0;
	Value = 0;
}

GCodeReceiverClass GCodeReceiver;