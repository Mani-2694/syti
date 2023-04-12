/*
 * TestUebung2.c
 *
 * Created: 12.04.2023 10:12:03
 * Author : manue
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <avr/interrupt.h>

int main(void)
{
	
	PCICR |= (1<<PCIE2);
	PCMSK2 |= (1<<PCINT19);
	
	PORTD |= (1<<PORTD3);
	
	sei();
	
	ADCSRA |= (1<<ADEN) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	ADMUX |= (1<REFS0) | (1<<MUX2) | (1<<MUX0);
	
	ADCSRA |= (1<<ADSC);
	
	TCCR1B |= (1<<WGM12) | (1<<CS12);
	TIMSK1 |= (1<<OCIE1A);
	TIMSK1 |= (1<<TOIE1);
	
	OCR1A = 62500;
	
    while (1) 
    {
    }
}

ISR(PCINT2_vect)
{
	if(!(PIND & (1<<PIND3)))
	{
		
	}
}

ISR(ADC_vect)
{
	float resultVolt = ADCW;
}

ISR(TIMER1_COMPA_vect)
{
	
}

ISR(TIMER1_OVF_vect)
{
	
}