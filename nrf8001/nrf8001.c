#define F_CPU 16000000  // macro that defines MCU frequency

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Include/SPI_api.h"
#include "Include/nrf8001_api.h"
#include "Include/UART_api.h"

#define nop() __asm__ __volatile__("nop")  // just to do nothing

/*
 * FUNCTION PROTOTYPES
 */
void pre_stuff(void);


/*
 * ISR functions
 */
ISR(USART1_TX_vect) {
	cli();
	sei();
}

ISR(USART1_RX_vect){
	cli();
	unsigned char uart_dr=UDR1;
	switch(uart_dr) {
		case 'A':
		case 'a':
			nrf_advertise();
			break;
		case 'B':
			uart_println((uint8_t *) &PORTB, 1);
			break;
		case 'b':
			uart_println((uint8_t *) &PINB, 1);
			break;
		case 'R':
		case 'r':
			nrf_receive_packet();
			break;
		case 'S':
		case 's':
			nrf_send_data((uint8_t *) "A message!", 10);
			break;
	}
	sei();
}


/*
 * MAIN FUNCTION
 */
int main(void) {
	// setup
	pre_stuff();
	uart_init();
	spi_init();
	
	uart_println((uint8_t *) "Program started!", 16);
	
	nrf_setup();
	
	// main loop
	sei();
	uart_println((uint8_t *) "Entering main!", 14);
    while(1) {
        if ((NRF_PIN & (1<<NRF_RDY)) == 0)
			nrf_receive_packet();
    }
}


/*
 * FUNCTION IMPLEMENTATIONS
 */
void pre_stuff(void) {
	// Remove CLKDIV8
	CLKPR = 0x80;
	CLKPR = 0x00;
	// DISABLE JTAG - take control of F port
	MCUCR = _BV(JTD);
	MCUCR = _BV(JTD);
}
