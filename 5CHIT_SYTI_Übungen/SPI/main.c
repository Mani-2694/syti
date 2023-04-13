/*
 * SPI.c
 *
 * Created: 09.03.2023 11:45:07
 * Author : manue
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "dht11/dht.h"
#include "LCD/lcd.h"
#include "SPI/spi.h"

static volatile int8_t temperature = 0;
static volatile int8_t humidity = 0;

static volatile int maxtemp = 50;
static volatile int ledsteps = 8;

int main(void)
{
	lcd_init(LCD_DISP_ON);
	
	spi_init();
		
	char output [40];

    while (1) 
    {
		lcd_clrscr();
		char ausg [10];
				
		int8_t resultValue = dht_gettemperaturehumidity(&temperature, &humidity);
					
		sprintf(output,"temp: %d",temperature);
		lcd_puts(output);
		
		lcd_gotoxy(0, 1);
		
		sprintf(output,"humid: %d",humidity);
		lcd_puts(output);
		
		int led = temperature * ledsteps / maxtemp;
		sprintf(output, " LED:%d", led);
		lcd_puts(output);
		
		uint8_t shiftvalue = 0;
		for (int i=0; i<led; i++)
		{
			shiftvalue |= (1<<i);
		}
		
		SPI_MasterTransmit(&shiftvalue);
		
		_delay_ms(500);
    }
}