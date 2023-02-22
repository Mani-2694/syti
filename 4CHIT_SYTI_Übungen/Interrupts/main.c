/*
 * Interrupts.c
 *
 * Created: 12.11.2021 14:42:39
 * Author : manue
 */ 
#define F_CPU 16000000 //Taktfrequenz der CPU
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#define led 0x01
#define ledclear 0x00


#define BSP3


static void PushButtonAndLED();
static void switchAndLED();
static void highEndRunningLED();

int main(void)
{
	DDRD = 0xFF;
	
	PCMSK1|=(1<<PCINT8);   //erlaubt PCINT8 einen Interrupt auszulösen
	PCMSK1 |=(1<<PCINT9);  //erlaubt PCINT9 einen Interrupt auszulösen
	PCMSK1 |=(1<<PCINT10); //erlaubt PCINT10 einen Interrupt auszulösen
	PCICR |=(1<<PCIE1); //festgelegt, wann Interrupt aufgerufen wird PCIE1 = any change on any PCINT14..8
	
	sei(); //aktiviert Interrupts
	
    while (1) 
    {
		#ifdef BSP1
		PushButtonAndLED();
		#elif defined BSP2
		switchAndLED();
		#elif defined BSP3
		highEndRunningLED();
		#endif
    }
}


#ifdef BSP1

static volatile int ledon=0; //volatile = Compiler löscht Variable nicht, wenn er meint, dass diese nicht mehr verwendet wird
void PushButtonAndLED(void)
{
	if (ledon%2)
	{
		PORTD |=led;
	}
	else
	{
		PORTD &= ~led;
	}
}

ISR(PCINT1_vect) //PIN Change Interrupt Routine -> 1 legt Priorität fest
{
	ledon+=1;
}

#elif defined BSP2

static volatile int status=0;
void switchAndLED(void)
{
	if(status%2)
	{
		PORTD|=led;
	}
	else
	{
		PORTD &= ~led;
	}
}

ISR(PCINT1_vect) //PIN Change Interrupt Routine
{
	if((PINC & (1 << PINC0)) == (1<<PINC0))
	{ 
		status+=1;
	}
}

#elif defined BSP3

static volatile int delay=3;
void highEndRunningLED(void)
{
	for(int i=0;i<4;i++)
	{
		PORTD =(0x01<<i);
		for(int d=0;d<=delay;d++)
		{
			_delay_ms(300);
		}
	}
	_delay_ms(200);
}

ISR(PCINT1_vect)//PIN Change Interrupt Routine
{
	
	if((PINC & (1 << PINC0)) == (1<<PINC0))
	{
		delay=1;
	}
	else if((PINC & (1 << PINC1)) ==(1<<PINC1))
	{
		delay=3;
	}
	else if((PINC & (1 << PINC2)) == (1<<PINC2))
	{
		delay = 6;
	}

}
#endif
