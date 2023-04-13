/*
 * adc.c
 *
 * Created: 03.11.2022 11:24:37
 *  Author: manue
 */ 

#include <avr/io.h>

void init_adc()
{
	ADMUX |= (1<<REFS0) | (1<<MUX0) |(1<<MUX2);
	ADCSRA |= (1<<ADEN) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) |(1<<ADPS2);
}

void start_adc()
{
	ADCSRA |= (1<<ADSC); //Wandlung starten
}

float read_adc()
{
	 return ADCW;
}