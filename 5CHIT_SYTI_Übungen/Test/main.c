/*
 * Test.c
 *
 * Created: 12.04.2023 16:28:49
 * Author : manue
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <avr/interrupt.h>

volatile int button_pressed = 0;
volatile int startcnt30sek = 0;
volatile int startcnt15sek = 0;

volatile float resultVolt = 0;
volatile int timercnt = 0;

#define SPI_DDR DDRB
#define SPI_PORT PORTB
#define SS_PORT PORTB2

#define MOSI_PORT PORTB3
#define MISO_PORT PORTB4
#define SCK_PORT PORTB5

int main(void)
{
	DDRC |= (1<<PORTC2);
	DDRD |= (1<<PORTD2);
	
	PORTC |= (1<<PORTC1);
	PCICR |= (1<<PCIE1);
	PCMSK1 |= (1<<PCINT9);
	
	TCCR1B |= (1<<WGM12) | (1<<CS12);
	TIMSK1 |= (1<<OCIE1A);
	OCR1A = 62500;
	
	
	ADMUX |= (1<<REFS0) | (1<<MUX2) | (1<<MUX0);
	ADCSRA |= (1<<ADEN) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
	ADCSRA |= (1<<ADSC);
	
	TCCR0A |= (1<<WGM00) | (1<<WGM01);
	TCCR0A |= (1<<COM0A1);
	TCCR0B |= (1<<CS00);
	OCR0A = 0xFF - (int)(256-256 * resultVolt / 100);
	
	sei();
	
    while (1) 
    {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			if (button_pressed && !startcnt30sek)
			{
				startcnt30sek = 1;
				timercnt = 0;
			}
			
			if (startcnt30sek && !button_pressed)
			{
				startcnt30sek = 0;
			}
			
			if (startcnt30sek && (timercnt >= 30))
			{
				PORTC |= (1<<PORTC2);
				startcnt30sek = 0;
				startcnt15sek = 1;
				timercnt = 0;
			}
			
			if (startcnt15sek && (timercnt >= 15))
			{
				PORTD |= (1<<PORTD2);
			}
			
		}

    }
}

void spi_init()
{
	SPI_DDR |= (1<<MOSI_PORT) | (1<<MISO_PORT) | (1<<SS_PORT) | (1<<SCK_PORT);
	
	SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR0);
}

void SPI_MasterTransmit(char *cData)
{
	SPI_PORT &= ~(1<<SS_PORT);
	
	/* Start transmission */
	SPDR = *cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	
	SPI_PORT |= (1<<SS_PORT);
}


ISR(PCINT1_vect)
{
	if(!((PINC & (1<<PINC1)) == (1<<PINC1)))
	{
		button_pressed = 1;
	}
	else
	{
		button_pressed = 0;
	}
}

ISR(TIMER1_COMPA_vect)
{
	timercnt++;
}

ISR(ADC_vect)
{
	resultVolt = ADCW / 1024 * 100;
	
	ADCSRA |= (1<<ADSC);
}