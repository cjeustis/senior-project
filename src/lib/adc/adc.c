#include "adc.h"
#include <avr/io.h>



float convert_adc_to_fahrenheit(uint16_t adc) {
	float c, v;
	/* Convert adc to voltage value */
	v = adc * 5.0;
	v = v / 1024.0;

	/* Convert voltage to celcius */
	c = (v - 0.5) * 10.0;

	/* Convert celcius to farenheit */
	return (c * 9.0 / 5.0) + 32.0;
}

void get_temp_reading(void) {
	// Start ADC0 conversion
	adc_enable_int();
	temps.channel = 0;
	start_adc(0);
	_delay_ms(10);

	// Start ADC1 conversion
	adc_enable_int();
	temps.channel = 1;
	_delay_ms(10);
	start_adc(1);
}

uint16_t start_adc(uint8_t channel) {
	// Set channel (& keeps it between 0-7)
	channel &= 0b00000111;
	// Clear bottom 3 bits beforing setting channel
	ADMUX = (ADMUX & 0xF8) | channel;

	// Start a Single conversion
	ADCSRA |= (1<<ADSC);

	// Wait for conversion to complete
	// while(ADCSRA & (1<<ADSC));

	return(ADC);
}

void adc_disable_int(void) {
	// Disable ADC interrupt
	ADCSRA &= ~(1<<ADIE);
}

void adc_enable_int(void) {
	// Disable ADC interrupt
	ADCSRA |= (1<<ADIE);
}

void set_reference(unsigned int ref)
{
	/* Clear bits */
	ADMUX &= ~(1<<REFS1) | ~(1<<REFS0);

	/* Set reference voltage */
	if (ref == 1)
	{
		ADMUX = (1<<REFS0);
	}
	else if (ref == 2)
	{
		ADMUX = (1<<REFS1);
	}
	else if (ref == 3)
	{
		ADMUX = (1<<REFS1) | (1<<REFS0);
	}
}

void set_prescaler(unsigned int prescaler)
{	
	// Clear bits
	ADCSRA &= ~(1<<ADTS2) | ~(1<<ADTS1) | ~(1<<ADTS0);

	if (prescaler == 2)
	{
		ADCSRA |= (1<<ADTS0);
	}
	else if (prescaler == 4)
	{
		ADCSRA |= (1<<ADTS1);
	}
	else if (prescaler == 8)
	{
		ADCSRA |= (1<<ADTS1) | (1<<ADTS0);
	}
	else if (prescaler == 16)
	{
		ADCSRA |= (1<<ADTS2);
	}
	else if (prescaler == 32)
	{
		ADCSRA |= (1<<ADTS2) | (1<<ADTS0);
	}
	else if (prescaler == 64)
	{
		ADCSRA |= (1<<ADTS1);
	}
	else if (prescaler == 128)
	{
		ADCSRA |= (1<<ADTS2) | (1<<ADTS1) | (1<<ADTS0);
	}
}

void init_adc(unsigned int ref, unsigned int prescaler)
{
	set_reference(ref);
	set_prescaler(prescaler);

	// Enable ADC
	ADCSRA |= (1<<ADEN);
}