/*
 * ADC.c
 *
 * Created: 21.01.2022 14:22:28
 * Author : manue
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "lcd.h" 

volatile float resultVolt = 0.0;
volatile uint8_t buffer[16];

void SwitchLeds(float x);

int main(void)
{
	DDRB = 0xFF;
	//Pull-Up verwenden, um kein Button zu erkennen
	DDRC &= (1<<PORTC5);
	PORTC |= (1<<PORTC5);
	
	lcd_init(LCD_DISP_ON);
    ADMUX |= (1<<REFS0) | (1<<MUX0) |(1<<MUX2);
    ADCSRA |= (1<<ADEN) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) |(1<<ADPS2);
    ADCSRA |= (1<<ADSC); //Wandlung starten
	
    sei();
    while (1)
    {
		
		//sprintf(buffer, "Spg: %.2f V", resultVolt);
		//lcd_puts(buffer);
		DefineButton(resultVolt);
		_delay_ms(500);
    }
}
ISR(ADC_vect){
	//Wandlung auslesen
    uint16_t result = ADCW;
    resultVolt = (result/ 1024.0)*5.0;
	
	//Wandlung starten
	ADCSRA |=(1<<ADSC);
}

void SwitchLeds(float x){
    if(x > 4)
    {
        PORTB =(1<<PORTB2);
    }
    else if (x < 2)
    {
        PORTB = (1<<PORTB0);
    }
    else
    {
        PORTB = (1<<PORTB1);
    }
}
void DefineButton(float x){
	lcd_clrscr();

	//Überprüfen, ob kein Button gedrückt ist
	if(x > 4.9)
	{
		lcd_puts("no button");
	}
	else if(x > 3)
	{
		lcd_puts("Button 1");
	}
	else if (x > 2)
	{
		lcd_puts("Button 2");
	}

	else
	{
		lcd_puts("Button 3");
	}
}