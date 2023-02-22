/*
 * Serial_Port.c
 *
 * Created: 29.04.2022 14:14:06
 * Author : manue
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "uartpolling.h" // bei "" werden auch die lokalen Libaries durchsucht, <> nur globale

int main()
{
	char *data;
	
	uart_init();
	uart_sendstring("Hallo\r\n");
	while(1)
	{
		uart_getc(&data);
		uart_putc(&data);
	}
}
