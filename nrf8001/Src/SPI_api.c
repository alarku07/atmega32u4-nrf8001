#include "../Include/SPI_api.h"
#include "../Include/nrf8001_api.h"

void spi_init(void) {
	/*
	 * SS   - PB0
	 * CLK  - PB1
	 * MOSI - PB2
	 * MISO - PB3
	 * RDY  - PB4
	 * RST  - PB5
	*/
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<NRF_NSS)|(1<<NRF_CLK)|(1<<NRF_MOSI)|(1<<NRF_RST);
	// set nss pin, rst pin high
	PORTB |= (1<<NRF_NSS)|(1<<NRF_RST);
	// enable NRF_RDY pullup
	PORTB |= (1<<NRF_RDY);
	/* Enable SPI, Master, LSB first, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<DORD);
}

void spi_tranceive(uint8_t *data, uint8_t length){
	for (uint8_t i=0; i<length; i++) {
		SPDR = *data++;
		while(!((SPSR)&(1<<SPIF)));
	}
}

uint8_t spi_receive(void) {
	uint8_t data = 0;
	// Load data into the buffer
	SPDR = data;
	
	//Wait until transmission complete
	while(!((SPSR)&(1<<SPIF)));
	
	// Return received data
	data = SPDR;
	return data;
}