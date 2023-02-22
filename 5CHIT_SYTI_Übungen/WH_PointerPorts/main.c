/*
 * WH_PointerPorts.c
 *
 * Created: 15.09.2022 10:42:15
 * Author : manue
 */ 

#include <avr/io.h>
#define F_CPU 16000000 //Taktfrequenz der CPU
#include "LedOut.h"


int main(void)
{	
	Init();
	// A ist ein Char und ist in binär 0010 0001
	char leds[] = {'A','B',0b10000000}; 

	while(1)
	{
		changeLED(leds,3);
	}  
}

