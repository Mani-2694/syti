/*
 * LedOut.h
 *
 * Created: 15.09.2022 11:19:56
 *  Author: manue
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000 //Taktfrequenz der CPU

void Init();
void changeLED(char *leds, int length);