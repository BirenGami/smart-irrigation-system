#define F_CPU 4000000UL			
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


void UART_init(long USART_BAUDRATE)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRL = BAUD_PRESCALE;		
	UBRRH = (BAUD_PRESCALE >> 8);	
}

unsigned char UART_RxChar()
{
	while ((UCSRA & (1 << RXC)) == 0);
	return(UDR);			
}

void UART_TxChar(char ch)
{
	while (! (UCSRA & (1<<UDRE)));	
	UDR = ch ;
}
int main()
{
	ADMUX=0x00;
	DDRA=0x00;
	DDRD=0xff;
	char buffer[10];
	UART_init(25);
	unsigned int x;
	while(1)
	{
		while(ADCSRA & (1<<ADSC));
		x = (ADCW)*5/1023;
		//itoa(x,buffer,10);
		//x=UART_RxChar();
		//for(int i=0;i<10;i++)
		//_delay_ms(1000);
		//UART_TxChar('b');
		//_delay_ms(1000);
	//	UART_TxChar('n');
	unsigned char j=0;
	while(buffer[j]!=0)
	{
		UART_TxChar(buffer[j]);
		j++;
	}
	}
}