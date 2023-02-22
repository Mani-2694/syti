/*
 * GccApplication1.c
 *
 * Created: 17.09.2021 15:36:15
 * Author : manue
 */ 

#define F_CPU 16000000 //Taktfrequenz der CPU
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{

    /* Replace with your application code */
	float leucht_dauer=800;
	DDRD = 0xFF; //Datenrichtungsregister -> auf Output gesetzt
    while (1) 
    {
		 //DDRD = 0x01;
		 //PORTD = 0x01;
		 //_delay_ms(100);
		 //PORTD = 0x00;
		 //_delay_ms(50);
		 
		 PORTD = 0x02;
		 _delay_ms(leucht_dauer);
		 PORTD = 0x00;
		 _delay_ms(50);

		 PORTD = 0x04;
		 _delay_ms(leucht_dauer);
		 PORTD = 0x00;
		 _delay_ms(50);

		 PORTD = 0x08;
		 _delay_ms(leucht_dauer);
		 PORTD = 0x00;
		 _delay_ms(50);

		 PORTD = 0x10;
		 _delay_ms(leucht_dauer);
		 PORTD = 0x00;
		 _delay_ms(50);

		 PORTD = 0x20;
		 _delay_ms(leucht_dauer);
		 PORTD = 0x00;
		 _delay_ms(50);
		 
		 PORTD = 0x40;
		 _delay_ms(leucht_dauer);
		 PORTD = 0x00;
		 _delay_ms(100);
		 
    }
}

