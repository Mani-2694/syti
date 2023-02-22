/*
 * eeprom.h
 *
 * Created: 26.01.2023 10:48:18
 *  Author: manue
 */ 

typedef struct _EepromData  {
	int majorVersion;
	int minorVersion;
	int headerLength;
	int transmitInterval;
	uint8_t crc;
} EepromData;

void SafeTransmitIntervalToEEPROM();

void LoadTransmitIntervalFromEEPROM();

void CreateCheckSum();

int VerifyCheckSum();
