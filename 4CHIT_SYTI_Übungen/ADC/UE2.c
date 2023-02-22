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
	lcd_init(LCD_DISP_ON);
    ADMUX |= (1<<REFS0) | (1<<MUX0) |(1<<MUX2);
    ADCSRA |= (1<<ADEN) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) |(1<<ADPS2);
    ADCSRA |= (1<<ADSC); //Wandlung starten
	
    sei();
    while (1)
    {
		lcd_clrscr();
		sprintf(buffer, "Spg: %.2f V", resultVolt);
		lcd_puts(buffer);
		SwitchLeds(resultVolt);
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
		lcd_clrscr();
        lcd_puts("Button 3");
    }
    else if (x < 2)
    {
        lcd_clrscr();
        lcd_puts("Button 2");
    }
    else
    {
       	lcd_clrscr();
       	lcd_puts("Button 1");
    }
}