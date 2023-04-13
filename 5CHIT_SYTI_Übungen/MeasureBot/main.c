/*
 * MeasureBot.c
 *
 * Created: 20.10.2022 10:54:46
 * Author : manue
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdio.h>
#include "LCD/lcd.h"
#include "ADC/adc.h"
#include "UART/uart.h"
#include "UART/uart_extension.h"
#include "EEPROM/eeprom.h"

#define BAUDRATE 9600 //BAUD RATE = wie viele Bits pro Sekunde, Symbolrate = wie viele Symbole pro Sekunde -> BAUD RATE == Symbolrate

static volatile float resultVolt = 0.0;
static volatile int adcStatus = 0; //if adc reads or not
static volatile int buttonStatus = 0; //Status for the 2 buttons
static volatile int systemStatus = 1; //if System is on or not
static volatile unsigned long timercntfortransmit = 0; //cnt für Timer
static volatile unsigned long timercntfordisplay = 0;
static volatile int serialTransmit = 0;

extern EepromData eepromData;

void init();
void StartMessageDisplay();
void CloseMessageDisplay();

int main(void)
{
	StartMessageDisplay();
	
	sei();
	
	init();
	init_adc();
	uart_init(UART_BAUD_SELECT(BAUDRATE, F_CPU));
	
	start_adc();
	
	LoadTransmitIntervalFromEEPROM();
	
	if(!VerifyCheckSum())
	{
		lcd_clrscr();
		lcd_puts("Checksum invalid");
	}

	DDRD |=  (1<<PORTD6);
	
	while(1)
	{	
		if(systemStatus && adcStatus)
		{
			adcStatus=0;
			//erneute Wandlung starten
			start_adc();
		}
		
		if(buttonStatus == 1)
		{
			if(systemStatus)
			{
				CloseMessageDisplay();
				systemStatus=0;
			}
			else
			{
				StartMessageDisplay();
				systemStatus=1;
			}
			buttonStatus = 0;
		}
		else if(buttonStatus == 2 && systemStatus)
		{
			eepromData.transmitInterval++;
			if(eepromData.transmitInterval>4)
			{
				eepromData.transmitInterval=0;
			}
							
			SafeTransmitIntervalToEEPROM();
			buttonStatus = 0;
		}

		if(systemStatus)
		{
if(handle_uart_values())
{
	char uart_value[20];
	char output [40];
				
	//uart_put_string("Read");
	read_buffer(uart_value);

	if(strcmp(uart_value, "B;a") == 0)
	{
		char ausg [10];
		dtostrf(resultVolt,3,0,ausg);
		//sprintf(output,"photo_voltage: %s, switch: %d",ausg,systemStatus);
					
		sprintf(output,"M%s[%s%s%s%s%s%s%d]", C_TYPE_DELIMITER, "photo_voltage", C_DEVICE_DATA_DELIMITER, ausg, C_DEVICE_DELIMITER, "switch", C_DEVICE_DATA_DELIMITER, systemStatus);
		uart_put_string(output);
	}
	else if(strcmp(uart_value, "B;t") == 0)
	{
		serialTransmit = 1;
					
		sprintf(output,"M%s[%s]", C_TYPE_DELIMITER, "OK");
		uart_put_string(output);
	}
	else if(strcmp(uart_value, "B;q") == 0)
	{
		serialTransmit = 0;
		char output [40];
					
		//sprintf(output,"photo_voltage: %s, switch: %d",ausg,systemStatus);
		sprintf(output,"M%s[%s]", C_TYPE_DELIMITER, "OK");
		uart_put_string(output);
	}
	else if (strncmp(uart_value, "B;tr", 4) == 0)
	{
		int x = (int)uart_value[4] - 48;

		if((x >= 0) & (x <= 4))
		{
			eepromData.transmitInterval = x;
			SafeTransmitIntervalToEEPROM();
						
			sprintf(output,"M%s[%s]", C_TYPE_DELIMITER, "OK");
			uart_put_string(output);
		}
		else
		{
			sprintf(output,"M%s[%s]", C_TYPE_DELIMITER, "NOK");
			uart_put_string(output);
		}
	}
	else
	{
		sprintf(output,"M%s[%s]", C_TYPE_DELIMITER, "NOK");
		uart_put_string(output);
	}

	memset(uart_value,0,sizeof(uart_value)); //Serial Storage leeren
}
		}
		
		ATOMIC_BLOCK(ATOMIC_FORCEON)
		{	
			if(eepromData.transmitInterval != 0 && systemStatus && serialTransmit && (timercntfortransmit > eepromData.transmitInterval*1000))
			{
				timercntfortransmit = 0;
				
				char ausg [10];
				dtostrf(resultVolt,3,0,ausg);
				char output [100];
				//sprintf(output,"M;photo_voltage: %s, switch: %d",ausg,systemStatus);
				sprintf(output,"M%s[%s%s%s%s%s%s%d]", C_TYPE_DELIMITER, "photo_voltage", C_DEVICE_DATA_DELIMITER, ausg, C_DEVICE_DELIMITER, "switch", C_DEVICE_DATA_DELIMITER, systemStatus);
				uart_put_string(output);
			}
		}
		
		
		//Display Refresh nach 1.5s (über Timer anstatt mit Delay)
		if (timercntfordisplay < 1500)
			continue;

		lcd_clrscr();

		//Sensorwert ausgeben
		char ausg [10];
		dtostrf(resultVolt,3,0,ausg);
		lcd_puts(ausg);
		lcd_puts("%");
		
		//Interval ausgeben
		char output[10];
		lcd_gotoxy(0, 1);
		sprintf(output, "Interval: %d", eepromData.transmitInterval);
		lcd_puts(output);
		
		//_delay_ms(300); kein Delay mehr notwendig
		timercntfordisplay=0;
	}
}

void init()
{
	//Button-Interrupts
	PCMSK1|=(1<<PCINT11);   //erlaubt PCINT11 einen Interrupt auszulösen
	PCMSK1 |=(1<<PCINT12);  //erlaubt PCINT12 einen Interrupt auszulösen
	PCICR |=(1<<PCIE1); //festgelegt, wann Interrupt aufgerufen wird PCIE1 = any change on any PCINT14..8
	
	//Timer
	//CTC Mode -> Clear Timer on Compare Modus -> Timer wird gelöscht, wenn der Wert dem Register entspricht
	TCCR0A |=(1<<WGM01);
	//Prescaler 64 -> teilt Taktfrequenz, um Geschwindigkeit des Timers zu verringern
	TCCR0B |=(1<<CS01) | (1<<CS00);
	//Taktzyklus = 16000000/64 => 4 => 250 Takte zu je 4qs = 1ms
	OCR0A = 250;
	TIMSK0 |=(1<<OCIE0A);
}

void StartMessageDisplay()
{
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_puts("Hello!");
	_delay_ms(600);
}

void CloseMessageDisplay()
{
	lcd_clrscr();
	lcd_puts("Good Bye!");
	_delay_ms(600);
	lcd_init(LCD_DISP_OFF);
}
  
ISR(ADC_vect){
	//Wandlung auslesen
	resultVolt = read_adc()/9; //durch 900 für max Wert und * 100 für Prozent
	
	// ADC-Wert wurde ausgelesen
	adcStatus = 1;
}

ISR(PCINT1_vect) //PIN Change Interrupt Routine, 1 legt Priorität fest
{
	if((PINC & (1 << PINC3)) == (1<<PINC3))
	{
		buttonStatus = 1;
	}
	else if((PINC & (1 << PINC4)) == (1<<PINC4))
	{
		buttonStatus = 2;
	}
}

ISR(TIMER0_COMPA_vect) 
{
	if(serialTransmit)
	{
		timercntfortransmit++;
	}
	
	timercntfordisplay++;
}