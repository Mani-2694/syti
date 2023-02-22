/*
 * LedOut.c
 *
 * Created: 15.09.2022 11:00:01
 *  Author: manue
 */ 

#include "LedOut.h"

void Init()
{
	DDRD = 0xFF;
	DDRB = 0xFF;
}

void changeLED(char *leds, int length)
{	
	for(int i = 0; i<length;i++)
	{
		PORTD = (leds[i]<<2);
		PORTB = (leds[i]>>6);
		_delay_ms(10000);
	}
}