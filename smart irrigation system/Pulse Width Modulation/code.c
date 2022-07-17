/*
 * Simple PWM.c
 *
 * Created: 09-07-2022 23:25:58
 * Author : Manthan
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>


int main(void)
{
	unsigned char duty;
	duty=128;
	TCCR0 =0b01101001;
	DDRB=0b00001000;
    while (1) 
    {
			OCR0=duty; 
    }
}

