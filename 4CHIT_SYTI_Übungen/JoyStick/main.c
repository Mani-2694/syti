/*
 * JoyStick.c
 *
 * Created: 04.02.2022 14:33:58
 * Author : manue
 */ 
#define F_CPU 16000000 //Taktfrequenz der CPU
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h" 
typedef struct{
	float x;
	float y;
}Cords;

typedef struct{
	int r;
	int g;
	int b;
}LED;

static volatile LED RGBLED = {.r=0,.g=0,.b=0};
static volatile Cords Koordinaten = {.x=0.0f,.y=0.0f};
int main(void)
{
	//ADC
	lcd_init(LCD_DISP_ON);
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADEN) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) |(1<<ADPS2);
	ADCSRA |= (1<<ADSC); //Wandlung starten
	sei();
	
	//PWM Ports auf Output setzen
	DDRB |= 0xFF;
	DDRD |= (1<<PORTD6);
	
	//Fast PWM 1 mit Top Value 0xFF
	TCCR1A |= (1<<WGM10) | (1<<WGM12); // setzt den Modus auf Fast PWM
    TCCR1A |= (1<<COM1A1) | (1<<COM1B1); // setzt den Output auf OC1A und OC1B
    TCCR1B |= (1<<CS10); // no Prescaler
	
	//Fast PWM 2 -> 1 PWM kann nur auf 2 Ports verwendet werden
	TCCR0A |= (1<<WGM00) | (1<<WGM01); // setzt den Modus auf Fast PWM
	TCCR0A |= (1<<COM0A1); // setzt den Output auf OC0A
	TCCR0B |= (1<<CS00); // no Prescaler
	
	while(1)
	{
		char ausg[10];
		lcd_clrscr();
	
		dtostrf(Koordinaten.x,6,2,ausg);
		lcd_puts(ausg);
		
		lcd_puts(" ");
		
		dtostrf(Koordinaten.y,6,2,ausg);
		lcd_puts(ausg);
		
		setRGB();
	
		_delay_ms(100);
	}
    
}
void setRGB()
{
	if (Koordinaten.x<-10)
	{
		RGBLED.r = 0;
		RGBLED.g = 0;
		RGBLED.b = 0;
	}
	else if (Koordinaten.x > RGBLED.r && Koordinaten.x > 10)
	{
		RGBLED.r=Koordinaten.x;
	}
	else if (-Koordinaten.y > RGBLED.b && Koordinaten.y < -10)
	{
		RGBLED.b = -Koordinaten.y;
	}
	else if (Koordinaten.y > RGBLED.r && Koordinaten.y > 10)
	{
		RGBLED.g = Koordinaten.y;
	}
	OCR0A = (0xFF/100*RGBLED.b); //Duty-Cycle
	OCR1A = (0xFF/100*RGBLED.g); //Duty-Cycle
	OCR1B = (0xFF/100*RGBLED.r); //Duty-Cycle
}

static int volatile adcCnt=0;
ISR(ADC_vect){
	
	switch(adcCnt%4){
		case 0:
			ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3));
			ADMUX |= (1<<MUX2);
			Koordinaten.x = (ADCW-512.0f)/5;
			break;
		case 2:
			ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3));
			ADMUX |= (1<<MUX0) | (1<<MUX2);
			Koordinaten.y = (ADCW-512.0f)/5;
			break;
		case 1:
			break;
		case 4:
			break;
		default:
			break;
		
	}
	ADCSRA |= (1<<ADSC);
	adcCnt++;
}
