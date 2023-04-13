/*
 * spi.c
 *
 * Created: 23.03.2023 11:00:35
 *  Author: manue
 */

#include <avr/io.h> 
#include "spi.h"

void spi_init()
{
	// MOSI, SCK, und SS ports auf Output setzen
	DDRB |= (1 << MOSI_PIN) | (1 << SCK_PIN) | (1 << SS_PIN);
	
	// SPI aktivieren, set as master, Clock Rate fosc/16 setzen
	SPCR = (1<<SPIE) | (1<<SPE) | (1<<MSTR) | (1<<SPR0);
}

void SPI_MasterTransmit(uint8_t *value)
{
	// Enable slave (active low)
	SS_PORT &= ~(1 << SS_PIN);
	
	/* Start transmission */
	SPDR = *value;
	
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	
	// Disable slave
	SS_PORT |= (1 << SS_PIN);
}