#include "GCodeSend.h"

void GCodeSendClass::Init()
{
    for (uint8_t i = 0; i < 6; i++) {
        Last_DInAray[i] = PinInControl.Digital_Read(i);
        char pl[24]; int n = snprintf(pl,sizeof(pl),"I%u %u", (unsigned)i, (unsigned)(Last_DInAray[i]?1:0));
        uint16_t crc=crc16_ccitt_false((const uint8_t*)pl,n,0xFFFF); TEENSY_PORT.write((const uint8_t*)pl,n); char tail[8]; snprintf(tail,sizeof(tail),"*%04X\n",crc); TEENSY_PORT.print(tail);
        memcpy(last_tx_payload,pl,n); last_tx_len=n; last_tx_retry=0;
        delayMicroseconds(100);
        IsAutoFeedback_D[i] = true;
    }

    for (uint8_t i = 0; i < 2; i++) {
        uint16_t a_Read = PinInControl.Analog_Read(i);
        char pl[24]; int n = snprintf(pl,sizeof(pl),"A%u %u", (unsigned)i, (unsigned)a_Read);
        uint16_t crc=crc16_ccitt_false((const uint8_t*)pl,n,0xFFFF); TEENSY_PORT.write((const uint8_t*)pl,n); char tail[8]; snprintf(tail,sizeof(tail),"*%04X\n",crc); TEENSY_PORT.print(tail);
        memcpy(last_tx_payload,pl,n); last_tx_len=n; last_tx_retry=0;
        delayMicroseconds(100);
        IsAutoFeedback_A[i] = true; lastTime_A[i] = micros(); f_feedback_A[i] = 10000;
    }
}

void GCodeSendClass::Execute()
{
    for (uint8_t i = 0; i < 6; i++) {
        if (!IsAutoFeedback_D[i]) continue;
        bool cur = PinInControl.Digital_Read(i);
        if (cur != Last_DInAray[i]) {
            Last_DInAray[i] = cur;
            char pl[24]; int n = snprintf(pl,sizeof(pl),"J%u %u", (unsigned)i, (unsigned)(cur?1:0));
            uint16_t crc=crc16_ccitt_false((const uint8_t*)pl,n,0xFFFF); TEENSY_PORT.write((const uint8_t*)pl,n); char tail[8]; snprintf(tail,sizeof(tail),"*%04X\n",crc); TEENSY_PORT.print(tail);
            memcpy(last_tx_payload,pl,n); last_tx_len=n; last_tx_retry=0;
        }
    }

    for (uint8_t i = 0; i < 2; i++) {
        if (!IsAutoFeedback_A[i]) continue;
        if (micros() - lastTime_A[i] > f_feedback_A[i]) {
            lastTime_A[i] = micros();
            uint16_t a_Read = PinInControl.Analog_Read(i);
            char pl[24]; int n = snprintf(pl,sizeof(pl),"B%u %u", (unsigned)i, (unsigned)a_Read);
            uint16_t crc=crc16_ccitt_false((const uint8_t*)pl,n,0xFFFF); TEENSY_PORT.write((const uint8_t*)pl,n); char tail[8]; snprintf(tail,sizeof(tail),"*%04X\n",crc); TEENSY_PORT.print(tail);
            memcpy(last_tx_payload,pl,n); last_tx_len=n; last_tx_retry=0;
        }
    }
    //delay(1000);
    //TEENSY_PORT.println("I1 1");
}

GCodeSendClass GCodeSend;