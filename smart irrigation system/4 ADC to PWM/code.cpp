#define F_CPU 8000000UL;
#include <avr/io.h>
#include <stdlib.h>
#include <math.h>

void adc_init(void){
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADSC);
}
uint16_t read_adc(uint8_t channel){
	ADMUX &= 0xF0;
	ADMUX |= channel;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return ADCW;
}

int main(void)
{
	float c,duty;
	DDRA = 0x00;
	TCCR0 =0b01101001;
	DDRB=0b00001000;
	adc_init();
	while (1)
	{
		c=read_adc(0)*5/1024;
		if (c<2.5)
		{
			duty=c*51;
			OCR0=duty;
		}
		else
		OCR0=0;
	}
}