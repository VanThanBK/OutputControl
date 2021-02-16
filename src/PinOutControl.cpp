#include "PinOutControl.h"

void PinOutControlClass::Init()
{
    pinMode(RELAY_1_PIN, OUTPUT);
    pinMode(RELAY_2_PIN, OUTPUT);
    pinMode(RELAY_3_PIN, OUTPUT);
    pinMode(RELAY_4_PIN, OUTPUT);

    digitalWrite(RELAY_1_PIN, 0);
    digitalWrite(RELAY_2_PIN, 0);
    digitalWrite(RELAY_3_PIN, 0);
    digitalWrite(RELAY_4_PIN, 0);

    pinMode(DIGITAL_OUT_1_PIN, OUTPUT);
    pinMode(DIGITAL_OUT_2_PIN, OUTPUT);
    pinMode(DIGITAL_OUT_3_PIN, OUTPUT);
    pinMode(DIGITAL_OUT_4_PIN, OUTPUT);

    digitalWrite(DIGITAL_OUT_1_PIN, 0);
    digitalWrite(DIGITAL_OUT_2_PIN, 0);
    digitalWrite(DIGITAL_OUT_3_PIN, 0);
    digitalWrite(DIGITAL_OUT_4_PIN, 0);

    pinMode(PWM_OUT_1_PIN, PWM);
    pinMode(PWM_OUT_2_PIN, PWM);
    pwmWrite(PWM_OUT_1_PIN, 0);
    pwmWrite(PWM_OUT_2_PIN, 0);

    Servo_1.attach(SERVO_1_PIN);
    Servo_2.attach(SERVO_2_PIN);
    Servo_1.write(0);
    Servo_2.write(0);
}

void PinOutControlClass::RL_ON(uint8_t index)
{
    switch (index)
    {
    case 0:
        digitalWrite(RELAY_1_PIN, 1);
        break;
    case 1:
        digitalWrite(RELAY_2_PIN, 1);
        break;
    case 2:
        digitalWrite(RELAY_3_PIN, 1);
        break;
    case 3:
        digitalWrite(RELAY_4_PIN, 1);
        break;
    default:
        break;
    }
}

void PinOutControlClass::RL_OFF(uint8_t index)
{
    switch (index)
    {
    case 0:
        digitalWrite(RELAY_1_PIN, 0);
        break;
    case 1:
        digitalWrite(RELAY_2_PIN, 0);
        break;
    case 2:
        digitalWrite(RELAY_3_PIN, 0);
        break;
    case 3:
        digitalWrite(RELAY_4_PIN, 0);
        break;
    default:
        break;
    }
}

void PinOutControlClass::Digital_ON(uint8_t index)
{
    switch (index)
    {
    case 0:
        digitalWrite(DIGITAL_OUT_1_PIN, 1);
        break;
    case 1:
        digitalWrite(DIGITAL_OUT_2_PIN, 1);
        break;
    case 2:
        digitalWrite(DIGITAL_OUT_3_PIN, 1);
        break;
    case 3:
        digitalWrite(DIGITAL_OUT_4_PIN, 1);
        break;
    default:
        break;
    }
}

void PinOutControlClass::Digital_OFF(uint8_t index)
{
    switch (index)
    {
    case 0:
        digitalWrite(DIGITAL_OUT_1_PIN, 0);
        break;
    case 1:
        digitalWrite(DIGITAL_OUT_2_PIN, 0);
        break;
    case 2:
        digitalWrite(DIGITAL_OUT_3_PIN, 0);
        break;
    case 3:
        digitalWrite(DIGITAL_OUT_4_PIN, 0);
        break;
    default:
        break;
    }
}

void PinOutControlClass::Pwm_Write(uint8_t index, uint16_t pwmValue)
{
    switch (index)
    {
    case 0:
        pwmWrite(PWM_OUT_1_PIN, pwmValue);
        break;
    case 1:
        pwmWrite(PWM_OUT_2_PIN, pwmValue);
        break;
    default:
        break;
    }
}

void PinOutControlClass::Analog_Write(uint8_t index, uint8_t pwmValue)
{
    switch (index)
    {
    case 0:
        analogWrite(PWM_OUT_1_PIN, pwmValue);
        break;
    case 1:
        analogWrite(PWM_OUT_2_PIN, pwmValue);
        break;
    default:
        break;
    }
}

void PinOutControlClass::Servo_Write(uint8_t index, uint8_t servoValue)
{
    switch (index)
    {
    case 0:
        Servo_1.write(servoValue);
        break;
    case 1:
        Servo_2.write(servoValue);
        break;
    default:
        break;
    }
}

void PinOutControlClass::RL_Reset()
{
    digitalWrite(RELAY_1_PIN, 0);
    digitalWrite(RELAY_2_PIN, 0);
    digitalWrite(RELAY_3_PIN, 0);
    digitalWrite(RELAY_4_PIN, 0);
}

void PinOutControlClass::Digital_Reset()
{
    digitalWrite(DIGITAL_OUT_1_PIN, 0);
    digitalWrite(DIGITAL_OUT_2_PIN, 0);
    digitalWrite(DIGITAL_OUT_3_PIN, 0);
    digitalWrite(DIGITAL_OUT_4_PIN, 0);
}

void PinOutControlClass::Pwm_Reset()
{
    pwmWrite(PWM_OUT_1_PIN, 0);
    pwmWrite(PWM_OUT_2_PIN, 0);
}

PinOutControlClass PinOutControl;