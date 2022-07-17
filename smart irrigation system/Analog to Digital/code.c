/*
 * ADC1.c
 *
 * Created: 02-07-2022 20:37:29
 * Author : Manthan
 */ 
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
	unsigned long b,c;
	int i=0,d=0;
	DDRD = 0b00000111;
	DDRA = 0x00;
	adc_init();
	
	
	
	
	while (1)
	{
		c=read_adc(0)*5/1023;
		if (c>0 && c<=1)
		{
			PORTD =0b00000001;
		}
		else if (c>1 &&c<=2)
		
			PORTD=0b00000010;
		
		else if (c>2 && c<=3)
		
			PORTD=0b00000011;
		
		else if (c>3 && c<=4)
		{
			PORTD=0b00000100;
		}
		else if(c>4 && c<=5)
		{
			PORTD=0b00000101;
		}
		
	}

}
