/*
 * MeasureBot.c
 *
 * Created: 20.10.2022 10:54:46
 * Author : manue
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "lcd.h"

#define BAUDRATE 9600 //BAUD RATE = wie viele Bits pro Sekunde, Symbolrate = wie viele Symbole pro Sekunde -> BAUD RATE == Symbolrate

static volatile float resultVolt = 0.0;
static volatile int adcStatus = 0; //if adc reads or not
static volatile int systemStatus = 1; //if System is on or not
static volatile int transmitInverval = 1;
static volatile int allowSerialSend=0;

volatile int buttonPressed = 0;
volatile int LCDStatus = 1;
volatile int counter = 0;

typedef struct _EepromData  {
	int size;
	int value;
} EepromData;

int main(void)
{
	sei();
	
	lcd_init(LCD_DISP_ON);
	
	init();
		
	while(1)
	{
		lcd_clrscr();
		
		if(buttonPressed == 1)
		{
			if(systemStatus)
			{
				lcd_clrscr();
				lcd_puts("Good Bye!");
				_delay_ms(600);
				systemStatus=0;
			}
			else
			{
				lcd_clrscr();
				lcd_puts("Hello!");
				_delay_ms(600);
				systemStatus=1;
			}
			buttonPressed = 0;
		}
		else if(buttonPressed == 2)
		{						
			lcd_puts("t");	
			buttonPressed = 0;
		}

		
		_delay_ms(1000);
	}
}

void init()
{
	//Button-Interrupts
	PCMSK1|=(1<<PCINT11);   //erlaubt PCINT11 einen Interrupt auszulösen
	PCMSK1 |=(1<<PCINT12);  //erlaubt PCINT12 einen Interrupt auszulösen
	PCICR |=(1<<PCIE1); //festgelegt, wann Interrupt aufgerufen wird PCIE1 = any change on any PCINT14..8
	
}

ISR(PCINT1_vect) //PIN Change Interrupt Routine, 1 legt Priorität fest
{
	if((PINC & (1 << PINC3)) == (1<<PINC3))
	{
		buttonPressed = 1;
	}
	else if((PINC & (1 << PINC4)) == (1<<PINC4))
	{
		buttonPressed = 2;
	}
}

ISR(PCINT1_vect)
{	
	/*char buff[20];
	itoa(PINC & ((1<<PINC3) | (1<<PINC4)), buff, 16);
	lcd_clrscr();
	lcd_puts(buff);
	_delay_ms(2000);*/
	
	//if(PINC & (1 << PINC3) == (1<<PINC3))
	//{
		//buttonPressed = 1;
		////lcd_puts("test1");
		////_delay_ms(1000);
	//}
	
	if(PINC & (1 << PINC4) == (1<<PINC4))
	{
		PORTB |= (1<<PORTB0);
		buttonPressed = 3;
		//lcd_puts("hallooo");
		//_delay_ms(1000);
	}
}