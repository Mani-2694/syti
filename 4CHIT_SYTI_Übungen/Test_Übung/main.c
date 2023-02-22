/*
 * Test_Uebung.c
 *
 * Created: 25.01.2022 19:37:28
 * Author : manue
 */ 
#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

static volatile int status=0;
int main(void)
{
	init();
    while (1) 
    {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			if(status==1)
			{
				PORTB |= (1<<PORTB0);
			}
			else if(status==0)
			{
				PORTB &= (1<<PORTB0);
			}
		}

    }
}

int init(void)
{
	PORTC |= (1<<PORTC0) | (1<<PORTC1);
	PCMSK1 |= (1<<PCINT8) | (1<<PCINT9); //erlaubt Interrupt auf diesen Port zuzulassen
	PCICR |= (1<<PCIE0) //wann wird Interrupt aufgerufen
	DDRB |= (1<<PORTB0); //auf Output setzen
	sei();
}

ISR(PCINT1_vect)
{
	if(!(PINC & (1<<PORTC0)))
	{
		status = 1;
	}
	else if(!(PINC & (1<<PORTC1)))
	{
		status = 0;
	}
}

