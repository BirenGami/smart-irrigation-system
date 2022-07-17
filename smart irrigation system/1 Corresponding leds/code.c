/*
 * 8 LED Blinking.c
 *
 * Created: 30-06-2022 19:24:17
 * Author : Manthan
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

int main(void)
{
    int a,b;
	DDRA=0b11111111;
    DDRB=0b00000000;
	DDRD=0b11111111;
    while (1) 
    {
		
		/*b=PINB;
		PORTA=b;
		a=(1*PINA0)+(2*PINA1)+(4*PINA2)+(8*PINA3);
		if (PINB==0b00000000)
		{
			PORTD=0b00000000;
		}
		else
		PORTD|=1<<(2+2);*/
		//PORTD =PINB;
		if(PINB==0b00000000)
		{
				PORTD=0b00000000;
		}
		else if (PINB==0b00000001)
		{
			PORTD=0b00000001;
		}
		else if(PINB==0b00000010)
		{
				PORTD=0b00000010;
		}
		else if(PINB==0b00000011)
		{
			PORTD=0b00000100;
		}
		else if(PINB==0b00000100)
		{
			PORTD=0b00001000;
		}
		else if(PINB==0b00000101)
		{
			PORTD=0b00010000;
		}
		else if(PINB==0b00000110)
		{
			PORTD=0b00100000;
		}
		else if(PINB==0b00000111)
		{
			PORTD=0b01000000;
		}
		else if(PINB==0b00001000)
		{
			PORTD=0b10000000;
		}
	}
}

