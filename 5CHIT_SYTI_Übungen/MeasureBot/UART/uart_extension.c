/*
 * uart_extension.c
 *
 * Created: 18.01.2023 19:11:45
 *  Author: manue
 */ 

#include <avr/io.h>
#include "uart_extension.h"
#include "uart.h"

//uint8_t rx_state = WAIT;  // Aktueller Status von UART
rxStatus rx_state = WAIT;
uint16_t string_index = 0;     // Index von Buffer
volatile char buffer[BUFFER_SIZE]; //Buffer für UART

void uart_put_string(char *string)
{
	char output[BUFFER_SIZE];
	
	sprintf(output, "%s%s%s", C_BEGIN, string, C_ESC);
	uart_puts(output);
}

int handle_uart_values()
{
	uint8_t tmp_value;

	switch(rx_state)
	{
		case WAIT:
		if (uart_check_for_value(&tmp_value))
		{
			if (tmp_value == C_BEGIN[0])
			{
				rx_state = ACCEPT;
			}
		}
		break;

		case ACCEPT:
		if (uart_check_for_value(&tmp_value))
		{
			if(tmp_value == C_BEGIN[0]) // header should never exist here
			{
				rx_state = ERROR;
			}
			if(tmp_value == C_ESC[0])
			{
				rx_state = ESCAPE;
			}
			else
			write_char_to_buffer(&tmp_value);
		}
		break;
		
		case ERROR:
		buffer[0] = '\0'; //Buffer leeren, idem man erstes Element auf 0 setzt
		string_index = 0;
		rx_state = WAIT;
		char output[40];
		sprintf(output,"M%s[%s]", C_TYPE_DELIMITER, "Failed");
		uart_put_string(output);
		break;

		case ESCAPE:
		string_index++;
		buffer[string_index] = '\0'; //Buffer beenden
		string_index = 0;
		return 1;
	};
	
	return 0;
}

//prüfen, ob etwas über den Seriellen Port eingelesen werden kann, wenn ja in Pointer speichern und zurücksenden
int uart_check_for_value(uint8_t *value)
{
	uint16_t uart_value = uart_getc();
	
	if (!(uart_value & UART_NO_DATA))
	{
		*value = ((uint8_t)uart_value);
		uart_putc(*value);
		
		return 1;
	}
	return 0;
}

//eingelesenes char (uint8_t == unsigned char mit 8 bit) zu buffer hinzufügen
void write_char_to_buffer(uint8_t *value)
{
	buffer[string_index] = (char)*value;
	
	string_index ++;
}

//CharArray Buffer iterieren und in den mitgegebenen CharArray Pointer schreiben
void read_buffer(char *output)
{
	int cnt;
	for (cnt=0; buffer[cnt] != '\0'; cnt++)
	{
		output[cnt] = buffer[cnt];
	}
	output[cnt] = '\0'; //char array beenden
	memset(buffer,0,sizeof(buffer)); //Buffer leeren
	rx_state = WAIT;
}