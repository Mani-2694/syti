/*
 * EEPROM.c
 *
 * Created: 06.10.2022 10:51:43
 * Author : manue
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include <stdio.h>
#include "lcd.h"
#include "checksum.h"

typedef struct _EepromData  {
	int size;
	int Zufallszahl;
	int Dummy1;
	int Dummy2;
	uint8_t crc;
} EepromData;

static volatile EepromData eepromData;
void SafeValueToEEPROM();
void LoadValueFromEEPROM();
void LoadEEPROMValueToDisplay();
void CreateCheckSum();
int VerifyCheckSum();
int GenerateRandomNumber();
void DisplayEEPROMSave();

int main(void)
{
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	
	DDRD |= 0x40;
	
	PCMSK1|=(1<<PCINT11);   //erlaubt PCINT11 einen Interrupt auszulösen
	PCMSK1 |=(1<<PCINT12);  //erlaubt PCINT12 einen Interrupt auszulösen
	PCMSK1 |=(1<<PCINT13); //erlaubt PCINT13 einen Interrupt auszulösen
	PCICR |=(1<<PCIE1); //festgelegt, wann Interrupt aufgerufen wird PCIE1 = any change on any PCINT14..8
		
	sei(); //aktiviert Interrupts
	
	LoadEEPROMValueToDisplay();
	
    while (1)
    {
		
    }
}

ISR(PCINT1_vect) //PIN Change Interrupt Routine, 1 legt Priorität fest
{
	
	if((PINC & (1 << PINC3)) == (1<<PINC3))
	{
		LoadEEPROMValueToDisplay();
	}
	else if((PINC & (1 << PINC4)) == (1<<PINC4))
	{	
		lcd_clrscr();
		
		LoadValueFromEEPROM();
		eepromData.Dummy1++; 
		eepromData.Dummy2++;
		SafeValueToEEPROM();
		
		lcd_puts("Dummy changed!");
		char ausg2[16];
		sprintf(ausg2, "%d", eepromData.Dummy1);
		lcd_gotoxy(0,1);
		lcd_puts("CRC: ");
		lcd_puts(ausg2);
		
	}
	else if((PINC & (1 << PINC5)) == (1<<PINC5))
	{	
		lcd_clrscr();
		
		//Random Zahl generien, im struct speichern und ausgeben
		eepromData.Zufallszahl = GenerateRandomNumber();
		char ausg[16];
		sprintf(ausg, "%d", eepromData.Zufallszahl);
		lcd_puts("Random: ");
		lcd_puts(ausg);
		
		//struct im EEPROM speichern
		CreateCheckSum();
		SafeValueToEEPROM();
		
		char ausg2[16];
		sprintf(ausg2, "%d", eepromData.crc);
		lcd_gotoxy(0,1);
		lcd_puts("CRC: ");
		lcd_puts(ausg2);
	}
	_delay_ms(200);
}

void LoadEEPROMValueToDisplay()
{
	lcd_clrscr();
	
	LoadValueFromEEPROM();
	
	if(!VerifyCheckSum())
	{
		lcd_puts("Checksum invalid!!");
	}
	else
	{
		char ausg[16];
		sprintf(ausg, "%d", eepromData.Zufallszahl);
		lcd_puts("EEPROM: ");
		lcd_puts(ausg);
	}
}

void SafeValueToEEPROM()
{
	//eeprom_write_byte(0,eepromData.Zufallszahl); //first attempt to save only the number
	eeprom_write_block(&eepromData,0,sizeof(eepromData));
	
	DisplayEEPROMSave();
}

void DisplayEEPROMSave()
{
	PORTD |= (1<<PORTD6);
	_delay_ms(1000);
	PORTD &= ~(1<<PORTD6);
}

void LoadValueFromEEPROM()
{
	//return eeprom_read_byte(0); //first attempt to read only the number
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

int GenerateRandomNumber()
{
	return rand() % 100;
}