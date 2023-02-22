/*
 * BitOperation.c
 *
 * Created: 01.10.2021 14:40:51
 * Author : manue
 */ 

#define F_CPU 16000000 //Taktfrequenz der CPU
#include <util/delay.h>
#include <avr/io.h>
#define led1 0x01
#define led2 0x02
#define led3 0x04
#define led4 0x08
#define ledclear 0x00
#define leddelay 800

//Funktionen deklarieren
void RunnigLed1();
void RunnigLed2();
void RunnigLed3();

int main(void)
{
    /* Replace with your application code */
	DDRD = 0xFF;
	while (1)
	{
		RunnigLed6();
	}
}

/* ----------------------------------	*/
/* Function: void RunningLed1(void)		*/
/* Port D is used to control four LEDs	*/
/* Parameters: none						*/
/* Return values: none					*/
/* ----------------------------------	*/
void RunnigLed1(void)
{
	PORTD = led1;
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
	
	PORTD = led2;
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
	
	PORTD = led3;
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
	
	PORTD = led4;
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
}
void RunnigLed2(void)
{
	PORTD = (led1<<0); //wird um 0 verschoben
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
	
	PORTD = (led1<<1); // wird um 1 nach links verschoben 0001 -> 0010
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
	
	PORTD = (led1<<2); //0001 -> 0100
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
	
	PORTD = (led1<<4); //0001 -> 1 0000
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
}
void RunnigLed3(void)
{
	PORTD = (led1 << PORTD1); // wird auf Pin-Konstante PORTD1 verschoben
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
	
	PORTD = (led1 << PORTD2); 
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
	
	PORTD = (led1 << PORTD3); 
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
	
	PORTD = (led1 << PORTD4); 
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
}
void RunnigLed4(void)
{
	PORTD = (led1 << PORTD0); // wird auf Pin-Konstante PORTD0 verschoben
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
	
	PORTD = (led1 << PORTD1); 
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
	
	PORTD = (led1 << PORTD2);
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
	
	PORTD = (led1 << PORTD3);
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
	
	PORTD = (led1 << PORTD4);
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
	
	PORTD = (led1 << PORTD5);
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
	
	PORTD = (led1 << PORTD6);
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
		
	PORTD = (led1 << PORTD7);
	_delay_ms(leddelay);
	PORTD = ledclear;
	_delay_ms(50);
}
void RunnigLed5()
{
	for(int i=0;i<8;i++)
	{
		PORTD =(led1<<i);
		_delay_ms(50);
	}
	for(int i=0;i<8;i++)
	{
		PORTD =(led1<<(8-i));
		_delay_ms(50);
	}

}
void RunnigLed6()
{
		PORTD =0x3C;
		_delay_ms(1000);
		PORTD =0xC3;
		_delay_ms(leddelay);



}