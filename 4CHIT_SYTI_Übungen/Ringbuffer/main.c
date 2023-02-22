/*
 * main.c
 *
 */
#include <stdio.h>
#include "ringbuffer.h"
#include "testribu.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "uartpolling.h" // bei "" werden auch die lokalen Libaries durchsucht, <> nur globale
#include "lcd.h"

int main (int argc, char** argv)
{
	lcd_init(LCD_DISP_ON);
	(void)argc;
	(void)argv;
	
	uart_init();
	
	uint8_t data;
	
	ringbufferInit();
	char str[60];
	sprintf(str,"String %d",10);
	printf("%s",str);
	return;
	ringbufferGet(&data);

	uart_sendstring(printf("Data: %d\n",data));
	
#if 0
	if (testribuDoTests() != 0) {
		uart_sendstring("Tests NOT OK! \n");
		//printf("Tests NOT OK! \n");
	} else {
		uart_sendstring("Tests NOT OK! \n");
		//printf("Tests NOT OK! \n");
	}
#endif
	testribuManualTest();
	return 0;
}
