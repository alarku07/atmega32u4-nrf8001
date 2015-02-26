#ifndef SPI_API_H_
#define SPI_API_H_

#include <avr/io.h>

void spi_init(void);
void spi_tranceive(uint8_t *data, uint8_t length);
uint8_t spi_receive(void);

#endif /* SPI_API_H_ */