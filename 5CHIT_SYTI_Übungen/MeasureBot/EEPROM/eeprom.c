/*
 * eeprom.c
 *
 * Created: 26.01.2023 10:47:01
 *  Author: manue
 */ 

#include <avr/io.h>
#include <avr/eeprom.h>
#include "checksum.h"
#include "eeprom.h"

EepromData eepromData;

void SafeTransmitIntervalToEEPROM()
{
	CreateCheckSum();
	eeprom_write_block(&eepromData,0,sizeof(eepromData));
}

void LoadTransmitIntervalFromEEPROM()
{
	eeprom_read_block(&eepromData,0,sizeof(eepromData));
}

void CreateCheckSum()
{
	eepromData.crc = crc_8(&eepromData,sizeof(eepromData)-1);
}

int VerifyCheckSum()
{
	if(crc_8(&eepromData,sizeof(eepromData)-1)==eepromData.crc)
	return 1;
	
	return 0;
}