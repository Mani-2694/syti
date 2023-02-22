/*
 * TestUebung.c
 *
 * Created: 22.02.2023 16:15:40
 * Author : manue
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD/lcd.h"
#include "UART/uart.h"
#include <util/atomic.h>

volatile int status = 0;
char buffer[16];

#define BAUD_RATE 9600
#define Prescale ((F_CPU/(BAUD_RATE*16UL))-1)

int main(void)
{
	lcd_init(LCD_DISP_ON);
	DDRB |= (1<<PORTB0);
	DDRD |= (1<<PORTD6);
	PORTD |= (1<<PORTD6);
	
	
	//Button
	DDRB &= ~(1<<PORTB1);
	PCMSK0 |= (1<<PCINT1);
	PCMSK1 |= (1<<PCINT11) | (1<<PCINT12);
	PCICR |= (1<<PCIE0);
	
	//ADC
	ADCSRA |= (1<<ADEN) | (1<<ADIE);
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
	ADMUX |= (1<<REFS0) | (1<<MUX0) | (1<<MUX1);
	ADCSRA |= (1<<ADSC);
	
	//16bit Timer alle 1s wird Compare Match ausgelöst
	TCCR1A |= (1<<WGM12);
	TCCR1B |= (1<<CS10) | (1<<CS12);
	OCR1A = 15625;
	TIMSK1 |= (1<<OCIE1A);
	
	
	//PWM auf PORTD6
	TCCR0A |= (1<<WGM00) | (1<<WGM01);
	TCCR0B |= (1<<CS00) | (1<<CS02);
	TCCR0A |= (1<<COM0A1);
	OCR0A = 2;
	
	//UART
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0) | (1<<UDRIE0);
	UCSR0C |= (1<<UPM01) | (1<<UCSZ00) | (1<<UCSZ01);
	//UBRR0L |= Prescale;
	uart_init(UART_BAUD_SELECT(BAUD_RATE, F_CPU));
	//UBRR0H |= BAUD_RATE;
	
	
	sei();
	char output[16] = "ab\0";
	TestPointer(output);
	
	for (int i=0; output[i]!='\0'; i++)
	{
		lcd_putc(output[i]);
	}
			
    while (1) 
    {
		//lcd_clrscr();
		//sprintf(buffer, "%d", status);
		//lcd_puts(buffer);
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			if (status %2 == 0)
			{
				PORTB |= (1<<PORTB0);
				status = 0;
			}
			else
			{
				PORTB &= ~(1<<PORTB0);
			}
		}


		//while((UCSR0A & (1<<UDRE0))==0)
			//UDR0 ='x';
			
		//while((UCSR0A & (1<<RXC0)) == 0)
			//lcd_putc(UDR0);

		_delay_ms(200);
    }
}

void TestPointer(char *value)
{
	lcd_puts(value);
	int cnt=0;
	for(int i=0; i<sizeof(value);i++)
	{
		lcd_putc(value[i]);
	}
	while(value[cnt]!='\0')
	{
		lcd_putc(value[cnt]);
		cnt++;
	}
}

ISR(ADC_vect)
{
	return ADCW/1024;
}

ISR(PCINT0_vect)
{
	if((PINB & (1<<PINB1)))
	{
		status=2;
	}

}


ISR(TIMER1_COMPA_vect)
{
	status++;
}