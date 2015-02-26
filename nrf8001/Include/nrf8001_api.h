#ifndef NRF8001_API_H__
#define NRF8001_API_H__

#include <avr/io.h>
#include "services.h"

#define SETUP_PACKET_LENGTH	32

#define NRF_PORT	PORTB
#define NRF_PIN		PINB
#define NRF_NSS		PORTB0
#define NRF_CLK		PORTB1
#define NRF_MOSI	PORTB2
#define NRF_MISO	PORTB3
#define NRF_RDY		PORTB4
#define NRF_RST		PORTB5

#define NRF_START_TRANSMISSION	(NRF_PORT &= ~(1<<NRF_NSS))
#define NRF_END_TRANSMISSION	(NRF_PORT |= 1<<NRF_NSS)

void nrf_wait_for_rdy(void);
void nrf_receive_packet(void);
void nrf_send_setup_data(void);
void nrf_setup(void);

void nrf_advertise(void);

/*
void nrf_send_command(unsigned char *packet);
void nrf_poll_aci(void);
*/
#endif
