/*
 * uartpolling.c
 *
 * Created: 06.05.2022 14:07:09
 *  Author: manue
 */

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define BAUDRATE 9600 //BAUD RATE = wie viele Bits pro Sekunde, Symbolrate = wie viele Symbole pro Sekunde -> BAUD RATE == Symbolrate
#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)


void uart_init()
{
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0); //RXEN0 -> Empfänger ist aktiviert, sonst wäre er normaler I/O Port //TXEN0 -> Sender ist aktiviert 
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); //8bit Anzahl der Bits pro Frame
	UBRR0L = BAUD_PRESCALE;
	UBRR0H = (BAUD_PRESCALE >> 8);
}

char uart_getc(char *data){
	while((UCSR0A & (1<<RXC0)) == 0); //warten bis Zeichen eingelesen werden können
	*data = UDR0;
	return *data;
}

void uart_putc(char *data){
	while((UCSR0A & (1<<UDRE0)) == 0); //warten bis Senden möglich ist
	UDR0 = *data;
}

void uart_sendstring(char *str)
{
	unsigned char j=0;

	while (str[j]!=0)
	{
		uart_putc(&str[j]);
		j++;
	}
}