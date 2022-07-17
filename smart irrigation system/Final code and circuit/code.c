// author= Manthan
#define F_CPU 4000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <math.h>
#include <util/delay.h>

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

void USART_Init( unsigned int baud )
{
	/* Set baud rate */
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}

void USART_Transmit( int data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR;
}

void UART_SendString(char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)		/* Send string till null */
	{
		USART_Transmit(str[j]);
		j++;
	}
}

int main(void)
{
	float c,duty;
	DDRA = 0x00;
	TCCR0 =0b01101001;
	DDRB=0b00001000;
	DDRA = 0x00;
	adc_init();
	USART_Init(25);
	 while (1)
	 {
		 c=read_adc(0)*5/1024;
		 if (c>2.5)
		 {
			 duty=c*51;
			 OCR0=duty;
			 UART_SendString("AT+CMGF=1");
			 _delay_ms(500);
			 UART_SendString("AT+CMGS = +91 6354514473\r Motor is on.\x1A\r");
			 _delay_ms(500);
		 }
		 else
		 {
			OCR0=0;
			UART_SendString("AT+CMGF=1");
			_delay_ms(500);
			UART_SendString("AT+CMGS = +91 6354514473\r Motor is off.\x1A\r");
			_delay_ms(500);
		 }
	 
	/*int x;
	x=read_adc(0);
	char str[5];
	itoa(x,str,10);
	
	for (int i=0;i<3;i++)
	{
		//USART_Receive();
		USART_Transmit(str[i]);
	}
	USART_Transmit('\r');*/
  }
}