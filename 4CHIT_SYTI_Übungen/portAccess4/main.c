/*
 * portAccess4.c
 *
 * Created: 15.10.2021 14:12:57
 * Author : manue
 */ 

#define F_CPU 16000000 //Taktfrequenz der CPU
#include <util/delay.h>
#include <avr/io.h>


#define led 0x80
#define ledclear 0x00
#define button 0x40

void PushButtonAndLED();
void switchAndLED();
void highEndRunningLED();

int main(void)
{
	//DDRD =~button; 
	DDRC =0xF8;
	DDRD = 0xFF;
	while(1)
	{
		//PushButtonAndLED()
		//switchAndLED();
		highEndRunningLED();
	}
}
void PushButtonAndLED(void) 
{
	//DDRD =~button;
	if (PIND==64)
	{
		PORTD=led;
	}
	else
	{
		PORTD = ledclear;
	}
}
static int status=0; //statische Variable, ist nur in dem Programm sichtbar
void switchAndLED(void)
{
	if ((PIND & (1 << PIND6)) == 64)
	{
		if(status==0)
		{
			PORTD = ledclear;
			status = 1;
		}
		else if(status==1)
		{
			PORTD = led;
			status = 0;
		}
		_delay_ms(400);
	}
}
static int delay=1;
void highEndRunningLED(void)
{	
	if((PINC & (1 << PINC0)) == 0x01) //aktiven Port überprüfen
	{
		delay=1;
	}
	else if((PINC & (1 << PINC1)) == 0x02)
	{
		delay=3;
	}
	else if((PINC & (1 << PINC2)) == 0x04)
	{
		delay = 6;
	}
 
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

