/*
 * spi.h
 *
 * Created: 23.03.2023 11:00:46
 *  Author: manue
 */ 

#define SS_PORT     PORTB
#define SS_DDR      DDRB
#define SS_PIN      PORTB2

#define MOSI_PIN    PORTB3
#define MISO_PIN    PORTB4
#define SCK_PIN     PORTB5

void spi_init();

void SPI_MasterTransmit(uint8_t *value);