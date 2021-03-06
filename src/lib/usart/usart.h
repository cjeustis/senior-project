#ifndef USART_H
#define USART_H

void set_transmit_rate(unsigned int transmit);
void set_frame_size(unsigned int bits);
void set_stop_bits(unsigned int bits);
void set_parity(unsigned int bits);
void usart_transmit(unsigned char data);
int usart_receive(void);
void init_usart(unsigned int baud_rate, unsigned int transmit_rate, unsigned int data_bits, unsigned int stop_bits, unsigned int parity_bits);

#endif