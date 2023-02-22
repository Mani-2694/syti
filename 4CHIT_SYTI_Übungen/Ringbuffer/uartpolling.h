/*
 * uartpolling.h
 *
 * Created: 06.05.2022 14:06:34
 *  Author: manue
 */ 


#ifndef UARTPOLLING_H_
#define UARTPOLLING_H_


#include <stdint.h>

char uart_getc(char *data);

void uart_putc(char *data);

void uart_sendstring(char *str);


#endif /* UARTPOLLING_H_ */