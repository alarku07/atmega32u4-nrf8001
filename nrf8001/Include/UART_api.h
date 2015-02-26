#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void uart_init(void);
void uart_print(uint8_t *data, uint8_t length);
void uart_println(uint8_t *data, uint8_t length);

#endif /* UART_H_ */
