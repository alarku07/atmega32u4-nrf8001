#include "../Include/UART_api.h"

void uart_init(void) {
	// Set baud rate
	UCSR1A = 0;
	// Asynchronous Double Speed mode operation
	UCSR1A = (1<<U2X1);
	//Enable receiver
	UCSR1B = (1<<RXEN1)|(1<<RXCIE1)|(1<<TXEN1)|(1<<TXCIE1);
	//Set frame format: 8data(UCSZ10), 1 stop bit(USBS1)
	UCSR1C = (3<<UCSZ10);
	//Baud rate 9600 fosc = 16M/8/9600 U2Xn=0 then 12 if U2Xn=1 then 25
	UBRR1=207;
}

void uart_print(uint8_t *data, uint8_t length) {
	uint8_t index;
	for (index=0; index<length; index++) {
		/* Wait for empty transmit buffer */
		while ( !( UCSR1A & (1<<UDRE1)) );
		/* Put data into buffer, sends the data */
		UDR1 = *data;
		data++;
	}
}

void uart_println(uint8_t *data, uint8_t length) {
	uart_print(data, length);
	while ( !( UCSR1A & (1<<UDRE1)) );
	UDR1 = '\r';
	while ( !( UCSR1A & (1<<UDRE1)) );
	UDR1 = '\n';
}