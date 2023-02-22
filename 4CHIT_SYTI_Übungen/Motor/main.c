/*
 * Motor.c
 *
 * Created: 25.03.2022 14:15:28
 * Author : manue
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "lcd.h"

volatile float resultVolt = 0.0;
int main(void)
{
	lcd_init(LCD_DISP_ON);
		
	//Richtung-Änderung-Ports
	//Button -> PORTC4
	//Ports -> PORTB4 und PORTB5
	DDRB |= (1<<PORTB4) & (1<<PORTB5);
	PCMSK1|=(1<<PCINT8);   //erlaubt PCINT8 einen Interrupt auszulösen
	PCICR |=(1<<PCIE1); //festgelegt, wann Interrupt aufgerufen wird PCIE1 = any change on any PCINT14..8
	
	//ADC
	DDRC &= (1<<PORTC5);
	PORTC |= (1<<PORTC5);
	
	ADMUX |= (1<<REFS0) | (1<<MUX0) |(1<<MUX2);
	ADCSRA |= (1<<ADEN) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) |(1<<ADPS2);
	ADCSRA |= (1<<ADSC); //Wandlung starten
		

	//PWM
	DDRD |= (1<<PORTD6);
	
	//Fast PWM 1 mit Top Value 0xFF
	TCCR0A |= (1<<WGM00) | (1<<WGM01); // setzt den Modus auf Fast PWM
	TCCR0A |= (1<<COM0A1); // Clear on Compare Modus
	TCCR0B |= (1<<CS00); // no Prescaler

	
	sei();
	while (1)
	{
		lcd_clrscr();
		SetMotor();
		switchmode();

		char ausg[10];
		lcd_clrscr();
		
		dtostrf(resultVolt,6,0,ausg);
		lcd_puts(ausg);
		lcd_puts("% Geschw.");

		_delay_ms(300);
	}
}
void SetMotor()
{
	OCR0A = (0xFF-50/100*resultVolt); //Duty-Cycle
}
static volatile int status=0;
void switchmode(void)
{
	if(status%2)
	{
		PORTB &= ~(1<<PORTB5);
		PORTB |= (1<<PORTB4);
	}
	else
	{
		PORTB &= ~(1<<PORTB4);
		PORTB |= (1<<PORTB5);
	}
}

ISR(PCINT1_vect) //PIN Change Interrupt Routine
{
	if((PINC & (1 << PINC4)) == (1<<PINC4))
	{
		status+=1;
	}
}

ISR(ADC_vect){
	//Wandlung auslesen und auf Wert zwischen 0 und 100 rechnen
	uint16_t result = ADCW;
	resultVolt = (result/1024)*100;
	
	//Wandlung starten
	ADCSRA |=(1<<ADSC);
}
