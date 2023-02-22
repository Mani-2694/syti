/*
 * LCD_Display.c
 *
 * Created: 03.12.2021 14:22:28
 * Author : manue
 */ 

#define F_CPU 16000000 //Taktfrequenz der CPU
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "lcd.h"
#define BSP2

volatile static unsigned long msticker =0;
static volatile int status=0;
int main(void)
{		
	lcd_init(LCD_DISP_ON);
	lcd_home();

	#ifdef BSP1
	
	char string[20] ="Hello World";
	int length=strlen(string);
		
	while(1)
	{
		
		for(int i=length-1;i>=0;i--)
		{
			lcd_clrscr(); //Display löschen
			char sub[20];
			int c=0;
			
			while (c <length)
			{
				sub[c] = string[c+i];
				c++;
			}
			sub[c] = '\0';
			lcd_home(); //Cursor setzen
			lcd_puts(sub); //Ausgabe auf Display
			_delay_ms(1000);
		}
		
		int cnt=0;
		while(cnt<16)
		{
			cnt++;
			lcd_clrscr();
			lcd_gotoxy(cnt,0);
			lcd_puts(string);
			_delay_ms(1000);
		}
	}
		
	#elif defined BSP2
		
	PCMSK1|=(1<<PCINT11);   //erlaubt PCINT8 einen Interrupt auszulösen
	PCICR |=(1<<PCIE1); //festgelegt, wann Interrupt aufgerufen wird PCIE1 = any change on any PCINT14..8
		
	//CTC Mode -> Clear Timer on Compare Modus -> Timer wird gelöscht, wenn der Wert dem Register entspricht
	TCCR0A |=(1<<WGM01);
	//Prescaler 64 -> teilt Taktfrequenz, um Geschwindigkeit des Timers zu verringern
	TCCR0B |=(1<<CS01) | (1<<CS00);
	//Taktzyklus = 16000000/64 => 4 => 250 Takte zu je 4qs = 1ms
	OCR0A = 250;
	TIMSK0 |=(1<<OCIE0A);
			
	sei();
	while(1)
	{
		if(status==1)
		{
			lcd_clrscr();
			char ausg[16];
			sprintf(ausg, "%d", msticker);
			lcd_puts(ausg);
			_delay_ms(200);
		}
	}
	#endif
}

ISR(PCINT1_vect)//PIN Change Interrupt Routine
{
	if((PINC & (1 << PINC3)) == (1<<PINC3))
	{
		if(status==0)
		{
			status = 1;
		}
		else
		{
			status=0;
			msticker=0;
		}
		_delay_ms(200);

	}

}
ISR(TIMER0_COMPA_vect)
{
	if(status==1)
	{
		msticker++;
	}
}
