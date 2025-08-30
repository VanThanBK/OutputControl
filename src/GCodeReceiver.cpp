//
//
//

#include "GCodeReceiver.h"
#include "CRC16.h"

void GCodeReceiverClass::Init()
{
	TEENSY_PORT.begin(BAUDRATE);
	rx_len = 0;
	is_frame_complete = false;
	last_rx_us = micros();
}

void GCodeReceiverClass::Execute()
{
	const uint32_t TIMEOUT_US = 20000;
	if (rx_len && (uint32_t)(micros() - last_rx_us) > TIMEOUT_US)
	{
		// timeout -> send NAK
		const char *pl = "NAK";
		uint16_t crc = crc16_ccitt_false((const uint8_t *)pl, 3, 0xFFFF);
		TEENSY_PORT.print(pl);
		char tail[8];
		snprintf(tail, sizeof(tail), "*%04X\n", crc);
		TEENSY_PORT.print(tail);
		rx_len = 0;
		is_frame_complete = false;
	}

	while (TEENSY_PORT.available())
	{
		char c = (char)TEENSY_PORT.read();
		last_rx_us = micros();
		if (c == '\r')
			continue;
		if (c == '\n')
		{
			is_frame_complete = true;
			break;
		}
		if (rx_len < RX_BUFFER_SIZE - 1)
		{
			rx_buf[rx_len++] = c;
		}
		else
		{ // overflow -> NAK
			const char *pl = "NAK";
			uint16_t crc = crc16_ccitt_false((const uint8_t *)pl, 3, 0xFFFF);
			TEENSY_PORT.print(pl);
			char tail[8];
			snprintf(tail, sizeof(tail), "*%04X\n", crc);
			TEENSY_PORT.print(tail);
			rx_len = 0;
			is_frame_complete = false;
			return;
		}
	}
	if (!is_frame_complete)
		return;
	rx_buf[rx_len] = '\0';
	// find '*'
	char *star = nullptr;
	for (size_t i = 0; i < rx_len; i++)
	{
		if (rx_buf[i] == '*')
		{
			star = &rx_buf[i];
			break;
		}
	}
	if (!star || (rx_len - (star - rx_buf)) < 5)
	{
		const char *pl = "NAK";
		uint16_t crc = crc16_ccitt_false((const uint8_t *)pl, 3, 0xFFFF);
		TEENSY_PORT.print(pl);
		char tail[8];
		snprintf(tail, sizeof(tail), "*%04X\n", crc);
		TEENSY_PORT.print(tail);
		rx_len = 0;
		is_frame_complete = false;
		return;
	}
	// parse CRC
	uint16_t crc_rx = 0;
	for (int i = 1; i <= 4; i++)
	{
		char ch = star[i];
		if (!isxdigit(ch))
		{
			const char *pl = "NAK";
			uint16_t crc = crc16_ccitt_false((const uint8_t *)pl, 3, 0xFFFF);
			TEENSY_PORT.print(pl);
			char tail[8];
			snprintf(tail, sizeof(tail), "*%04X\n", crc);
			TEENSY_PORT.print(tail);
			rx_len = 0;
			is_frame_complete = false;
			return;
		}
		crc_rx = (uint16_t)((crc_rx << 4) | (uint16_t)((ch <= '9') ? ch - '0' : ((ch & 0x5F) - 'A' + 10)));
	}
	size_t payload_len = (size_t)(star - rx_buf);
	uint16_t crc_calc = crc16_ccitt_false((const uint8_t *)rx_buf, payload_len, 0xFFFF);
	if (crc_calc != crc_rx)
	{
		const char *pl = "ERR";
		uint16_t crc = crc16_ccitt_false((const uint8_t *)pl, 3, 0xFFFF);
		TEENSY_PORT.print(pl);
		char tail[8];
		snprintf(tail, sizeof(tail), "*%04X\n", crc);
		TEENSY_PORT.print(tail);
		rx_len = 0;
		is_frame_complete = false;
		return;
	}
	// control frames
	if (payload_len == 3 && (strncmp(rx_buf, "ERR", 3) == 0 || strncmp(rx_buf, "NAK", 3) == 0))
	{
		handleControlFrame(rx_buf, payload_len);
		rx_len = 0;
		is_frame_complete = false;
		return;
	}
	parseFrame(rx_buf, payload_len);
	rx_len = 0;
	is_frame_complete = false;
}

void GCodeReceiverClass::parseFrame(const char *payload, size_t len)
{
	if (len == 0)
		return;
	char type = payload[0];
	size_t p = 1;
	uint16_t index = 0;
	while (p < len && payload[p] >= '0' && payload[p] <= '9')
	{
		index = (uint16_t)(index * 10 + (payload[p] - '0'));
		++p;
	}
	while (p < len && payload[p] == ' ')
		++p;
	bool neg = false;
	if (p < len && (payload[p] == '-' || payload[p] == '+'))
	{
		neg = (payload[p] == '-');
		++p;
	}
	uint32_t ip = 0;
	while (p < len && payload[p] >= '0' && payload[p] <= '9')
	{
		ip = ip * 10 + (payload[p] - '0');
		++p;
	}
	float val = (float)ip;
	if (p < len && payload[p] == '.')
	{
		++p;
		uint32_t frac = 0, div = 1;
		while (p < len && payload[p] >= '0' && payload[p] <= '9')
		{
			frac = frac * 10 + (payload[p] - '0');
			div *= 10;
			++p;
		}
		val += (float)frac / (float)div;
	}
	if (neg)
	{
		val = -val;
	}

	switch (type)
	{
	case 'T':
		if (val == 1)
		{
			if (index == 1)
				PinOutControl.Digital_Reset();
			else if (index == 2)
				PinOutControl.Pwm_Reset();
		}
		break;
	case 'D':
		if (val == 0)
			PinOutControl.Digital_OFF(index);
		else
			PinOutControl.Digital_ON(index);
		break;
	case 'P':
		if (val >= 0)
			PinOutControl.Analog_Write(index, (uint8_t)val);
		break;
	case 'Q':
		if (val >= 0)
			PinOutControl.Pwm_Write(index, (uint16_t)val);
		break;
	case 'I':
	{ // request digital read
		bool v = PinInControl.Digital_Read(index);
		char pl[24];
		int n = snprintf(pl, sizeof(pl), "I%u %u", (unsigned)index, (unsigned)(v ? 1 : 0));
		uint16_t crc = crc16_ccitt_false((const uint8_t *)pl, n, 0xFFFF);
		TEENSY_PORT.write((const uint8_t *)pl, n);
		char tail[8];
		snprintf(tail, sizeof(tail), "*%04X\n", crc);
		TEENSY_PORT.print(tail);
		memcpy(GCodeSend.last_tx_payload, pl, n);
		GCodeSend.last_tx_len = n;
		GCodeSend.last_tx_retry = 0;
	}
	break;
	case 'J': // set auto digital feedback enable
		GCodeSend.IsAutoFeedback_D[index] = (val != 0);
		break;
	case 'A':
	{ // request analog read
		uint16_t v = PinInControl.Analog_Read(index);
		char pl[24];
		int n = snprintf(pl, sizeof(pl), "A%u %u", (unsigned)index, (unsigned)v);
		uint16_t crc = crc16_ccitt_false((const uint8_t *)pl, n, 0xFFFF);
		TEENSY_PORT.write((const uint8_t *)pl, n);
		char tail[8];
		snprintf(tail, sizeof(tail), "*%04X\n", crc);
		TEENSY_PORT.print(tail);
		memcpy(GCodeSend.last_tx_payload, pl, n);
		GCodeSend.last_tx_len = n;
		GCodeSend.last_tx_retry = 0;
	}
	break;
	case 'B': // set auto analog feedback period (>100 enables)
		if (val > 100)
		{
			GCodeSend.f_feedback_A[index] = (uint32_t)val;
			GCodeSend.IsAutoFeedback_A[index] = true;
		}
		else
		{
			GCodeSend.IsAutoFeedback_A[index] = false;
		}
		break;
	default:
		break;
	}
}

void GCodeReceiverClass::handleControlFrame(const char *payload, size_t len)
{
	(void)len;
	if (strncmp(payload, "ERR", 3) == 0 || strncmp(payload, "NAK", 3) == 0)
	{
		// Ask GCodeSend to resend last frame
		if (GCodeSend.last_tx_len > 0 && GCodeSend.last_tx_retry < 3)
		{
			uint16_t crc = crc16_ccitt_false((const uint8_t *)GCodeSend.last_tx_payload, (size_t)GCodeSend.last_tx_len, 0xFFFF);
			TEENSY_PORT.write((const uint8_t *)GCodeSend.last_tx_payload, GCodeSend.last_tx_len);
			char tail[8];
			snprintf(tail, sizeof(tail), "*%04X\n", crc);
			TEENSY_PORT.print(tail);
			GCodeSend.last_tx_retry++;
		}
	}
}

GCodeReceiverClass GCodeReceiver;